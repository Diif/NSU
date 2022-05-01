package logic.model;

public class IncorectGameOptions extends Exception{
    public IncorectGameOptions(int len, int height, int numBombs){
        super("Can't initialize game with length " + len + ", height " + height+", bombs " + numBombs +".");
    }
}