package logic.infographic;

public class DetailRepresentation {
    private Coordinates connectionCoords;
    private Coordinates coords;
    private Direction direction;
    private int id;
    private boolean isPlaced;
    private int length;
    private char symb;


    public DetailRepresentation(int length, char symb, int id){
        isPlaced = false;
        this.length = length;
        this.symb = symb;

        coords = new Coordinates(-1,-1);
        connectionCoords = new Coordinates(-1,-1);
        direction = Direction.NONE;
    }

    public int getId() {
        return id;
    }

    public int getLength() {
        return length;
    }

    public char getSymb() {
        return symb;
    }


    public Coordinates getCoords() {
        return coords;
    }

    public void setCoords(Coordinates coords) {
        this.coords = coords;
    }

    public Coordinates getConnectionCoords() {
        return connectionCoords;
    }

    public void setConnectionCoords(Coordinates connectionCoords) {
        this.connectionCoords = connectionCoords;
    }

    public void setParentCoords(int x, int y) {
        connectionCoords.setX(x);
        connectionCoords.setY(y);
    }

    public void setCoords(int x, int y) {
        coords.setX(x);
        coords.setY(y);
    }

    public Direction getDirection() {
        return direction;
    }

    public void setDirection(Direction direction) {
        this.direction = direction;
    }

    public boolean isPlaced() {
        return isPlaced;
    }

    public void setPlaced(boolean placed) {
        isPlaced = placed;
    }

}
