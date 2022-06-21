package controller;

import model.GameModel;

public class Controller {
    private final GameModel model;
    public Controller(GameModel model){
        assert model != null;
        this.model = model;
    }

    public void executeCommand(Command command){
        Command.CommandType type = command.getType();
        switch (type){
            case BODY_DELAY -> model.setSupplierBodyDelay(command.getValue());
            case ENGINE_DELAY -> model.setSupplierEngineDelay(command.getValue());
            case ACCESSORY_DELAY -> model.setSupplierAccessoryDelay(command.getValue());
            case DEALER_DELAY -> model.setDealersDelay(command.getValue());
            case INCORRECT -> System.err.println("Controller command error");
        }
    }

}
