package crackhash.worker;

import org.springframework.amqp.core.Binding;
import org.springframework.amqp.core.BindingBuilder;
import org.springframework.amqp.core.Queue;
import org.springframework.amqp.core.TopicExchange;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;
import org.springframework.amqp.rabbit.listener.SimpleMessageListenerContainer;
import org.springframework.amqp.rabbit.listener.adapter.MessageListenerAdapter;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.core.task.SimpleAsyncTaskExecutor;
import org.springframework.core.task.TaskExecutor;
import org.springframework.data.mongodb.repository.config.EnableMongoRepositories;
import org.springframework.scheduling.annotation.EnableScheduling;

import crackhash.worker.receiver.PartReceiver;


@SpringBootApplication
@EnableMongoRepositories
@EnableScheduling
public class WorkerApplication {

	@Value("${exchangeName}")
	private String exchangeName;

  @Value("${workerNum}")
  private String workerNumber;

  @Bean
  Queue queue() {
    return new Queue("worker"+workerNumber, true);
  }

  @Bean
  TopicExchange exchange() {
    return new TopicExchange(exchangeName);
  }

  @Bean
  Binding binding(Queue queue, TopicExchange exchange) {
    return BindingBuilder.bind(queue).to(exchange).with("worker"+workerNumber);
  }

  @Bean
  SimpleMessageListenerContainer container(ConnectionFactory connectionFactory,
      MessageListenerAdapter listenerAdapter) {
    SimpleMessageListenerContainer container = new SimpleMessageListenerContainer();
    container.setConnectionFactory(connectionFactory);
    container.setQueueNames("worker"+workerNumber);
    container.setMessageListener(listenerAdapter);
    return container;
  }

  @Bean
  MessageListenerAdapter listenerAdapter(PartReceiver receiver) {
    var listener = new MessageListenerAdapter(receiver, "receivePart"); 
    return listener;
  }

  @Bean
  @Qualifier("simpleAsyncExecutor")
  TaskExecutor taskExecutor() {
    return new SimpleAsyncTaskExecutor();
  }

	public static void main(String[] args) {
		SpringApplication.run(WorkerApplication.class, args);
	}

}
