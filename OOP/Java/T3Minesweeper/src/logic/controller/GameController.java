package logic.controller;

import logic.model.*;

public final class GameController {

    private GameModel model;

    public void setModel(GameModel model) {
        this.model = model;
    }

    public void processCommand(Command command){
        Command.CommandType type = command.getType();
        switch (type){
            case CLICK -> model.processClick((Integer)command.getArg("x"),(Integer)command.getArg("y"));
            case FLAG -> model.changeFlag((Integer)command.getArg("x"),(Integer)command.getArg("y"));
            case EXIT_TO_MENU -> closeGame();
            case SAVE_SCORE -> {
                ScoreTable scores = model.getScoreTable();
                scores.addScore((String)command.getArg("name"),(Double) command.getArg("score"));
            }
            case REMOVE_SCORE -> {
                ScoreTable scores = model.getScoreTable();
                scores.removeScore((Integer)command.getArg("index"));
            }
            case SERIALIZE_SCORE -> {
                ScoreTable scoreTable = model.getScoreTable();
                scoreTable.serializeScores();
            }
            case INCORRECT -> {
                System.err.println("Internal error. Exiting...");
                System.exit(1);
            }
        }
    }

    public void startGame(int fieldLen, int fieldHeight, int numBombs) throws IncorectGameOptions {
        model.startNewGame(fieldLen,fieldHeight,numBombs);
    }

    private void closeGame(){
        model.closeTimer();
        model.setStateAndNotify(GameModel.StateType.CLOSED);
    }

}

