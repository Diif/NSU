package model.confighandler;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

public class ConfigHandler {
    private HashMap<String, Integer> options;
    private final int DEFAULT_STORAGE_SIZE=100;
    private final int DEFAULT_ACCESSORY_SUPPLIES=2;
    private final int DEFAULT_WORKERS=3;
    private final int DEFAULT_DEALERS=2;
    private final int DEFAULT_LOG_MODE = 0;

    public ConfigHandler(){
        options = new HashMap<>();
        options.put("storageBodySize", DEFAULT_STORAGE_SIZE);
        options.put("storageEngineSize", DEFAULT_STORAGE_SIZE);
        options.put("storageAccessorySize", DEFAULT_STORAGE_SIZE);
        options.put("storageCarSize", DEFAULT_STORAGE_SIZE);
        options.put("accessorySupplies", DEFAULT_ACCESSORY_SUPPLIES);
        options.put("workers", DEFAULT_WORKERS);
        options.put("dealers", DEFAULT_DEALERS);
        options.put("logMode", DEFAULT_LOG_MODE);
    }

    public void loadConfigOptions(String pathname){
        Scanner scanner;
        try {
            scanner = new Scanner(new File(pathname));
        } catch (FileNotFoundException e){
            System.err.println("Can't open config. Default setting applied.\n" +
                    "\tstorageBodySize=" +DEFAULT_STORAGE_SIZE+'\n'+
                    "\tstorageEngineSize=" +DEFAULT_STORAGE_SIZE+'\n'+
                    "\tstorageAccessorySize=" +DEFAULT_STORAGE_SIZE+'\n'+
                    "\tstorageCarSize=" +DEFAULT_STORAGE_SIZE+'\n'+
                    "\taccessorySupplies=" +DEFAULT_ACCESSORY_SUPPLIES+'\n'+
                    "\tworkers=" +DEFAULT_WORKERS+'\n'+
                    "\tdealers=" +DEFAULT_DEALERS+'\n'+
                    "\tlogMode="+DEFAULT_LOG_MODE);
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
