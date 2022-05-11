package logic.view.GUI;

import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.input.MouseButton;
import logic.controller.Command;
import logic.controller.GameController;
import logic.model.Title;

import javafx.scene.image.ImageView;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class TitleButton extends Button {
    private final static Image flagImage;
    private final static Image bombImage;
    private static GameController controller;
    private final Title title;

    static{
        FileInputStream input = null;
        try {
            input = new FileInputStream("res/flag.png");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        assert input!=null;
        flagImage = new Image(input, 25,25,false,false);

        input = null;
        try {
            input = new FileInputStream("res/mine.png");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        assert input!=null;
        bombImage = new Image(input, 25,25,false,false);
    }

    public TitleButton(Title title){
        assert controller != null;
        assert title != null;
        this.title = title;
        this.setOnMouseClicked(action ->{
            Command command = Command.getInstance();
            if(action.getButton() == MouseButton.SECONDARY){
                command.setType(Command.CommandType.FLAG);
            } else {
                command.setType(Command.CommandType.CLICK);
            }
            command.changeArg("x", title.getX());
            command.changeArg("y", title.getY());
            controller.processCommand(command);
        });
    }

    public void updateIcon(){
        boolean terraIncognita = title.isTerraIncognita();
        if(title.isFlag() && terraIncognita){
            this.setGraphic(new ImageView(flagImage));
            return;
        }
        if(title.isTerraIncognita()){
            this.setGraphic(null);
        } else {
            if(title.isBomb()){
                this.setGraphic(new ImageView(bombImage));
            }else {
                this.setGraphic(null);
                this.setText(Integer.valueOf(title.getNumBombsAround()).toString());
            }
        }
    }

    public static void setController(GameController controller) {
        TitleButton.controller = controller;
    }

}
