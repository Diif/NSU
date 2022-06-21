package model.confighandler;

public class InvalidConfigFIle extends Exception{
    InvalidConfigFIle(int line){
        super("Invalid config file. Problems in line #"+ Integer.toString(line) + ".");
    }
}
