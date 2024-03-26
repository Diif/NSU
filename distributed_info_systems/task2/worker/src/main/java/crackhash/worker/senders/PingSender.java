package crackhash.worker.senders;

import org.springframework.amqp.core.MessageDeliveryMode;
import org.springframework.amqp.core.MessageProperties;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.core.task.TaskExecutor;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import crackhash.worker.model.dtos.WorkerPingDto;

@Component
public class PingSender {

  private final RabbitTemplate rabbitTemplate;
  private final ObjectMapper jsonMapper;


  @Value("${workerNum}")
  private Integer workerNumber;

  @Value("${exchangeName}")
	private String exchangeName;

  @Value("${managerQueueName}")
  private String managerQueueName;


  @Autowired
  PingSender(
    RabbitTemplate rabbitTemplate,
    ObjectMapper jsonMapper){
    this.rabbitTemplate = rabbitTemplate;
    this.jsonMapper = jsonMapper;
  }

  @Scheduled(fixedRateString = "${pingTickMillis}")
  private void sendPing() throws JsonProcessingException{
    rabbitTemplate.convertAndSend(exchangeName, "ping",
    jsonMapper.writeValueAsString(new WorkerPingDto(workerNumber)));
  }
}
