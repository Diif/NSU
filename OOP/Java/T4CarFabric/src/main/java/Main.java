import controller.Controller;
import model.GameModel;
import view.GUI;

public class Main {
    public static void main(String[] argc){
        GameModel model = new GameModel();
        Controller controller = new Controller(model);
        model.loadConfig("config.txt");
        model.initModel();
        model.startProduction();
        GUI.startGUI(model,controller);
    }
}
