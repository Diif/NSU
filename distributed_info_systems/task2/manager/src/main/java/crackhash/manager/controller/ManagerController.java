package crackhash.manager.controller;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import crackhash.manager.database.CrackRequestRepo;
import crackhash.manager.database.PartRepo;
import crackhash.manager.model.dtos.GetStatusDto;
import crackhash.manager.model.dtos.PostRequestBody;
import crackhash.manager.model.dtos.PostRequestResponse;
import crackhash.manager.model.entities.CrackRequest;
import crackhash.manager.model.entities.PartStatus;
import crackhash.manager.model.entities.RequestPart;
import crackhash.manager.model.entities.RequestStatus;
import crackhash.manager.model.internal.ServiceInfoProvider;
import crackhash.manager.sender.CommandFactory;
import crackhash.manager.sender.PartSender;

@RestController
public class ManagerController {

  private final PartSender sender;
  private final CommandFactory commandFactory;
  private final ServiceInfoProvider infoProvider;

  private final CrackRequestRepo requestRepo;
  private final PartRepo partRepo;
  
  @Autowired
  public ManagerController(
    CommandFactory commandFactory,
    PartSender sender,
    ServiceInfoProvider infoProvider,
    CrackRequestRepo cRequestRepo,
    PartRepo partRepo){
    this.sender = sender;
    this.infoProvider = infoProvider;
    this.requestRepo = cRequestRepo;
    this.partRepo = partRepo;
    this.commandFactory = commandFactory;
  }
  
  @PostMapping("/api/hash/crack")
  public ResponseEntity<PostRequestResponse> postRequest(@RequestBody PostRequestBody request) {    
    if (!infoProvider.isRecovered())
    {
      return new ResponseEntity<>(HttpStatus.SERVICE_UNAVAILABLE);
    }
    var t = createNewCrackRequest(request);
    var cr = requestRepo.save(t);
    CompletableFuture.runAsync(new Runnable() {
      @Override
      public void run() {
        assert(cr.getTotalParts() >= 0);
        
        if(cr.getTotalParts() == 0)
        {
          return;
        }
        List<RequestPart> parts = CrackRequest.splitRequestIntoParts(cr);
        parts = partRepo.saveAll(parts);
        try {
          sendPartsToWorkers(parts);
        } catch (InterruptedException e) {
          throw new RuntimeException(e);
        }
      }
    });
    return new ResponseEntity<>(new PostRequestResponse(cr.getId()), HttpStatus.OK);
  }

  private CrackRequest createNewCrackRequest(PostRequestBody requestBody){
    var t = new CrackRequest(
      null,
      requestBody.getHash(),
      requestBody.getMaxLength(),
      infoProvider.getAmountOfAliveWorkers(),
      RequestStatus.IN_PROGRESS,
      0,
      new ArrayList<String>()
      );
    return t;
  }

  private void sendPartsToWorkers(List<RequestPart> parts) throws InterruptedException{
    sender.addPartsToSend(parts);
    sender.addCommandToExecute(commandFactory.getSendCommand());
  }

  @GetMapping("/api/hash/status")
  public ResponseEntity<GetStatusDto> getRequest(@RequestParam String requestId) {
    var req = requestRepo.findById(requestId);
    return req
    .map((r) -> new ResponseEntity<GetStatusDto>(new GetStatusDto(r.getStatus().name(), r.getResult()), HttpStatus.OK))
    .orElse(new ResponseEntity<GetStatusDto>(new GetStatusDto(RequestStatus.ERROR.name(), null), HttpStatus.OK));
  }
}