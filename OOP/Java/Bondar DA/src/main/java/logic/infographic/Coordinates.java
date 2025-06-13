package logic.infographic;

public class Coordinates {
    private int x;
    private int y;

    public int getX() {
        return x;
    }

    private void changeCoordsByDirection(Direction direction){
        switch (direction){
            case TOP:
                this.setY(this.getY() - 1);
                break;
            case BOT:
                this.setY(this.getY() + 1);
                break;
            case LEFT:
                this.setX(this.getX() - 1);
                break;
            case RIGHT:
                this.setX(this.getX() + 1);
                break;
            case NONE:
                break;
        }
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public Coordinates(int x, int y){
        this.x = x;
        this.y = y;
    }
}
