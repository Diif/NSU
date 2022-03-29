package commands;

import calculator.ProgramContext;

import java.util.Stack;

public class Divide implements Command{
    @Override
    public final void execute(ProgramContext context){
        Stack<Double> stack = Command.assertAndGetStack(context);
        if(stack.size() < 2){
            logger.warning("stack size < 2, can't execute binary command. Ignore.");
            return;
        }
        Double divider = stack.pop();
        if(divider == 0){
            logger.warning("Division by zero. Ignore command.");
            return;
        }
        stack.push(stack.pop() / divider);
    }
}
