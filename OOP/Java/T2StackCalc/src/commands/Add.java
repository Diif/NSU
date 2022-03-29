package commands;

import calculator.ProgramContext;

import java.util.Stack;

public class Add implements Command{
    @Override
    public final void execute(ProgramContext context){
        Stack<Double> stack = Command.assertAndGetStack(context);
        if(stack.size() < 2){
            logger.warning("stack size < 2, can't execute binary command. Ignore.");
            return;
        }
        stack.push((stack.pop()) + stack.pop());
    }
}
