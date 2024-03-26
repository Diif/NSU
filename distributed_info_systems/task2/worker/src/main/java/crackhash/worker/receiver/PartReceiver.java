package crackhash.worker.receiver;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonMappingException;

public interface PartReceiver {
  void receivePart(String part) throws JsonMappingException, JsonProcessingException, InterruptedException;
}
