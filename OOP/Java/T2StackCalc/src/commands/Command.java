package commands;
import calculator.ProgramContext;

import javax.naming.NamingException;
import java.util.Stack;
import java.util.logging.Logger;

public interface Command {
    Logger logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);

    void execute(ProgramContext context);

     static Stack<Double> assertAndGetStack(ProgramContext context){
        Stack<Double> stack = null;
        try {
            stack = (Stack<Double>) context.lookup("stack");
        } catch (NamingException e){
            logger.severe("Can't find stack in context.\n" + e.getLocalizedMessage());
            throw new RuntimeException("No stack.");
        }
        assert stack != null;
        return stack;
    }
}
