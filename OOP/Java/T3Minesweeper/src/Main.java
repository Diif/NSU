import logic.view.GUI.GUI;
import logic.model.GameModel;
import logic.controller.GameController;
import logic.view.TextUI;

public class Main {
    public static void main(String[] args){
        GameModel model = new GameModel();
        GameController gc = new GameController();
        gc.setModel(model);
        if(args.length == 1) {
            GUI.startGUI(model, gc);
        } else {
            TextUI ui = new TextUI();
            gc.setModel(model);
            ui.setModel(model);
            ui.setController(gc);
            ui.menuSection();
        }
    }
}
