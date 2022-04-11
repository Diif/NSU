package commands;

import calculator.ProgramContext;

import javax.naming.NamingException;
import java.util.HashMap;
import java.util.Stack;

public class Push implements Command {
    @Override
    public final void execute(ProgramContext context){
        String[] args = null;
        Stack<Double> stack = null;
        HashMap<String, Double> params = null;
        try {
            args = (String[]) context.lookup("args");
            stack = (Stack<Double>) context.lookup("stack");
            params = (HashMap<String,Double>) context.lookup("params");
        } catch (NamingException e){
            logger.severe("Can't find args/params/stack in context.\n" + e.getLocalizedMessage());
            throw new RuntimeException("No args/params/stack.");
        }
        assert stack != null;
        assert args != null;
        assert params != null;
        if(args.length < 2){
            logger.warning("Not enough args for PUSH command. Ignore.");
            return;
        }
        String toPush = args[1];
        if(params.containsKey(toPush)){
            stack.push(params.get(toPush));
        } else {
            try {
                stack.push(Double.parseDouble(args[1]));
            } catch (NumberFormatException e){
                logger.warning("Incorrect push argument. Ignore command.");
            }

        }
    }
}
