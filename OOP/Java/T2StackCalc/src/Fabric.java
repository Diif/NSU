import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;
import java.util.HashMap;
import java.lang.reflect.InvocationTargetException;
import commands.*;

public class Fabric {
    private Scanner configScanner;

    public Fabric(String configName){
        try{
            Path filePath = Paths.get(configName);
            configScanner = new Scanner(filePath);
        } catch(IOException e) {
            System.err.println("Error while reading file: " + e.getLocalizedMessage() + "Can't continue without commands.");
        }
    }

    public HashMap<String, Command> CreateCommands(){
        HashMap<String, Command> map = new HashMap<String, Command>();
        int counter = 1;
        while(configScanner.hasNextLine()){
            String line = configScanner.nextLine();
            String[] key_and_val = line.split("=");
            try {
                Class c1 = Class.forName("commands." + key_and_val[1]);
                map.put(key_and_val[0], (Command)c1.getDeclaredConstructor().newInstance());
            } catch (ArrayIndexOutOfBoundsException e){
                System.out.println("Incorrect command line. Ignored.\n\t" + counter + ": " + line);
            } catch (ClassNotFoundException e){
                System.out.println("Class doesn't exists in commands package. + \n\t" + counter + ": " + line + "\n\t" + e.getLocalizedMessage());
            } catch (NoSuchMethodException | InstantiationException | IllegalAccessException  | InvocationTargetException e){
                System.out.println("Internal error.\n\t" + counter + ": " + line + "\n\t" + e.getLocalizedMessage());
            }
        }

    }
}
