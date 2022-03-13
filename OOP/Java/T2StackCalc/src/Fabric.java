import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;
import java.util.HashMap;
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
        while(configScanner.hasNextLine()){
            String line = configScanner.nextLine();
            String[] key_and_val = line.split("=");
            map.put(key_and_val)
        }

    }
}
