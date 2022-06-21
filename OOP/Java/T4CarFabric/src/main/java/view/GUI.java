package view;

import controller.Command;
import controller.Controller;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Orientation;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import model.GameModel;
import model.confighandler.ConfigHandler;

import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

public class GUI extends Application {
    private static GameModel model;
    private static Controller controller;
    private ArrayList<UpdateTask> updateTasks;
    private Timer timer;
    private Stage primaryStage;
    private final int MAX_SLIDER_DELAY = 5000;

    public static void startGUI(GameModel model, Controller controller){
        assert model != null;
        assert controller != null;
        GUI.model = model;
        GUI.controller = controller;
        launch();
    }

    @Override
    public void start(Stage primaryStage){
        primaryStage.setTitle("Fabric information");
        this.primaryStage = primaryStage;
        fillPrimaryStage();
        initTimer();
    }

    @Override
    public void stop(){
        timer.cancel();
        timer.purge();
        model.interruptProduction();
    }

    private void fillPrimaryStage(){
        updateTasks = new ArrayList<>();
        HBox layout = new HBox();
        Scene scene = new Scene(layout);

        VBox supSettings = createSettingsVBox();
        VBox storageInfo = createStorageInfoVBox();
        VBox carInfoVBox = createCarInfoVBox();
        VBox dealerSettingVBox = createDealerSettingVBox();

        HBox.setHgrow(supSettings, Priority.ALWAYS);
        HBox.setHgrow(storageInfo, Priority.ALWAYS);
        HBox.setHgrow(carInfoVBox, Priority.ALWAYS);
        HBox.setHgrow(dealerSettingVBox, Priority.ALWAYS);

        layout.getChildren().addAll(supSettings, storageInfo,carInfoVBox,dealerSettingVBox);
        primaryStage.setScene(scene);
        primaryStage.show();

//        primaryStage.on

    }

    private VBox createSettingsVBox(){
        Label supBody = new Label("Body supplier delay");
        Slider sliderBody = new Slider(100, Math.max(model.getSupplierBodyDelay(), MAX_SLIDER_DELAY), model.getSupplierBodyDelay());
        Label sliderBodyVal = new Label(String.valueOf(sliderBody.getValue()));
        sliderBody.valueProperty().addListener((obsVal, oldVal, newVal) ->{
            sliderBodyVal.setText(String.valueOf(newVal.intValue()));
            Command command = Command.getInstance();
            command.setType(Command.CommandType.BODY_DELAY);
            command.setValue(newVal.intValue());
            controller.executeCommand(command);
        });

        Label supEngine = new Label("Engine supplier delay");
        Slider sliderEngine = new Slider(100, Math.max(model.getSupplierEngineDelay(), MAX_SLIDER_DELAY), model.getSupplierEngineDelay());
        Label sliderEngineVal = new Label(String.valueOf(sliderEngine.getValue()));
        sliderEngine.valueProperty().addListener((obsVal, oldVal, newVal) -> {
            sliderEngineVal.setText(String.valueOf(newVal.intValue()));
            Command command = Command.getInstance();
            command.setType(Command.CommandType.ENGINE_DELAY);
            command.setValue(newVal.intValue());
            controller.executeCommand(command);
        });

        Label supAccessory = new Label("Body supplier delay");
        Slider sliderAccessory = new Slider(100, Math.max(model.getSupplierAccessoryDelay(), MAX_SLIDER_DELAY), model.getSupplierAccessoryDelay());
        Label sliderAccessoryVal = new Label(String.valueOf(sliderAccessory.getValue()));
        sliderAccessory.valueProperty().addListener((obsVal, oldVal, newVal) -> {
            sliderAccessoryVal.setText(String.valueOf(newVal.intValue()));
            Command command = Command.getInstance();
            command.setType(Command.CommandType.ACCESSORY_DELAY);
            command.setValue(newVal.intValue());
            controller.executeCommand(command);
        });

        VBox vBox = new VBox(supBody, sliderBody,sliderBodyVal, supEngine, sliderEngine, sliderEngineVal, supAccessory, sliderAccessory, sliderAccessoryVal);
        VBox.setVgrow(supBody, Priority.ALWAYS);
        VBox.setVgrow(sliderBody, Priority.ALWAYS);
        VBox.setVgrow(sliderBodyVal, Priority.ALWAYS);
        VBox.setVgrow(supEngine, Priority.ALWAYS);
        VBox.setVgrow(sliderEngine, Priority.ALWAYS);
        VBox.setVgrow(sliderEngineVal, Priority.ALWAYS);
        VBox.setVgrow(supAccessory, Priority.ALWAYS);
        VBox.setVgrow(sliderAccessory, Priority.ALWAYS);
        VBox.setVgrow(sliderAccessoryVal, Priority.ALWAYS);
        vBox.setAlignment(Pos.CENTER);
        String cssLayout = "-fx-border-color: red;\n" +
                "-fx-border-insets: 5;\n" +
                "-fx-border-width: 3;\n" +
                "-fx-border-style: dashed;\n";
        vBox.setStyle(cssLayout);

        return vBox;
    }

