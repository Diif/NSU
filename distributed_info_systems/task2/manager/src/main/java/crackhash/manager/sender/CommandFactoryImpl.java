package crackhash.manager.sender;

import org.springframework.amqp.AmqpException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import com.fasterxml.jackson.core.JsonProcessingException;

@Component
class CommandFactoryImpl implements CommandFactory{

  private final PartSender sender;
  private final Command resendCommand;

  @Autowired
  CommandFactoryImpl(PartSender sender){
    this.sender = sender;
    resendCommand = new Command() {
      @Override
      public void execute(){
        try{
          sender.sendParts();
        } catch (Exception e){
          System.out.println("Command execution fail: " + e.getLocalizedMessage());
        }
      }
    };
  }

  @Override
  public Command getSendCommand() {
    return resendCommand;
  }

  @Override
  public Command getResendCommand(int workerNum) {
    return new Command() {
      @Override
      public void execute() throws JsonProcessingException, AmqpException, InterruptedException {
        sender.resendKicked(workerNum);
      }
    };
  }

  @Override
  public Command getResendCreatedCommand() {
    return new Command() {
      @Override
      public void execute() throws JsonProcessingException, AmqpException, InterruptedException {
        sender.resendCreated();
      }
    };
  }

  @Override
  public Command getResendZeroPartsCommand() {
    return new Command() {
      @Override
      public void execute() throws JsonProcessingException, AmqpException, InterruptedException {
        sender.resendZeroParts();
      }
    };
  }
  
}
