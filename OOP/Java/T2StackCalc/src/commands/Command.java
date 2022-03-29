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
            logger.severe("Can't find stack in context. Can't continue.\n" + e.getLocalizedMessage());
            System.exit(-1);
        }
        assert stack != null;
        return stack;
    }
}
