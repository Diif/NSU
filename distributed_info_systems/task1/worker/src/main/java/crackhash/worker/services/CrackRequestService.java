package crackhash.worker.services;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

import org.apache.commons.codec.digest.DigestUtils;
import org.paukov.combinatorics3.Generator;
import org.springframework.context.annotation.Scope;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.client.HttpComponentsClientHttpRequestFactory;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

import crackhash.worker.model.dtos.CrackRequestDto;
import crackhash.worker.model.dtos.PatchRequestResponseDto;
import crackhash.worker.model.entities.CrackRequest;

@Service
@Scope("singleton")
public class CrackRequestService implements ICrackRequestService {
  private Character[] dict = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890".chars().mapToObj(i -> Character.valueOf((char)i)).toArray(Character[]::new);

  private ExecutorService threadPool = Executors.newFixedThreadPool(1);

  @Override
  public void addRequest(CrackRequestDto crackRequest) {
    var cr = new CrackRequest(crackRequest);
    threadPool.submit(new Runnable() {
      @Override
      public void run() {
        crackHash(cr);
      }
    });
    
  }

  private void crackHash(CrackRequest crackRequest){
    var res = crackRequest.getResult();
    
    for (int l = 1; l <= crackRequest.getMaxLen(); l++)
    {
      var generator = Generator.permutation(dict).withRepetitions(l).iterator();
      int totalPerm = (int)Math.pow((double) dict.length, (double)l);
      int partSize = (int) Math.floor((double)totalPerm / crackRequest.getPartTotal());
      int startInd =  partSize * (crackRequest.getPartNum() - 1);
      int endInd =  partSize * (crackRequest.getPartNum());
      
      if (crackRequest.getPartTotal() == crackRequest.getPartNum())
      {
        endInd += totalPerm % crackRequest.getPartTotal();
      }

      for (int i = 0; i < endInd; i++)
      {
        if (i < startInd)
        {
          generator.next();
          continue;
        }
        
        var word = generator.next().stream().map(String::valueOf).collect(Collectors.joining());
        
        if (DigestUtils.md5Hex(word).equals(crackRequest.getHash()))
        {
          res.add(word);
        }
      }
    }
    sendPatchRequest(crackRequest);
  }

  private void sendPatchRequest(CrackRequest cr){
    try {
      RestTemplate restTemplate = new RestTemplate(new HttpComponentsClientHttpRequestFactory());;
      String addr = "http://manager:8080/internal/api/manager/hash/crack/request";
      PatchRequestResponseDto body = new PatchRequestResponseDto(cr.getId(), cr.getResult());
      HttpEntity<PatchRequestResponseDto> request = new HttpEntity<PatchRequestResponseDto>(body);
      restTemplate.exchange(addr,HttpMethod.PATCH, request, Void.class); 
    } catch (Exception e){
      System.out.println(e.getMessage());
    }
    
  }
  
}
