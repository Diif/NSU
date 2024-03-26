package crackhash.manager.sender;

import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import org.springframework.amqp.AmqpException;
import org.springframework.amqp.rabbit.connection.CorrelationData;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.amqp.rabbit.core.RabbitTemplate.ConfirmCallback;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.core.task.TaskExecutor;
import org.springframework.dao.OptimisticLockingFailureException;
import org.springframework.lang.Nullable;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import crackhash.manager.database.CrackRequestRepo;
import crackhash.manager.database.PartRepo;
import crackhash.manager.model.entities.CrackRequest;
import crackhash.manager.model.entities.PartStatus;
import crackhash.manager.model.entities.RequestPart;
import crackhash.manager.model.internal.ServiceInfoProvider;
import jakarta.annotation.PostConstruct;

@Component
class SenderImpl extends PartSender {

  @Value("${senderCommandCapacity}")
  private Integer commandCapacity;

  @Value("${senderMessageCapacity}")
  private Integer messageCapacity;

  @Value("${exchangeName}")
  private String exchangeName;

  @Value("${pingTickMillis}")
  private Integer pingTickMillis;

  private TaskExecutor taskExecutor;
  private BlockingQueue<List<RequestPart>> requestPartQueue;
  private BlockingQueue<Command> commandQueue;
  private BlockingQueue<CorrelationData> ackQueue;
  private final ServiceInfoProvider infoProvider;
  private final ObjectMapper jsonMapper;

  private final RabbitTemplate rabbitTemplate;

  private final PartRepo partRepo;
  private final CrackRequestRepo requestRepo;

  @Autowired
  SenderImpl(
    ServiceInfoProvider infoProvider,
    ObjectMapper jsonMapper,
    RabbitTemplate rabbitTemplate,
    TaskExecutor taskExecutor,
    PartRepo partRepo,
    CrackRequestRepo requestRepo){
    this.rabbitTemplate = rabbitTemplate;
    this.jsonMapper = jsonMapper;
    this.partRepo = partRepo;
    this.infoProvider = infoProvider;
    this.taskExecutor = taskExecutor;
    this.requestRepo = requestRepo;
  }

  private void startSender(){
    taskExecutor.execute(new Runnable() {

      @Override
      public void run() {
        Thread.currentThread().setName("Sender thread");
        while (true) {
          try {
            commandQueue.take().execute();
          } catch (InterruptedException e) {
            System.out.println("Sender thread is down.");
            return;
          } catch (Exception e){
            System.out.println("Sender got exception:" + e.getLocalizedMessage());            
          }
        }
      }
      
    });

    taskExecutor.execute(new Runnable() {
      @Override
      public void run() {
        while (true) {
          try
          {
            var cd = ackQueue.take();
            var part = partRepo.findById(cd.getId()).get();
            try 
            {
              var cf = cd.getFuture().get(pingTickMillis, TimeUnit.MILLISECONDS);
              if (cf.isAck())
              {
                part.setStatus(PartStatus.ACKED);
                partRepo.save(part);
              }
              else
              {
                throw new TimeoutException("nack received");
              }
            }
            catch (TimeoutException e)
            {
              sendParts(List.of(part));
            }
          }
          catch (InterruptedException e) {
            System.out.println("Not_acked resender thread is down.");
            return;
          }
          catch (Exception e){
            System.out.println("Sender got exception:" + e.getLocalizedMessage());            
          }
        }
      }
      
    });
  }

  @PostConstruct
  private void initAndStartSender(){
    requestPartQueue =  new ArrayBlockingQueue<>(commandCapacity);
    commandQueue =  new ArrayBlockingQueue<>(messageCapacity);
    ackQueue = new ArrayBlockingQueue<>(messageCapacity);
    startSender();
  }

  @Override
  public void addPartsToSend(List<RequestPart> parts) throws InterruptedException {
    requestPartQueue.put(parts);
  }

  @Override
  public void addCommandToExecute(Command command) throws InterruptedException {
    commandQueue.put(command);
  }

  @Override
  void sendParts() throws InterruptedException, JsonProcessingException, AmqpException {
    if (requestPartQueue.isEmpty())
    {
      return;
    }
    var workers = infoProvider.getAliveWorkersOrWait().toArray();
    
    int workerInd = 0;
    int workersAmount = workers.length;
    while (!requestPartQueue.isEmpty()) {
      var parts = requestPartQueue.remove();
      assert(parts.size() > 0);

      workerInd = sendParts(parts, workerInd, workersAmount, workers);
    }
  }

  private void sendParts(List<RequestPart> parts) throws InterruptedException, JsonProcessingException, AmqpException{
    var workers = infoProvider.getAliveWorkersOrWait().toArray();
    
    int workerInd = 0;
    int workersAmount = workers.length;

    sendParts(parts, workerInd, workersAmount, workers);
  }

  private int sendParts(List<RequestPart> parts, int workerInd, int workersAmount, Object[] workers) throws JsonProcessingException, AmqpException, InterruptedException{
    for(var part : parts)
      {
        part.setWorkerNum((Integer)workers[workerInd]);

        assert(Objects.nonNull(part.getId()));
        // can't be < 1 by design
        assert(part.getWorkerNum() > 0);

        part.setStatus(PartStatus.NOT_ACKED);
        try
        {
          partRepo.save(part);
        } catch (OptimisticLockingFailureException e)
        {
          System.out.println("Sender exception: " + e.getLocalizedMessage());
          continue;
        }
        

        CorrelationData cd = new CorrelationData(part.getId());
        rabbitTemplate.convertAndSend(exchangeName,
        infoProvider.getWorkerRouteKey(part.getWorkerNum()),
        jsonMapper.writeValueAsString(part),
        cd);

        ackQueue.put(cd);

        workerInd = (workerInd + 1) % workersAmount;        
      }
      return workerInd;
  }

  @Override
  void resendKicked(int worker) throws JsonProcessingException, AmqpException, InterruptedException {
    var parts = partRepo.findByWorkerNumAndStatusNot(worker, PartStatus.SOLVED);
    sendParts(parts);
  }

  @Override
  void resendCreated() throws JsonProcessingException, AmqpException, InterruptedException {
    var toResend = partRepo.findByStatus(PartStatus.CREATED);
    sendParts(toResend);
  }

  @Override
  void resendZeroParts() throws InterruptedException, JsonProcessingException, AmqpException{
    var numAlive = infoProvider.getAmountOfAliveWorkers();
    if (numAlive == 0)
    {
      return;
    }

    var zeroPartReqs = requestRepo.findByTotalParts(0);
    
    for (var req : zeroPartReqs)
    {
      req.setTotalParts(numAlive);
      var parts = CrackRequest.splitRequestIntoParts(req);
      requestRepo.save(req);
      parts = partRepo.saveAll(parts);
      sendParts(parts);
    }
  }
}
