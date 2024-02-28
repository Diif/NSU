package crackhash.manager.controller;

import java.util.Calendar;
import java.util.concurrent.ConcurrentHashMap;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PatchMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.client.RestTemplate;

import crackhash.manager.model.dtos.CrackRequestDto;
import crackhash.manager.model.dtos.GetStatusDto;
import crackhash.manager.model.dtos.PatchRequestBodyDto;
import crackhash.manager.model.dtos.PostRequestBody;
import crackhash.manager.model.dtos.PostRequestResponse;
import crackhash.manager.model.entities.CrackRequest;
import crackhash.manager.model.entities.CrackRequest.CrackStatus;

@RestController
public class ManagerController {

  @Value("${numWorkers}")
  private Integer numWorkers;

  @Value("${timeoutHalfMil}")
  private Integer timeoutHalfMil;

  private ConcurrentHashMap<Integer,CrackRequest> requests = new ConcurrentHashMap<>();

  @PostMapping("/api/hash/crack")
  public ResponseEntity<PostRequestResponse> postRequest(@RequestBody PostRequestBody request) {
    var cr = new CrackRequest(request.getHash(), request.getMaxLength(), (int)timeoutHalfMil / 500);
    requests.put(cr.getId(),cr);
    sendTaskToWorkers(cr);
    return new ResponseEntity<>(new PostRequestResponse(cr.getId()), HttpStatus.OK);
  }

  private void sendTaskToWorkers(CrackRequest crackRequest){
    RestTemplate restTemplate = new RestTemplate();
    for (int i = 1; i <= numWorkers; i++)
    {
      String addr = "http://worker" + i + ":8080/internal/api/worker/hash/crack/task";
      var body = new CrackRequestDto(crackRequest, i, numWorkers);
      HttpEntity<CrackRequestDto> request = new HttpEntity<CrackRequestDto>(body);
      restTemplate.postForEntity(addr, request, Void.class);
    }
  }

  @GetMapping("/api/hash/status")
  public ResponseEntity<GetStatusDto> getRequest(@RequestParam Integer requestId) {
    var req = requests.get(requestId);
    if (req == null || req.getStatus().equals(CrackRequest.CrackStatus.ERROR))
    {
      return new ResponseEntity<GetStatusDto>(new GetStatusDto(CrackRequest.CrackStatus.ERROR.name(), null), HttpStatus.OK);
    }
    else if (req.getStatus().equals(CrackRequest.CrackStatus.IN_PROGRESS))
    {
      return new ResponseEntity<GetStatusDto>(new GetStatusDto(CrackRequest.CrackStatus.IN_PROGRESS.name(), null), HttpStatus.OK);
    }
    return new ResponseEntity<GetStatusDto>(new GetStatusDto(CrackRequest.CrackStatus.READY.name(), req.getResult()), HttpStatus.OK);
  }
  
  @PatchMapping("/internal/api/manager/hash/crack/request")
  public void patchReguest(@RequestBody PatchRequestBodyDto pr) {
    try {
      var cr = requests.get(pr.id());
      cr.addResult(pr.data());
      cr.increaseAcs();
      if (cr.getAcs() == numWorkers)
      {
        cr.setStatus(CrackStatus.READY);
      }
    } catch (NullPointerException e){
      // do nothing
    }   
  }

  @Scheduled(fixedRateString = "${timeoutHalfMil}")
  private void checkTimeouts(){
    var curTime = Calendar.getInstance();
    for (var e : requests.entrySet()){
      if (!e.getValue().getStatus().equals(CrackStatus.IN_PROGRESS)){
        continue;
      }
      if (e.getValue().getExpirationTime().before(curTime)){
        e.getValue().setStatus(CrackStatus.ERROR);
      }
    }
  }
}