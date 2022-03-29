package calculator;

import commands.Command;

import java.util.HashMap;
import java.util.Scanner;
import java.util.Stack;
import java.io.InputStream;
import java.util.logging.Logger;

public class StackCalculator {
    private final HashMap<String, Command> commandMap;
    private final Logger logger;

    public StackCalculator(String fileWithConfiguration){
        logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);
        Fabric fabric = new Fabric(fileWithConfiguration);
        commandMap = fabric.createCommandsMap();
    }

    public void calculate(InputStream in){
        logger.info("Start calculation...");
        Scanner fileWithCommands = new Scanner(in);
        int lineNum = 1;
        Stack<Double> stack = new Stack<Double>();
        HashMap<String, Double> params = new HashMap<String, Double>();
        ProgramContext context = new ProgramContext();
        context.addToEnvironment("stack", stack);
        context.addToEnvironment("params", params);


        while(fileWithCommands.hasNextLine()){
            String line = fileWithCommands.nextLine();
            String[] strs = line.split(" ");
            try {
                if(!commandMap.containsKey(strs[0])){
                    throw new RuntimeException();
                }
                context.addToEnvironment("args", strs);
            } catch (RuntimeException e){
                logger.warning("Unrecognized command: " + strs[0] +
                        "\n\tAt line: " + lineNum);
                continue;
            }
            Command command = commandMap.get(strs[0]);
            command.execute(context);
            lineNum++;
        }
        if(stack.size() > 1) {
            logger.warning("stack size > 1.");
        }
    }
}
