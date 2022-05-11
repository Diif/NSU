package logic.model;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

public class GameModel{
    public enum StateType{
        ACTION, DEFEAT, VICTORY, CLOSED
    }

    private int gameTime;
    private int fieldSizeX;
    private int fieldSizeY;
    private int baseScore;
    private double curScore;
    private int titlesForWin;
    private boolean isFirstClick;
    private boolean timerClosed;
    private final String aboutInfo;
    private StateType gameState;
    private GameField field;
    private Timer timer;
    private final PropertyChangeSupport changeSupport;
    private final ScoreTable scores;


    public GameModel(){
        aboutInfo = "\t\tWelcome to Minesweeper!\n\t1) Click on titles to open them.\n\t2) Numbers show count of bombs around (3x3 area).\n\t3) Try not to blow up!";
        changeSupport = new PropertyChangeSupport(this);
        timerClosed = true;
        scores = new ScoreTable();
        scores.initScores();
    }

    public void closeTimer(){
        timerClosed = true;
        timer.cancel();
        timer.purge();
    }

    public void setStateAndNotify(StateType state){
        gameState = state;
        changeSupport.firePropertyChange("stateChange", null, state);
    }

    public void addListener(PropertyChangeListener listener){
        changeSupport.addPropertyChangeListener(listener);
    }

    public void removeListener(PropertyChangeListener listener){
        changeSupport.removePropertyChangeListener(listener);
    }

    public void startNewGame(int fieldLen, int fieldHeight, int numBombs) throws IncorectGameOptions {
        if(fieldLen <= 0 || fieldHeight <= 0 || numBombs <= 0 || fieldHeight * fieldLen <= numBombs + 1 || fieldLen > 58 || fieldHeight > 34){
            throw new IncorectGameOptions(fieldLen, fieldHeight, numBombs);
        }
        gameState = StateType.ACTION;
        fieldSizeX = fieldLen;
        fieldSizeY = fieldHeight;
        titlesForWin = fieldSizeX * fieldSizeY - numBombs;
        baseScore =  fieldSizeX * fieldSizeY - numBombs;
        curScore = baseScore;
        isFirstClick = true;

        if(!timerClosed){
            closeTimer();
        }
        timer = new Timer();
        gameTime = 0;
        field = new GameField(fieldSizeX, fieldSizeY);
        field.generateGameField(numBombs);
        setStateAndNotify(StateType.ACTION);
    }

    private boolean canIgnoreClick(int x, int y){
        if(x < 0 || y < 0 || x >= fieldSizeX || y >= fieldSizeY || gameState != StateType.ACTION){
            changeSupport.firePropertyChange("nothingChange", null, null);
            return true;
        }
        Title title = field.getTitle(x,y);
        if(!title.isTerraIncognita() || title.isFlag()){
            changeSupport.firePropertyChange("nothingChange", null, null);
            return true;
        }
        return false;
    }

    private boolean isVictory(){
        if (titlesForWin == 0){
            gameState = StateType.VICTORY;
            field.openTitles();
            closeTimer();
            setStateAndNotify(StateType.VICTORY);
            return true;
        }
        return false;
    }

    private void clickTitle(Title title){
        if(title.getType() == Title.TitleType.BOMB){
            if(isFirstClick) {
                field.moveBomb(title);
            } else {
                clickBomb();
                return;
            }
        }
        int x = title.getX();
        int y = title.getY();
        openLocality(x,y);
        if(isFirstClick) {
            startGameTimer();
            isFirstClick = false;
        }
        if(!isVictory()) {
            changeSupport.firePropertyChange("fieldChange", null, title);
        }
    }

    private void clickBomb(){
            field.openTitles();
            setStateAndNotify(StateType.DEFEAT);
            closeTimer();
    }

    public void changeFlag(int x, int y){
        Title title =field.getTitle(x,y);
        title.changeFlag();
        changeSupport.firePropertyChange("flagChange", null, title);
    }

    public ScoreTable getScoreTable() {
        return scores;
    }

    public void processClick(int x, int y){
        boolean canIgnore = canIgnoreClick(x,y);
        if(canIgnore){
            return;
        }

        Title title = field.getTitle(x,y);
        baseScore--;
        clickTitle(title);
    }

    private void recalculateScore(){
        curScore = (double) baseScore / gameTime;
    }

    private void startGameTimer(){
        timerClosed = false;
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                gameTime++;
                recalculateScore();
                changeSupport.firePropertyChange("timerTick", 0, gameTime);
            }
        };
        timer.schedule(task, 1000,1000);
    }

    private void recursiveOpenNeighbors(int titleX, int titleY, ArrayList<Title> titleArrayList){
        if(titleX < 0 || titleY < 0 || titleX >= fieldSizeX || titleY >= fieldSizeY){
            return;
        }
        Title title = field.getTitle(titleX, titleY);
        if (title.wasChecked()){
            return;
        }
        title.setWasChecked(true);
        titleArrayList.add(title);
        if(title.isBomb() || !title.isTerraIncognita()){
            return;
        }
        title.setTerraIncognita(false);
        changeSupport.firePropertyChange("titleChange", null, title);
        titlesForWin--;
        if(title.getNumBombsAround() > 0 || titlesForWin == 0){
            return;
        }
        for(int y = titleY - 1, i = 0; i < 3; i++, y++){
            for (int x = titleX -1, j = 0; j < 3; j++, x++){
                recursiveOpenNeighbors(x,y, titleArrayList);
            }
        }
    }

    private void openLocality(int titleX, int titleY){
        ArrayList<Title> titleArrayList = new ArrayList<>();
        recursiveOpenNeighbors(titleX,titleY, titleArrayList);
        for (Title t : titleArrayList) {
            t.setWasChecked(false);
        }
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
    public String getAboutInfo() {
        return aboutInfo;
    }
}