    private VBox createStorageInfoVBox(){
        Label strBody = new Label("Body storage info:");
        Label strBodyCapacity = new Label("Capacity: " + model.getBodyStorageCapacity());
        Label strBodySize = new Label("Bodies count: " + 0);
        Label strBodyTotal = new Label("Bodies total: " + 0);
        updateTasks.add(() -> {
            strBodySize.setText("Bodies count: " + model.getBodyStorageSize());
            strBodyTotal.setText("Bodies total: " + model.getTotalBodiesCount());
        });

        Label strEngine = new Label("Engine storage info:");
        Label strEngineCapacity = new Label("Capacity: " + model.getEngineStorageCapacity());
        Label strEngineSize = new Label("Engines count: " + 0);
        Label strEngineTotal = new Label("Engines total: " + 0);
        updateTasks.add(() -> {
            strEngineSize.setText("Engines count: " + model.getEngineStorageSize());
            strEngineTotal.setText("Engines total: " + model.getTotalEnginesCount());
        });

        Label strAccessory = new Label("Accessory storage info:");
        Label strAccessoryCapacity = new Label("Capacity: " + model.getAccessoryStorageCapacity());
        Label strAccessorySize = new Label("Accessories count: " + 0);
        Label strAccessoryTotal = new Label("Accessories total: " + 0);
        updateTasks.add(() -> {
            strAccessorySize.setText("Accessories count: " + model.getAccessoryStorageSize());
            strAccessoryTotal.setText("Accessories total: " + model.getTotalAccessoriesCount());
        });

        strBodyTotal.setPadding(new Insets(0,0,25,0));
        strEngineTotal.setPadding(new Insets(0,0,25,0));

        VBox vBox = new VBox(strBody, strBodyCapacity, strBodySize, strBodyTotal, strEngine, strEngineCapacity, strEngineSize,strEngineTotal, strAccessory, strAccessoryCapacity, strAccessorySize, strAccessoryTotal);

        VBox.setVgrow(strBody, Priority.ALWAYS);
        VBox.setVgrow(strBodyCapacity, Priority.ALWAYS);
        VBox.setVgrow(strBodySize, Priority.ALWAYS);
        VBox.setVgrow(strBodyTotal, Priority.ALWAYS);
        VBox.setVgrow(strEngine, Priority.ALWAYS);
        VBox.setVgrow(strEngineCapacity, Priority.ALWAYS);
        VBox.setVgrow(strEngineSize, Priority.ALWAYS);
        VBox.setVgrow(strEngineTotal, Priority.ALWAYS);
        VBox.setVgrow(strAccessory, Priority.ALWAYS);
        VBox.setVgrow(strAccessoryCapacity, Priority.ALWAYS);
        VBox.setVgrow(strAccessorySize, Priority.ALWAYS);
        VBox.setVgrow(strAccessoryTotal, Priority.ALWAYS);
        vBox.setAlignment(Pos.CENTER);


        return vBox;
    }

    private VBox createCarInfoVBox(){
        Label manufactory = new Label("Manufactory orders count:");
        Label ordersCount = new Label(String.valueOf(model.getManufactoryTaskCount()));

        Label storageCar = new Label("Cars storage info:");
        Label strCapacity = new Label("Capacity: " + model.getCarStorageCapacity());
        Label curCars = new Label("Cars in storage: " + model.getCarStorageSize());
        Label totalCars = new Label("Cars total: " + model.getTotalCarsCount());

        updateTasks.add(() -> {
            ordersCount.setText(String.valueOf(model.getManufactoryTaskCount()));
            curCars.setText("Cars in storage: " + model.getCarStorageSize());
            totalCars.setText("Cars total: " + model.getTotalCarsCount());
        });

        VBox vBox = new VBox(manufactory,ordersCount,storageCar,strCapacity, curCars,totalCars);
        VBox.setVgrow(manufactory,Priority.ALWAYS);
        VBox.setVgrow(ordersCount,Priority.ALWAYS);
        ordersCount.setPadding(new Insets(0,0,25,0));
        VBox.setVgrow(totalCars,Priority.ALWAYS);
        vBox.setAlignment(Pos.CENTER);
        return vBox;
    }

    private VBox createDealerSettingVBox(){
        Label info = new Label("Dealers delay");
        Slider slider = new Slider(100, Math.max(model.getDealersDelay(), MAX_SLIDER_DELAY),model.getDealersDelay());
        slider.setOrientation(Orientation.VERTICAL);
        Label sliderVal = new Label(String.valueOf(slider.getValue()));

        slider.valueProperty().addListener((obsVal, oldVal,newVal) -> {
            sliderVal.setText(String.valueOf(newVal.intValue()));
            Command command = Command.getInstance();
            command.setType(Command.CommandType.DEALER_DELAY);
            command.setValue(newVal.intValue());
            controller.executeCommand(command);
        });

        VBox vBox = new VBox(info,slider, sliderVal);
        VBox.setVgrow(info,Priority.ALWAYS);
        VBox.setVgrow(slider,Priority.ALWAYS);
        VBox.setVgrow(sliderVal, Priority.ALWAYS);
        vBox.setAlignment(Pos.CENTER);

        return vBox;
    }

    private void initTimer(){
        timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                Platform.runLater(() -> {
                    for(UpdateTask task : updateTasks){
                        task.update();
                    }
                });
            }
        },1000,1000);
    }
}
