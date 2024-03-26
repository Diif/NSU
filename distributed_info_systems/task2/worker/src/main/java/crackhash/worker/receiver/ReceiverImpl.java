package crackhash.worker.receiver;

import java.util.ArrayList;
import java.util.Objects;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.stream.Collectors;

import org.apache.commons.codec.digest.DigestUtils;
import org.paukov.combinatorics3.Generator;
import org.springframework.amqp.AmqpException;
import org.springframework.amqp.rabbit.connection.CorrelationData;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Scope;
import org.springframework.core.task.TaskExecutor;
import org.springframework.dao.OptimisticLockingFailureException;
import org.springframework.stereotype.Component;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import crackhash.worker.database.AnswerRepo;
import crackhash.worker.model.entities.AnswerStatus;
import crackhash.worker.model.entities.RequestPart;
import crackhash.worker.model.entities.WorkerAnswer;
import jakarta.annotation.PostConstruct;

@Component
@Scope("singleton")
public class ReceiverImpl implements PartReceiver {

  private final AnswerRepo answerRepo;
  private BlockingQueue<CorrelationData> ackQueue;
  private final RabbitTemplate rabbitTemplate;
  private final ObjectMapper jsonMapper;

  private Character[] dict = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890".chars().mapToObj(i -> Character.valueOf((char)i)).toArray(Character[]::new);

  @Value("${workerNum}")
  private Integer workerNumber;

  @Value("${managerQueueName}")
  private String managerQueueName;

  @Value("${exchangeName}")
	private String exchangeName;

  @Value("${senderMessageCapacity}")
  private Integer messageCapacity;

  @Value("${pingTickMillis}")
  private Integer pingTickMillis;

  private final TaskExecutor executor;

  @Autowired
  ReceiverImpl(
    ObjectMapper jsonMapper,
    @Qualifier("simpleAsyncExecutor") TaskExecutor executor,
    AnswerRepo answerRepo,
    RabbitTemplate rabbitTemplate){
      this.jsonMapper = jsonMapper;
      this.answerRepo = answerRepo;
      this.rabbitTemplate = rabbitTemplate;
      this.executor = executor;
  }

  @PostConstruct
  private void initReceiver(){
    ackQueue = new ArrayBlockingQueue<>(messageCapacity);
    executor.execute(new Runnable() {
      @Override
      public void run() {
        while (true) {
          try
          {
            var cd = ackQueue.take();
            var answer = answerRepo.findById(cd.getId()).get();
            try 
            {
              var cf = cd.getFuture().get(pingTickMillis, TimeUnit.MILLISECONDS);
              if (cf.isAck())
              {
                answer.setStatus(AnswerStatus.ACKED);
                boolean saved = false;
                while (!saved)
                {
                  saved = saveAnswer(answer);
                  if (!saved)
                  {
                    answer = answerRepo.findById(cd.getId()).get();
                  }
                }
              }
              else
              {
                throw new TimeoutException("nack received");
              }
            }
            catch (TimeoutException e)
            {
              sendAnswer(answer);
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

    try
    {
      makeRecovery();    
    } catch (Exception e)
    {
      System.out.println("Worker got exception during recovery: " + e.getLocalizedMessage());
    }
  }

  private boolean saveAnswer(WorkerAnswer answer){
    try
    {
      answerRepo.save(answer);
      return true;
    }
    catch (OptimisticLockingFailureException e)
    {
      return false;
    }
  }

  private void makeRecovery() throws JsonProcessingException, AmqpException, InterruptedException{
    var unacked = answerRepo.findByStatusAndWorkerNum(AnswerStatus.NOT_ACKED, workerNumber);
    
    for (var answer : unacked)
    {
      sendAnswer(answer);
    }
  }

  @Override
  public void receivePart(String partString) throws JsonMappingException, JsonProcessingException, InterruptedException {
    
    var part = jsonMapper.readValue(partString,RequestPart.class);
    var optAns = answerRepo.findFirst1ByPartId(part.getId());
    if (optAns.isPresent())
    {
      sendAnswer(optAns.get()); 
      return;
    }
    var res = crackHash(part);
    
    WorkerAnswer answer = new WorkerAnswer(
      null,
      part.getId(),
      workerNumber,
      AnswerStatus.NOT_ACKED,
      res);
    answer = answerRepo.save(answer);

    assert(Objects.nonNull(answer.getId()));

    sendAnswer(answer);
  }

  private void sendAnswer(WorkerAnswer answer) throws JsonProcessingException, AmqpException, InterruptedException{
    CorrelationData cd = new CorrelationData(answer.getId());
    rabbitTemplate.convertAndSend(
      exchangeName,
      managerQueueName,
      jsonMapper.writeValueAsString(answer),
      cd);
    ackQueue.put(cd);
  }

  private ArrayList<String> crackHash(RequestPart part){
    var res = new ArrayList<String>();
    var totalParts = part.getTotalParts();
    var partNum = part.getPartNum();
    var hash = part.getHash();
    for (int l = 1; l <= part.getMaxLen(); l++)
    {
      var generator = Generator.permutation(dict).withRepetitions(l).iterator();
      int totalPerm = (int)Math.pow((double) dict.length, (double)l);
      int partSize = (int) Math.floor((double)totalPerm / totalParts);
      int startInd =  partSize * (partNum - 1);
      int endInd =  partSize * (partNum);
      
      if (totalParts == partNum)
      {
        endInd += totalPerm % totalParts;
      }

      for (int i = 0; i < endInd; i++)
      {
        if (i < startInd)
        {
          generator.next();
          continue;
        }
        
        var word = generator.next().stream().map(String::valueOf).collect(Collectors.joining());
        
        if (DigestUtils.md5Hex(word).equals(hash))
        {
          res.add(word);
        }
      }
    }
    return res;
  }
  
}
