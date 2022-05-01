package logic.controller;

import logic.model.*;

public final class GameController {
    private GameModel model;

    public void setModel(GameModel model) {
        this.model = model;
    }

    void ProcessClick(int x, int y){
        model.processClick(x,y);
    }

}

