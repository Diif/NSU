package model.confighandler;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

public class ConfigHandler {
    private HashMap<String, Integer> options;

    public ConfigHandler(){
        options = new HashMap<>();
        options.put("storageBodySize", 100);
        options.put("storageEngineSize", 100);
        options.put("storageAccessorySize", 100);
        options.put("storageCarSize", 100);
        options.put("accessorySupplies", 2);
        options.put("workers", 3);
        options.put("dealers", 2);
        options.put("logMode", 0);
    }

    public void loadConfigOptions(String pathname){
        Scanner scanner;
        try {
            scanner = new Scanner(new File(pathname));
        } catch (FileNotFoundException e){
            System.err.println("Can't open config. Default setting applied.");
            return;
        }
        int line = 0;
        while (scanner.hasNextLine()){
            line++;
            try {
                String[] optionAndVal = scanner.nextLine().split("=");
                if (options.containsKey(optionAndVal[0])) {
                    int val = Integer.parseInt(optionAndVal[1]);
                    if(val <= 0){
                        throw new RuntimeException();
                    }
                    options.put(optionAndVal[0], Integer.valueOf(optionAndVal[1]));
                }
            } catch (RuntimeException e){
                System.err.println("Invalid option in line #" + Integer.toString(line) + ". Ignored");
            }
        }
    }

    public int getOption(String optionName){
        if(options.containsKey(optionName)){
            return options.get(optionName);
        } else {
            throw new IllegalArgumentException("Options does not exists.");
        }
    }

}
