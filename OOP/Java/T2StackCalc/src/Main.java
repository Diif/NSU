
import calculator.StackCalculator;
import tests.CalculatorTest;
import tests.CommandsTest;
import tests.FabricTest;

import java.io.*;
import java.util.logging.*;

public class Main {

    private static void setupGlobalLogger(){
        Logger logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);
        FileHandler fileHandler = null;
        try {
            fileHandler = new FileHandler("log.txt");
        } catch (IOException e){
            System.err.println("Can't create file logger.");
        }
        assert fileHandler != null;
        fileHandler.setFormatter(new SimpleFormatter());

        Logger rootLogger = Logger.getLogger("");
        Handler[] handlers = rootLogger.getHandlers();
        if (handlers[0] instanceof ConsoleHandler) {
            rootLogger.removeHandler(handlers[0]);
        }

        logger.addHandler(fileHandler);
    }

    public static void main(String[] args) {
        setupGlobalLogger();
        Logger logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);
        logger.info("Main logger was created.");
        FabricTest fabricTest = new FabricTest();
        fabricTest.testMethods();
        CommandsTest commandsTest = new CommandsTest();
        commandsTest.testExecution();
        CalculatorTest calculatorTest = new CalculatorTest();
        calculatorTest.testCalculator();
//        InputStream stream = System.in;
//        if (args.length > 0) {
//            try {
//                stream = new FileInputStream(new File((args[0])));
//            } catch (FileNotFoundException e){
//                logger.info("Can't find input file. Using standard input...");
//                stream = System.in;
//            }
//        }
//
//        StackCalculator calculator = new StackCalculator("config.conf");
//        calculator.calculate(stream);
    }

}
