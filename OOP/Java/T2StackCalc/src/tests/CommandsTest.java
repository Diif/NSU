package tests;

import commands.*;
import calculator.ProgramContext;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.Stack;
import java.util.HashMap;

public class CommandsTest {
    @Test
    public void testExecution(){
        ProgramContext context = new ProgramContext();

        Add add = new Add();
        Comment comment = new Comment();
        Define define = new Define();
        Divide div = new Divide();
        Multiply mult = new Multiply();
        Print print = new Print();
        Push push = new Push();
        Sqrt sqrt = new Sqrt();
        Sub sub = new Sub();

        assertThrows(RuntimeException.class, () -> add.execute(context));
        comment.execute(context);
        assertThrows(RuntimeException.class, () -> define.execute(context));
        assertThrows(RuntimeException.class, () -> div.execute(context));
        assertThrows(RuntimeException.class, () -> mult.execute(context));
        assertThrows(RuntimeException.class, () -> print.execute(context));
        assertThrows(RuntimeException.class, () -> push.execute(context));
        assertThrows(RuntimeException.class, () -> sqrt.execute(context));
        assertThrows(RuntimeException.class, () -> sub.execute(context));

        Stack<Double> stack = new Stack<Double>();
        HashMap<String,Double> params= new HashMap<>();
        String[] args = new String[3];
        args[0] = "#";
        args[1] = "+";
        context.addToEnvironment("stack", stack);
        context.addToEnvironment("params", params);
        context.addToEnvironment("args", args);

        stack.push(4.0);
        stack.push(1.0);
        add.execute(context);
        assertEquals(stack.peek(), 5.0);
        assertEquals(stack.size(), 1);

        stack.push(1.0);
        comment.execute(context);
        assertEquals(stack.peek(), 1.0);
        assertEquals(stack.size(), 2);

        args[1] = "am";
        args[2] = "6";
        define.execute(context);
        assertTrue(params.containsKey("am"));
        assertEquals(params.get("am"), 6);

        args[1] = "am";
        push.execute(context);
        assertEquals(stack.size(), 3);
        assertEquals(stack.peek(), 6);

        div.execute(context);
        assertEquals(stack.peek(), 1.0 / 6.0);

        stack.clear();
        stack.push(10.0);
        push.execute(context);
        mult.execute(context);
        assertEquals(stack.peek(), 60);
        assertEquals(stack.size(), 1);
        stack.push(3.0);
        sub.execute(context);;
        assertEquals(stack.peek(), 57);
        stack.push(9.0);
        sqrt.execute(context);
        assertEquals(stack.peek(), 3);
        assertEquals(stack.size(), 2);

    }
}
