package crackhash.manager;

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
import org.springframework.transaction.annotation.EnableTransactionManagement;

import crackhash.manager.reciever.Receiver;

@SpringBootApplication
@EnableMongoRepositories
@EnableScheduling
public class ManagerApplication {

  @Value("${exchangeName}")
	public String topicExchangeName;

  @Value("${managerQueueName}")
  public String managerQueueName;

  public final String pingQueueName = "ping";

  @Bean
  @Qualifier("queueManager")
  Queue queueManager() {
    return new Queue(managerQueueName, true);
  }

  @Bean
  @Qualifier("queuePing")
  Queue queuePing() {
    return new Queue(pingQueueName, false);
  }

  @Bean
  TopicExchange exchange() {
    return new TopicExchange(topicExchangeName);
  }

  @Bean
  Binding bindingExchangeManager(@Qualifier("queueManager")Queue queue, TopicExchange exchange) {
    return BindingBuilder.bind(queue).to(exchange).with(managerQueueName);
  }

  @Bean
  Binding bindingExchangePing(@Qualifier("queuePing") Queue queue, TopicExchange exchange) {
    return BindingBuilder.bind(queue).to(exchange).with(pingQueueName);
  }

  @Bean
  SimpleMessageListenerContainer container(
    ConnectionFactory connectionFactory,
    MessageListenerAdapter listenerAdapter) {
    SimpleMessageListenerContainer container = new SimpleMessageListenerContainer();
    container.setConnectionFactory(connectionFactory);
    container.setQueueNames(managerQueueName, pingQueueName);
    container.setMessageListener(listenerAdapter);
    return container;
  }

  @Bean
  MessageListenerAdapter listenerAdapter(Receiver receiver) {
    var listener = new MessageListenerAdapter(receiver);
    listener.addQueueOrTagToMethodName("ping", "receivePing");
    listener.addQueueOrTagToMethodName("manager", "receiveWorkerAnswer");
    return listener;
  }

  @Bean
  TaskExecutor taskExecutor() {
    return new SimpleAsyncTaskExecutor();
  }
	public static void main(String[] args) {
    // TODO
    //  Recovery:
    //   *(send 0 part requests OR created parts without parts) AND kick not in
    //  Mongo replics
		SpringApplication.run(ManagerApplication.class, args);
	}
	
}
