import controller.Controller;
import model.GameModel;
import view.GUI;

public class Main {
    private static final String CONFIG_PATH="resources/config.cfg";
    public static void main(String[] argc){
        GameModel model = new GameModel();
        Controller controller = new Controller(model);
        model.loadConfig(CONFIG_PATH);
        model.initModel();
        model.startProduction();
        GUI.startGUI(model,controller);
    }
}
