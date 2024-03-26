package crackhash.manager.sender;

import java.util.List;

import org.springframework.amqp.AmqpException;

import com.fasterxml.jackson.core.JsonProcessingException;

import crackhash.manager.model.entities.RequestPart;

public abstract class PartSender {
  public abstract void addPartsToSend(List<RequestPart> parts) throws InterruptedException;
  public abstract void addCommandToExecute(Command command) throws InterruptedException;

  abstract void sendParts() throws InterruptedException, JsonProcessingException, AmqpException;
  abstract void resendKicked(int workerNum) throws JsonProcessingException, AmqpException, InterruptedException;
  abstract void resendCreated() throws JsonProcessingException, AmqpException, InterruptedException;
  abstract void resendZeroParts() throws InterruptedException, JsonProcessingException, AmqpException;
}