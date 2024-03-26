package crackhash.manager.reciever;

import java.util.Objects;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.OptimisticLockingFailureException;
import org.springframework.stereotype.Component;
import org.springframework.transaction.annotation.Transactional;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import crackhash.manager.database.CrackRequestRepo;
import crackhash.manager.database.PartRepo;
import crackhash.manager.model.dtos.WorkerPingDto;
import crackhash.manager.model.entities.PartStatus;
import crackhash.manager.model.entities.RequestPart;
import crackhash.manager.model.entities.RequestStatus;
import crackhash.manager.model.entities.WorkerAnswer;
import crackhash.manager.model.internal.ServiceInfoProvider;

@Component
class ReceiverImpl implements Receiver{
  private final CrackRequestRepo requestRepo;
  private final PartRepo partRepo;
  private final ServiceInfoProvider infoProvider;
  private final ObjectMapper jsonMapper;

  @Autowired
  ReceiverImpl(
    ObjectMapper jsonMapper,
    CrackRequestRepo cRequestRepo,
    ServiceInfoProvider infoProvider,
    PartRepo partRepo){
    this.requestRepo = cRequestRepo;
    this.partRepo = partRepo;
    this.infoProvider = infoProvider;
    this.jsonMapper = jsonMapper;
  }

  @Override
  public synchronized void receiveWorkerAnswer(String answerString) throws JsonMappingException, JsonProcessingException {
    var answer = jsonMapper.readValue(answerString, WorkerAnswer.class);
    var part = partRepo.findById(answer.partId()).orElse(null);
    if (null == part)
    {
      return;
    }

    var req = requestRepo.findById(part.getRequestId()).orElse(null);
    if (null == req)
    {
      return;
    }

    if (part.getStatus().equals(PartStatus.SOLVED))
    {
      return;
    }

    if (req.getStatus().equals(RequestStatus.READY))
    {
      // must not be here.
      throw new RuntimeException("Inconsistent data has been found: got ACKED part for READY request.");
    }

    part.setStatus(PartStatus.SOLVED);
    
    req.getResult().addAll(answer.data());
    req.setAcs(req.getAcs() + 1);

    assert(req.getTotalParts() >= req.getAcs());

    if (req.getAcs() == req.getTotalParts())
    {
      req.setStatus(RequestStatus.READY);
    }

    // TODO: handle concurrency update exception
    // it's also must be in 1 transaction
    
    requestRepo.save(req);
    boolean saved = false;
    while (!saved) {
      saved = savePart(part);
      if (!saved)
      {
        part = partRepo.findById(part.getId()).get();
        part.setStatus(PartStatus.SOLVED);
      }
    }
  }

  private boolean savePart(RequestPart part){
    try
    {
      partRepo.save(part);
      return true;
    }
    catch (OptimisticLockingFailureException e) {
      return false;
    }
  }

  @Override
  public void receivePing(String pingString) throws JsonMappingException, JsonProcessingException {
    var ping = jsonMapper.readValue(pingString, WorkerPingDto.class);
    assert(Objects.nonNull(ping.workerNum()));

    infoProvider.nullifyStreakOrAddAlive(ping.workerNum());
  }
  
}
