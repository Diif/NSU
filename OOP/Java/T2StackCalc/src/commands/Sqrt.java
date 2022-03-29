package commands;

import calculator.ProgramContext;

import java.util.Stack;

public class Sqrt implements Command{
    @Override
    public final void execute(ProgramContext context){
        Stack<Double> stack = Command.assertAndGetStack(context);
        if(stack.size() < 1){
            logger.warning("stack size < 1, can't execute unary command. Ignore.");
            return;
        }
        stack.push(Math.sqrt(stack.pop()));
    }
}
