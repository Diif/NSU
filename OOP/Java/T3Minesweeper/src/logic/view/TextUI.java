package logic.view;

import logic.controller.Command;
import logic.controller.GameController;
import logic.model.*;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.Scanner;

public class TextUI implements PropertyChangeListener{
    private GameModel model;
    private GameController controller;
    private final Scanner scanner;
    private int sizeX;
    private int sizeY;
    private GameField field;

    public TextUI(){
        scanner = new Scanner(System.in);
        model = null;
    }

    public void setModel(GameModel model){
        if(this.model != null){
            model.removeListener(this);
        }
        this.model = model;
        assert model != null;
        model.addListener(this);
    }

    public void setController(GameController controller){
        this.controller = controller;
    }

    public void menuSection(){
        assert model != null;
        assert controller != null;
        while (true){
            printMenu();
            String input = scanner.next();
            switch (input) {
                case "1" -> initNewGame();
                case "2" -> recordsSection();
                case "3" -> aboutSection();
                case "4" -> exitGame();
            }
        }
    }

    private void printMenu(){
        System.out.println("\t\t******Minesweeper menu******");
        System.out.println("\t1. Start new game.");
        System.out.println("\t2. Records.");
        System.out.println("\t3. About.");
        System.out.println("\t4. Exit.");
        System.out.println("\t\t\t********************");
    }

    private void initNewGame(){
        int fieldLen, fieldHeight, numBombs;
        System.out.println("\t\t******New game options******");
        System.out.println("\tEnter new field size X: ");
        fieldLen = getInputDigits();
        System.out.println("\tEnter new field size Y: ");
        fieldHeight = getInputDigits();
        System.out.println("\tEnter number of bombs: ");
        numBombs = getInputDigits();
        try {
            if(fieldLen > 99 || fieldHeight > 99){
                System.out.println("Field is too big for text UI.\n");
                System.out.println("Back to menu...");
                System.out.println("\t\t\t********************");
                return;
            }
            sizeX = fieldLen;
            sizeY = fieldHeight;
            controller.startGame(fieldLen,fieldHeight,numBombs);
        } catch (IncorectGameOptions e){
            System.out.println(e.getLocalizedMessage());
            System.out.println("Back to menu...");
            System.out.println("\t\t\t********************");
        }

    }

 private void recordsSection(){
     ScoreTable scoreTable = model.getScoreTable();
     ArrayList<AbstractMap.SimpleEntry<String, Double>> list = scoreTable.getScores();
     System.out.println("\t\t******Score table******");
     StringBuilder str = new StringBuilder();
     int place = 1;
     for (AbstractMap.SimpleEntry<String, Double> se: list) {
         str.append(place);
         str.append(".");
         str.append(se.getKey());
         str.append(" - ");
         str.append(se.getValue());
         System.out.println(str);
         str.setLength(0);
         place++;
     }
     System.out.println("\n\t   Write number to remove score.");
     System.out.println("\n\tb. Back.");
     System.out.println("\t\t\t********************");
     waitScoreSection(scoreTable);

 }

    private void waitScoreSection(ScoreTable scoreTable){
        int num;
        while (true){
            String input = scanner.next();
            if(input.equals("b")){
                break;
            }
            try {
                num = Integer.parseInt(input);
                Command command = Command.getInstance();
                command.setType(Command.CommandType.REMOVE_SCORE);
                command.changeArg("index", num-1);
                controller.processCommand(command);
                break;
            } catch (NumberFormatException e){
                System.out.println("Incorrect number format. Try again.");
            }

        }
    }

    private void aboutSection(){
        printAbout();
        waitForBackButton();
    }

    private void waitForBackButton(){
        boolean continueLoop = true;
        while (continueLoop){
            String input = scanner.next();
            if(input.equals("b")){
                continueLoop = false;
            }
        }
    }

    private void exitGame(){
        Command command = Command.getInstance();
        command.setType(Command.CommandType.SERIALIZE_SCORE);
        controller.processCommand(command);
        System.exit(0);
    }

    private void printAbout(){
        System.out.println("\t\t******Minesweeper about******");
        System.out.println(model.getAboutInfo());
        System.out.println("\n\tb. Back.");
        System.out.println("\t\t\t********************");
    }

    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        String eventName = evt.getPropertyName();

