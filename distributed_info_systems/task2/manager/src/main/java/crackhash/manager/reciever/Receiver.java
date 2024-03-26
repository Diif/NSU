package crackhash.manager.reciever;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonMappingException;

public interface Receiver {
  void receivePing(String pingString) throws JsonMappingException, JsonProcessingException;
  void receiveWorkerAnswer(String answerString) throws JsonMappingException, JsonProcessingException;
}
