package logic.model;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.Timer;
import java.util.TimerTask;

public class GameModel{
    public enum StateType{
        DEFEAT, ACTION, VICTORY
    }


    private int gameTime;
    private int fieldSizeX;
    private int fieldSizeY;
    private int numBombs;
    private int baseScore;
    private double curScore;
    private int titlesForWin;
    private boolean isFirstClick;
    private StateType gameState;
    private GameField field;
    private Timer timer;
    private PropertyChangeSupport changeSupport;

    public void addListener(PropertyChangeListener listener){
        changeSupport.addPropertyChangeListener(listener);
    }

    public void removeListener(PropertyChangeListener listener){
        changeSupport.removePropertyChangeListener(listener);
    }

    public void startNewGame(int fieldLen, int fieldHeight, int numBombs) throws IncorectGameOptions {
        if(fieldLen <= 0 || fieldHeight <= 0 || numBombs <= 0 || fieldHeight * fieldLen <= numBombs){
            throw new IncorectGameOptions(fieldLen, fieldHeight, numBombs);
        }
        gameTime = 0;
        gameState = StateType.ACTION;
        fieldSizeX = fieldLen;
        fieldSizeY = fieldHeight;
        titlesForWin = fieldSizeX * fieldSizeY - numBombs;
        baseScore =  fieldSizeX * fieldSizeY - numBombs;
        curScore = baseScore;
        isFirstClick = true;
        this.numBombs = numBombs;

        timer = new Timer();
        field = new GameField(fieldSizeX, fieldSizeY);
        field.generateGameField(numBombs);

    }

    public void processClick(int x, int y){
        if(x < 0 || y < 0 || x >= fieldSizeX || y >= fieldSizeY || gameState != StateType.ACTION){
            return;
        }
        Title title = field.getTitle(x,y);
        if(!title.isTerraIncognita()){
            return;
        }
        baseScore--;
        if(title.getType() == Title.TitleType.BOMB){
            if(isFirstClick){
                field.moveBomb(x,y);
            } else {
                gameState = StateType.DEFEAT;
                field.openTitles();
                changeSupport.firePropertyChange("gameState", StateType.ACTION, StateType.DEFEAT);
                return;
            }
        }
        openLocality(x,y);
        if(isFirstClick) {
            startGameTimer();
            isFirstClick = false;
        }
        if (titlesForWin == 0){
            gameState = StateType.VICTORY;
            field.openTitles();
            changeSupport.firePropertyChange("gameState", StateType.ACTION, StateType.VICTORY);
        }

    }

    private void recalculateScore(){
        curScore = (double) baseScore / gameTime;
    }

    private void startGameTimer(){
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                gameTime++;
                recalculateScore();
                changeSupport.firePropertyChange("timerTick", 0, gameTime);
            }
        };
        timer.schedule(task, 1,1);
    }

    private void openLocality(int titleX, int titleY){
        if(titleX < 0 || titleY < 0 || titleX >= fieldSizeX || titleY >= fieldSizeY){
            return;
        }
        Title title = field.getTitle(titleX, titleY);
        if (title.isWasChecked()){
            return;
        }
        title.setWasChecked(true);
        title.setTerraIncognita(false);
        changeSupport.firePropertyChange("titleChange", null, title);
        titlesForWin--;
        if(title.getNumBombsAround() > 0 || titlesForWin == 0){
            return;
        }
        for(int y = titleY - 1, i = 0; i < 3; i++, y++){
            for (int x = titleX -1, j = 0; j < 3; j++, x++){
                openLocality(x,y);
            }
        }
        title.setWasChecked(false);
    }

    public double getCurScore() {
        return curScore;
    }

    public GameField getField() {
        return field;
    }

    public int getGameTime() {
        return gameTime;
    }

    public StateType getGameState() {
        return gameState;
    }
}
