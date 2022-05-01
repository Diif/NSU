package logic.model;

public class Title {
    public enum TitleType{
        BOMB,
        GROUND
    }

    private TitleType type;
    int x;
    int y;
    private int numBombsAround;
    private boolean isTerraIncognita;
    private boolean wasChecked;

    public Title(int x, int y){
        this.type = TitleType.GROUND;
        this.x = x;
        this.y = y;
        isTerraIncognita = true;
        numBombsAround = 0;
        wasChecked = false;
    }

    public TitleType getType(){
        return  type;
    }

    public int getNumBombsAround() {
        return numBombsAround;
    }

    public boolean isTerraIncognita() {
        return isTerraIncognita;
    }

    public boolean isWasChecked() {
        return wasChecked;
    }
    public void setType(TitleType type) {
        this.type = type;
    }

    public void setNumBombsAround(int numBombsAround) {
        this.numBombsAround = numBombsAround;
    }

    public void increaseNumBombsAround(){
        this.numBombsAround++;
    }

    public void decreaseNumBombsAround(){
        this.numBombsAround--;
    }

    public void setTerraIncognita(boolean terraIncognita) {
        isTerraIncognita = terraIncognita;
    }

    public void setWasChecked(boolean wasChecked) {
        this.wasChecked = wasChecked;
    }

    public int getX() {
        return x;
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
}
