package logic.model;

import java.util.Random;

public class GameField {
    private final Title[] titles;
    private final int sizeX;
    private final int sizeY;
    private final int size;

    public GameField(int sizeX, int sizeY){
        this.sizeX = sizeX;
        this.sizeY = sizeY;
        this.size = sizeX*sizeY;
        titles = new Title[size];
    for (int i = 0; i < size; i++){
        titles[i] = new Title(i % sizeX, i / sizeX);
        }
    }

    public void generateGameField(int numBombs){
        if (numBombs > size){
            numBombs = size;
        }
        for (int i = 0; i < numBombs; i++){
            addBombToNewRandomPlace();
        }
    }

    public void openTitles(){
        for (int i = 0; i < size; i++){
            titles[i].setTerraIncognita(false);
        }
    }

    public Title getTitle(int x, int y){
        if(x >= sizeX || y >=sizeY){
            throw new IncorrectCoordsException(x,y, sizeX, sizeY);
        }
        return titles[x + y*sizeX];
    }

    private void addBombToNewRandomPlace(){
        Random rand = new Random();
        Title title;
        int place, x, y;
        while(true) {
            place = rand.nextInt(size);
            x = place % sizeX;
            y = place / sizeX;
            title = this.getTitle(x,y);
            if(!title.isBomb()){
                title.setType(Title.TitleType.BOMB);
                addBombToNeighbors(x, y);
                break;
            }
        }
    }

    public void moveBomb(int x, int y){
        addBombToNewRandomPlace();
        Title title = this.getTitle(x,y);
        title.setType(Title.TitleType.GROUND);
        removeBombFromNeighbors(x,y);
    }

    public void moveBomb(Title title){
        addBombToNewRandomPlace();
        title.setType(Title.TitleType.GROUND);
        removeBombFromNeighbors(title.getX(),title.getY());
    }

    private void addBombToNeighbors(int x, int y){
        if(x >= sizeX || y >=sizeY){
            throw new IncorrectCoordsException(x,y, sizeX, sizeY);
        }
        x--;
        y--;
        int startX = x;
        for (int i = 0; i < 3; i++,y++){
            if(y <0){
                continue;
            }
            if(y >= sizeY){
                break;
            }
            for (int j = 0; j < 3; j++,x++){
                if(x < 0){
                    continue;
                }
                if(x >= sizeX){
                    break;
                }
                Title title = getTitle(x,y);
                title.increaseNumBombsAround();
            }
            x = startX;
        }
    }

    private void removeBombFromNeighbors(int x, int y){
        if(x >= sizeX || y >=sizeY){
            throw new IncorrectCoordsException(x,y, sizeX, sizeY);
        }
        x--;
        y--;
        int startX = x;
        for (int i = 0; i < 3; i++,y++){
            if(y <0){
                continue;
            }
            if(y >= sizeY){
                break;
            }
            for (int j = 0; j < 3; j++,x++){
                if(x < 0){
                    continue;
                }
                if(x >= sizeX){
                    break;
                }
                Title title = getTitle(x,y);
                title.decreaseNumBombsAround();
            }
            x = startX;
        }
    }


    public int getSizeX() {
        return sizeX;
    }

    public int getSizeY() {
        return sizeY;
    }

    public int getSize() {
        return size;
    }
}
