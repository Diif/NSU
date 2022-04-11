package tests;

import calculator.StackCalculator;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import static commands.Command.logger;

public class CalculatorTest {
    @Test
    public void testCalculator(){
        InputStream stream = null;
            try {
                stream = new FileInputStream(new File(("workflow.conf")));
            } catch (FileNotFoundException e){
                logger.info("Can't find input file. Using standard input...");
                stream = System.in;
            }
        assertNotNull(stream);

        StackCalculator calculator = new StackCalculator("config.conf");
        assertNotNull(calculator);
        calculator.calculate(stream);
    }
}
