package logic.controller;


import java.util.HashMap;

public class Command {
    public enum CommandType{
        CLICK, FLAG, EXIT_TO_MENU,SAVE_SCORE,REMOVE_SCORE,SERIALIZE_SCORE, INCORRECT
    }
    private HashMap<String , Object> args;
    private CommandType type;
    private static final Command instance = new Command();

    private Command(){
        type = CommandType.INCORRECT;
        args = new HashMap<>();
    }

    public static Command getInstance(){
        return instance;
    }

    public void changeArg(String key, Object value){
        args.put(key, value);
    }

    public Object getArg(String key){
        return args.get(key);
    }

    public CommandType getType() {
        return type;
    }

    public void setType(CommandType type) {
        this.type = type;
    }

    public boolean isCorrect(){
        return !(type == CommandType.INCORRECT);
    }
}
