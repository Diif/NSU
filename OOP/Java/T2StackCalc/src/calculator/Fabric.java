package calculator;

import java.io.IOException;
import java.util.Scanner;
import java.io.File;
import java.util.HashMap;
import java.lang.reflect.InvocationTargetException;
import commands.*;
import java.util.logging.Logger;

public class Fabric {
    private Scanner configScanner;
    private final Logger logger;

    public Fabric(String configName)  {
        logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);
            try {
                configScanner = new Scanner(new File(configName));
            }
            catch (IOException e){
                logger.severe("Can't open config file.\n\t" +e.getLocalizedMessage());
            }
    }

    public HashMap<String, Command> createCommandsMap(){
        HashMap<String, Command> map = new HashMap<String, Command>();
        int counter = 1;
        if(null == configScanner){
            return map;
        }
        while(configScanner.hasNextLine()){
            String line = configScanner.nextLine();
            String[] key_and_val = line.split("=");
            try {
                Class<?> c1 = Class.forName("commands." + key_and_val[1]);
                map.put(key_and_val[0], (Command)c1.getDeclaredConstructor().newInstance());
            } catch (ArrayIndexOutOfBoundsException e){
                logger.warning("Incorrect command line. Ignored.\n\t" + counter + ": " + line);
            } catch (ClassNotFoundException e){
                logger.warning("Class doesn't exists in commands package. + \n\t" + counter + ": " + line + "\n\t" + e.getLocalizedMessage());
            } catch (NoSuchMethodException | InstantiationException | IllegalAccessException  | InvocationTargetException e){
                logger.severe("Internal error. Check commands files.\n\t" + counter + ": " + line + "\n\t" + e.getLocalizedMessage());
            }
            counter++;
        }
    return map;
    }
}
