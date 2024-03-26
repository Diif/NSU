package crackhash.manager.sender;

public interface CommandFactory {
  Command getSendCommand();
  Command getResendCommand(int workerNum);
  Command getResendCreatedCommand();
  Command getResendZeroPartsCommand();
}