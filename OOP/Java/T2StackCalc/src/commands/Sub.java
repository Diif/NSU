package commands;

import calculator.ProgramContext;

import java.util.Stack;

public class Sub implements Command{
    @Override
    public final void execute(ProgramContext context){
        Stack<Double> stack = Command.assertAndGetStack(context);
        if(stack.size() < 2){
            logger.warning("stack size < 2, can't execute binary command. Ignore.");
            return;
        }
        stack.push(-1 * stack.pop() + stack.pop());
    }
}