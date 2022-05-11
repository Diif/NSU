package logic.view.GUI;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.Modality;
import javafx.stage.Stage;
import logic.controller.Command;
import logic.controller.GameController;
import logic.model.GameField;
import logic.model.GameModel;
import logic.model.ScoreTable;
import logic.model.Title;


import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.AbstractMap;
import java.util.ArrayList;

public class GUI extends Application implements PropertyChangeListener {
    private Stage primaryStage;
    private HBox layout;
    private VBox menu;
    private GridPane field;
    private ArrayList<TitleButton> buttonArrayList;
    private Label scoreLabel;
    private Label timerLabel;
    private GameField modelField;
    private static GameController controller;
    private static GameModel model;
    int sizeX;

    public static void startGUI(GameModel model, GameController controller){
        assert model != null;
        assert controller != null;
        GUI.model = model;
        GUI.controller = controller;
        System.out.println("Thread startGUI" + Thread.currentThread());
        launch();
    }

    @Override
    public void start(Stage primaryStage){
        primaryStage.setTitle("Minesweeper");
        this.primaryStage = primaryStage;
        model.addListener(this);
        setUpPrimaryStage();
    }

    private void setUpPrimaryStage(){
        assert GUI.model != null;
        assert GUI.controller != null;

        createMenuLayout();
        createFieldLayout();
        createMainLayout();

        Scene scene = new Scene(layout);

        primaryStage.setScene(scene);
        primaryStage.setWidth(600);
        primaryStage.setHeight(600);
        primaryStage.show();
    }

    private void createMenuLayout(){
        menu = new VBox();
        menu.getChildren().add(createStartButton());
        menu.getChildren().add(createRecordsButton());
        menu.getChildren().add(createAboutButton());
        menu.getChildren().add(createExitButton());
        menu.getChildren().add(createTimerAndScoreVBox());
        menu.setMinWidth(100);
    }

    private void createFieldLayout(){
        field = new GridPane();
        field.setAlignment(Pos.CENTER);
        HBox.setHgrow(field, Priority.ALWAYS);
    }

    private void createMainLayout(){
        layout = new HBox();
        layout.getChildren().addAll(field,menu);
        layout.setAlignment(Pos.CENTER_RIGHT);
    }

    private Button createStartButton(){
        Button startButton = new Button("Start");
        startButton.setMaxSize(Double.MAX_VALUE,Double.MAX_VALUE);
        VBox.setVgrow(startButton, Priority.ALWAYS);

        startButton.setOnAction(action -> {
            Stage optionsStage = new Stage();
            optionsStage.setTitle("New game options");

            Label sizeXLabel = new Label("Enter field sizes X:");
            Label sizeYLabel = new Label("Enter field sizes Y:");
            Label bombsLabel = new Label("Enter number of bombs:");
            TextField sizeX = new TextField("9");
            TextField sizeY = new TextField("9");
            TextField numBombs = new TextField("10");
            Button confirmButton = createConfirmButton(sizeX,sizeY,numBombs, optionsStage);

            VBox vBox = new VBox(sizeXLabel, sizeX, sizeYLabel, sizeY, bombsLabel, numBombs,confirmButton);
            vBox.setAlignment(Pos.CENTER);

            optionsStage.setScene(new Scene(vBox));
            optionsStage.initModality(Modality.APPLICATION_MODAL);
            optionsStage.setMinHeight(80);
            optionsStage.setMinWidth(120);
            optionsStage.showAndWait();
        });
        return startButton;
    }

    private Button createConfirmButton(TextField sizeX, TextField sizeY, TextField numBombs, Stage stage){
        Button confirmButton = new Button("Confirm");
        confirmButton.setAlignment(Pos.CENTER);

        confirmButton.setOnAction(action ->{
            try{
                int x = Integer.parseInt(sizeX.getText());
                int y = Integer.parseInt(sizeY.getText());
                int nBombs = Integer.parseInt(numBombs.getText());
                controller.startGame(x,y,nBombs);
                this.sizeX = x;
                timerLabel.setText("0.0");
                scoreLabel.setText("0.0");
                stage.close();
            }catch (Exception e){
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setTitle("Warning");
                alert.setHeaderText(null);
                alert.setContentText("Incorrect options. Try again.");
                alert.showAndWait();
            }
        });
        return confirmButton;
    }

