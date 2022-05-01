package logic.model;

public class IncorrectCoordsException extends RuntimeException{
    public IncorrectCoordsException(int x, int y, int sizeX, int sizeY){
        super("Coords (" +x+","+y+") are incorrect in field with size "+sizeX+"x"+sizeY+".");
    }
}
