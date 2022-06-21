package controller;
import java.util.HashMap;

public class Command {
    public enum CommandType{
        DEALER_DELAY, BODY_DELAY, ENGINE_DELAY, ACCESSORY_DELAY, INCORRECT
    }
    private int value;
    private CommandType type;
    private static final Command instance = new Command();

    private Command(){
        type = CommandType.INCORRECT;
        value = 1000;
    }

    public static Command getInstance(){
        return instance;
    }

    public CommandType getType() {
        return type;
    }

    public void setType(CommandType type) {
        this.type = type;
    }

    public void setValue(int value){
        this.value = value;
    }

    public int getValue(){
        return value;
    }
}