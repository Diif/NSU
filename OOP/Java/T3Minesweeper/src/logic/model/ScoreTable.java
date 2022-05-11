package logic.model;

import java.io.*;
import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayList;
import java.util.Comparator;

public class ScoreTable {

    private static class PairComparator implements Comparator<SimpleEntry<String, Double>> {
        @Override
        public int compare(SimpleEntry<String, Double> o1,SimpleEntry<String, Double> o2) {
            Double val1 = o1.getValue();
            Double val2 = o2.getValue();
            return val2.compareTo(val1);
        }
    }

    private File scoresFile;
    private ArrayList<SimpleEntry<String, Double>> scores;

    public void initScores(){
        scoresFile = new File("scores.bin");
        boolean fileExists = false;
        try {
            fileExists = !scoresFile.createNewFile();
        } catch (IOException e) {
            e.printStackTrace();
        }
        if(fileExists){
            try {
                if(scoresFile.length() == 0){
                    scores = new ArrayList<SimpleEntry<String, Double>>();
                    return;
                }
                FileInputStream fileInputStream
                        = new FileInputStream(scoresFile);
                ObjectInputStream objectInputStream
                        = new ObjectInputStream(fileInputStream);
                scores = (ArrayList<SimpleEntry<String, Double>>) objectInputStream.readObject();
                objectInputStream.close();
            } catch (IOException | ClassNotFoundException e) {
                System.err.println("Can't deserialize file.");
            }
        } else {
            scores = new ArrayList<SimpleEntry<String, Double>>();
        }
    }

    public void serializeScores(){
        try {
            FileOutputStream fileOutputStream
                    = new FileOutputStream(scoresFile);
            ObjectOutputStream objectOutputStream
                    = new ObjectOutputStream(fileOutputStream);
            objectOutputStream.writeObject(scores);
            objectOutputStream.flush();
            objectOutputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void addScore(String name, Double score){
        scores.add(new SimpleEntry<>(name, score));
        sortScores();
    }

    public ArrayList<SimpleEntry<String, Double>> getScores() {
        return scores;
    }

    public void removeScore(int index){
        if (index >= scores.size() || index < 0){
            return;
        }
        scores.remove(index);
    }

    private void sortScores(){
        scores.sort(new PairComparator());
    }
}
