package logic.model;

public class Title {
    public enum TitleType{
        BOMB,
        GROUND
    }

    private TitleType type;
    private int x;
    private int y;
    private int numBombsAround;
    private boolean isTerraIncognita;
    private boolean wasChecked;
    private boolean isFlag;

    public Title(int x, int y){
        this.type = TitleType.GROUND;
        this.x = x;
        this.y = y;
        isTerraIncognita = true;
        numBombsAround = 0;
        wasChecked = false;
        isFlag = false;
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

    public boolean wasChecked() {
        return wasChecked;
    }
    public boolean isBomb(){return type == TitleType.BOMB;}
    public boolean isFlag(){return isFlag;}
    public void setFlag(boolean flag){isFlag = flag;}
    public void changeFlag(){isFlag = !isFlag;}
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
