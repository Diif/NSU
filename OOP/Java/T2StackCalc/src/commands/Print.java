package commands;

import calculator.ProgramContext;

import java.util.Stack;

public class Print implements Command{
        @Override
        public final void execute(ProgramContext context){
            Stack<Double> stack = Command.assertAndGetStack(context);
            if(stack.size() >= 1){
                System.out.println(stack.peek());
            } else {
                logger.warning("stack is empty. Print nothing.");
            }
        }
}
