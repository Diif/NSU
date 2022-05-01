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
        titles[i] = new Title(i % sizeY, i / sizeY);
        }
    }

    public void generateGameField(int numBombs){
        if (numBombs > size){
            numBombs = size;
        }
        Random rand = new Random();
        for (int i = 0; i < numBombs; i++){
            int place =rand.nextInt(size);
            titles[place].setType(Title.TitleType.BOMB);
            addBombToNeighbors(place % sizeY, place / sizeY);
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

    public void moveBomb(int x, int y){
        Title title = this.getTitle(x,y);
        title.setType(Title.TitleType.GROUND);
        removeBombFromNeighbors(x,y);

        Random rand = new Random();
        int place = rand.nextInt(size);
        int newX = place % sizeY, newY = place / sizeY;
        title = this.getTitle(newX,newY);
        while ((newX == x && newY == y) || title.getType() == Title.TitleType.BOMB){
            place = rand.nextInt(size);
            newX = place % sizeY;
            newY = place / sizeY;
            title = this.getTitle(newX,newY);
        }
        title.setType(Title.TitleType.BOMB);
        addBombToNeighbors(newX, newY);
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
}