    private Button createRecordsButton(){
        Button recordsButton = new Button("Records");
        recordsButton.setMaxSize(Double.MAX_VALUE,Double.MAX_VALUE);
        VBox.setVgrow(recordsButton, Priority.ALWAYS);

        recordsButton.setOnAction(action -> {
            Stage aboutStage = createRecordStage();
            aboutStage.showAndWait();
        });
        return recordsButton;
    }
    private Stage createRecordStage(){
        Stage aboutStage = new Stage();
        aboutStage.setTitle("Records");


        aboutStage.setScene(new Scene(createRecordVBox()));
        aboutStage.initModality(Modality.APPLICATION_MODAL);
        aboutStage.setMinHeight(80);
        aboutStage.setMinWidth(120);
        return aboutStage;
    }

    private VBox createRecordVBox(){
        Label recordLabel = createRecordLabel();
        TextField inputField = new TextField("Enter score number to delete");
        Button deleteButton = createRecordDeleteButton(inputField, recordLabel);

        VBox vBox = new VBox(recordLabel, inputField, deleteButton);
        vBox.setAlignment(Pos.CENTER);
        return vBox;
    }
    private Button createRecordDeleteButton(TextField inputField, Label recordLabel){
        Button button = new Button("Delete");
        button.setOnAction(actionEvent -> {
            try {
                int num = Integer.parseInt(inputField.getText());
                Command command = Command.getInstance();
                command.setType(Command.CommandType.REMOVE_SCORE);
                command.changeArg("index", num-1);
                controller.processCommand(command);
                recordLabel.setText(createRecordsStr(model.getScoreTable()));
            } catch (Exception e){
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setTitle("Warning");
                alert.setHeaderText(null);
                alert.setContentText("Incorrect number. Try again.");
                alert.showAndWait();
            }
        });
        button.setAlignment(Pos.CENTER);
        return button;
    }
    private Label createRecordLabel(){
        Label aboutLabel = new Label(createRecordsStr(model.getScoreTable()));
        aboutLabel.setAlignment(Pos.CENTER);
        return aboutLabel;
    }

    private String createRecordsStr(ScoreTable scoreTable){
        ArrayList<AbstractMap.SimpleEntry<String, Double>> list = scoreTable.getScores();
        if(list.size() == 0){
            return "No records.";
        }
        StringBuilder str = new StringBuilder();
        int place = 1;
        for (AbstractMap.SimpleEntry<String, Double> se: list) {
            str.append("\t");
            str.append(place);
            str.append(".");
            str.append(se.getKey());
            str.append(" - ");
            str.append(se.getValue());
            str.append("\t\n");
            place++;
        }
        return str.toString();
    }

    private Button createAboutButton(){
        Button aboutButton = new Button("About");
        aboutButton.setMaxSize(Double.MAX_VALUE,Double.MAX_VALUE);
        VBox.setVgrow(aboutButton, Priority.ALWAYS);

        aboutButton.setOnAction( action -> {
            Stage aboutStage = new Stage();
            aboutStage.setTitle("About");
            Label aboutLabel = new Label(GUI.model.getAboutInfo() + "\n\t\tNote: right click to set flag.");
            aboutStage.setScene(new Scene(aboutLabel));
            aboutLabel.setAlignment(Pos.CENTER);
            aboutStage.initModality(Modality.APPLICATION_MODAL);
            aboutStage.showAndWait();
        });
        return aboutButton;
    }

    private Button createExitButton(){
        Button exitButton = new Button("Exit");
        exitButton.setMaxSize(Double.MAX_VALUE,Double.MAX_VALUE);
        VBox.setVgrow(exitButton, Priority.ALWAYS);

        exitButton.setOnAction(action -> {
            Command command = Command.getInstance();
            command.setType(Command.CommandType.SERIALIZE_SCORE);
            controller.processCommand(command);
            System.exit(0);
        });
        return exitButton;
    }

