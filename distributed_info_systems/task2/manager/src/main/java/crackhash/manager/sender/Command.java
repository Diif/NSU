package crackhash.manager.sender;

import org.springframework.amqp.AmqpException;

import com.fasterxml.jackson.core.JsonProcessingException;

public interface Command {
  void execute() throws JsonProcessingException, AmqpException, InterruptedException;
}