        switch (eventName){
            case "nothingChange" -> commandInvite();
        case "fieldChange", "flagChange" ->{
            printField();
            printTimeAndScore();
            commandInvite();
            }
        case "timerTick", "titleChange" -> {}
        case "stateChange" -> {
            GameModel.StateType type = (GameModel.StateType) evt.getNewValue();
            if(type == GameModel.StateType.ACTION) {
                field = model.getField();
                printField();
                commandInvite();
                } else if(type == GameModel.StateType.DEFEAT){
                    System.out.println("DEFEAT");
                    printField();
                } else if(type == GameModel.StateType.VICTORY){
                    System.out.println("VICTORY");
                    printField();
                    askForScore();
                } else {
                    System.out.println("Back to main menu...");
                }
            }
        }
    }

    private void askForScore(){
        System.out.println("Do you want to save your score?(Y/any)");
        printTimeAndScore();
        String str = scanner.next();
        if(str.equals("Y") || str.equals("y")) {
            System.out.println("Enter your name:");
            str = scanner.next();
            Command command = Command.getInstance();
            command.setType(Command.CommandType.SAVE_SCORE);
            command.changeArg("score", model.getCurScore());
            command.changeArg("name", str);
            controller.processCommand(command);
        }
    }

    private void printTimeAndScore(){
        System.out.println("Time: " + model.getGameTime() +"\tScore: " + model.getCurScore());
    }


    private Command getCommand(String[] strs){
        Command command = Command.getInstance();
        int len = strs.length;
        if(len < 1 || len > 3){
            System.out.println("Incorrect options. Try again.");
            command.setType(Command.CommandType.INCORRECT);
        }
        switch (len){
            case 1 -> {
                if(strs[0].equals("e")){
                    command.setType(Command.CommandType.EXIT_TO_MENU);
                } else {
                    command.setType(Command.CommandType.INCORRECT);
                }
            }
            case 2 -> {
                int x,y;
                try {
                    x = Integer.parseInt(strs[0]);
                    y = Integer.parseInt(strs[1]);
                    command.setType(Command.CommandType.CLICK);
                    command.changeArg("x", x);
                    command.changeArg("y", y);
                } catch (NumberFormatException e) {
                    System.out.println("Incorrect coords. Try again.");
                    command.setType(Command.CommandType.INCORRECT);
                }
            }
            case 3 -> {
                if(strs[0].equals("f")) {
                    int x, y;
                    try {
                        x = Integer.parseInt(strs[1]);
                        y = Integer.parseInt(strs[2]);
                        command.setType(Command.CommandType.FLAG);
                        command.changeArg("x", x);
                        command.changeArg("y", y);
                    } catch (NumberFormatException e) {
                        System.out.println("Incorrect coords. Try again.");
                        command.setType(Command.CommandType.INCORRECT);
                    }
                } else {
                    command.setType(Command.CommandType.INCORRECT);
                }
            }
            default -> command.setType(Command.CommandType.INCORRECT);
        }
        return command;
    }

    private void commandInvite(){
        System.out.print("Write coords to click \"x y\", \"e\" to exit, \"f x y\" for flagging: ");
        String str;
        String[] strs;
        Command command;
        do {
            str = scanner.nextLine();
            strs = str.split(" ");
            command = getCommand(strs);
        } while (!command.isCorrect());

        controller.processCommand(command);
    }

    private void printField(){
        StringBuilder str = new StringBuilder();
        str.append("   ");
        for (int i = 0; i < sizeX; i++){
            str.append(getFormattedNumber(i));
        }
        System.out.println(str);

        for (int i = 0; i < sizeY; i++){
            str.setLength(0);
            str.append("\u001B[0m");
            str.append(getFormattedNumber(i));
            for (int j = 0; j < sizeX; j++) {
                Title title = field.getTitle(j,i);
                if(title.isTerraIncognita()){
                    if(title.isFlag()){
                        str.append("\u001B[0m");
                        str.append("F");
                    }else {
                        str.append(" ");
                    }
                } else {
                    if (title.isFlag()) {
                        str.append("\u001B[0m");
                        str.append("F");
                    } else {
                        str.append(chooseColorForTitle(title));
                        if (title.isBomb()) {
                            str.append("*");
                        } else {
                            str.append(title.getNumBombsAround());
                        }
                    }
                }
                str.append("  ");
            }
            System.out.println(str);
        }
    }
    private String chooseColorForTitle(Title title){
        Title.TitleType type = title.getType();
        if(type == Title.TitleType.BOMB){
            return "\u001B[31m";
        }
        int numBombs = title.getNumBombsAround();
        switch (numBombs){
            case 0 -> {return "\u001B[37m";}
            case 1 -> {return "\u001B[32m";}
            case 2 -> {return "\u001B[36m";}
            case 3 -> {return "\u001B[34m";}
            case 4 -> {return "\u001B[33m";}
            case 5 -> {return "\u001B[35m";}
            default -> {return "\u001B[31m";}
        }

    }

    private String getFormattedNumber(int num){
        if(num > 99 || num < 0){
           return " ";
        }
        String str = Integer.toString(num);
        str += " ";
        if (str.length() == 2){
            str += " ";
        }
        return str;
    }


    private int getInputDigits() throws NumberFormatException{
        int num;
        while(true) {
            try {
                num = Integer.parseInt(scanner.next());
                return num;
            } catch (NumberFormatException e){
                System.out.println("Incorrect number format. Try again.");
            }
        }
    }

}