    private VBox createTimerAndScoreVBox(){
        VBox section = new VBox();
        section.setMaxSize(Double.MAX_VALUE,Double.MAX_VALUE);
        VBox.setVgrow(section, Priority.ALWAYS);

        Label timerText = new Label("Timer: ");
        Label scoreText = new Label("Score: ");
        Label timerValue = new Label("0.0");
        Label scoreValue = new Label("0.0");
        timerValue.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        scoreValue.setMaxSize(50,50);

        HBox timer = new HBox();
        timer.setMaxSize(Double.MAX_VALUE,Double.MAX_VALUE);
        HBox.setHgrow(timerValue, Priority.ALWAYS);
        VBox.setVgrow(timer, Priority.ALWAYS);

        HBox score = new HBox();
        score.setMaxSize(Double.MAX_VALUE,Double.MAX_VALUE);
//        HBox.setHgrow(scoreValue, Priority.ALWAYS);
        VBox.setVgrow(score, Priority.ALWAYS);

        timer.getChildren().addAll(timerText, timerValue);
        score.getChildren().addAll(scoreText, scoreValue);

        section.getChildren().addAll(timer,score);
        timerLabel = timerValue;
        scoreLabel = scoreValue;
        return section;
    }

    @Override
    public void propertyChange(PropertyChangeEvent event){
        String name = event.getPropertyName();
        switch (name){
            case "nothingChange" ->{}
            case "timerTick" -> {
                Platform.runLater( () -> {
                    timerLabel.setText(Integer.valueOf(model.getGameTime()).toString());
                    scoreLabel.setText(Double.valueOf(model.getCurScore()).toString());
                });
            }
            case "titleChange", "flagChange" -> {
            Title title =(Title)event.getNewValue();
            updateTitle(title.getX(), title.getY());
            }
            case "fieldChange" -> {updateField();}
            case "stateChange" -> {
                GameModel.StateType type = (GameModel.StateType) event.getNewValue();
                if(type == GameModel.StateType.ACTION) {
                    modelField = model.getField();
                    setUpField();
                } else if(type == GameModel.StateType.DEFEAT){
                    System.out.println("DEFEAT");
                    updateField();
                } else if(type == GameModel.StateType.VICTORY){
                    System.out.println("VICTORY");
                    updateField();
                    askForScore();
                }
            }
        }
    }

    private void setUpField(){
        field.getChildren().clear();
        buttonArrayList = new ArrayList<>();
        int size = modelField.getSize();
        int sizeX = modelField.getSizeX();
        TitleButton.setController(controller);
        int x,y;
        for (int i = 0; i < size; i++){
            x = i % sizeX;
            y = i / sizeX;
            Title title = modelField.getTitle(x,y);
            TitleButton titleButton= new TitleButton(title);
            titleButton.setPrefSize(30, 30);
            titleButton.setMinSize(30,30);
            titleButton.updateIcon();
            field.add(titleButton, x,y);
            buttonArrayList.add(i, titleButton);
        }
    }

    private void updateField(){
        for (TitleButton b: buttonArrayList) {
            b.updateIcon();
        }
    }

    private void updateTitle(int x, int y){
        buttonArrayList.get(y*sizeX + x).updateIcon();
    }

    private void askForScore(){
        Stage stage = new Stage();
        stage.setTitle("Save score?");

        Label nameText = new Label("Enter your name: ");
        TextField nameField = new TextField();
        Button noButton = getNoButton(stage);
        Button yesButton = getYesButton(stage, nameField);

        HBox buttonsBox = new HBox();
        buttonsBox.getChildren().addAll(noButton,yesButton);

        VBox mainBox = new VBox();
        mainBox.getChildren().addAll(nameText, nameField, buttonsBox);

        stage.setScene(new Scene(mainBox));
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.showAndWait();
    }

    private Button getNoButton(Stage stage){
        Button noButton = new Button("No");
        noButton.setMaxSize(Double.MAX_VALUE,Double.MAX_VALUE);
        HBox.setHgrow(noButton, Priority.ALWAYS);

        noButton.setOnAction(action -> {
            stage.close();
        });
        return noButton;
    }

    private Button getYesButton(Stage stage, TextField name){
        Button yesButton = new Button("Yes");
        yesButton.setMaxSize(Double.MAX_VALUE,Double.MAX_VALUE);
        HBox.setHgrow(yesButton, Priority.ALWAYS);

        yesButton.setOnAction(action -> {
            Command command = Command.getInstance();
            command.setType(Command.CommandType.SAVE_SCORE);
            command.changeArg("name", name.getText());
            command.changeArg("score", model.getCurScore());
            controller.processCommand(command);
            stage.close();
        });

        return yesButton;
    }

}