import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.Map.Entry;

public class Handler{
    private int count;
    private ArrayList<Entry<String, Integer>> statistic;
    private Scanner fileScanner;

    public Handler(String fileName){
        count = 0;
        try{
            Path filePath = Paths.get(fileName);
            fileScanner = new Scanner(filePath);
        } catch(IOException e) {
            System.err.println("Error while reading file: " + e.getLocalizedMessage());
        }
    }

    public void collectStatisticFromFile(){
        TreeMap<String, Integer> words_freq = new TreeMap<String, Integer>();
        while (fileScanner.hasNextLine()){
            String line = fileScanner.nextLine();

            String[] words = line.split("[^a-zA-Z0-9]");
            for (String word : words){
                if("\n\0".equals(word)){
                    continue;
                }
                if(!words_freq.containsKey(word)){
                    words_freq.put(word, 1);
                } else {
                    words_freq.put(word, words_freq.get(word)+1);
                }
                count++;
            }
        }
        statistic = new ArrayList<Entry<String, Integer>>(words_freq.entrySet());
        statistic.sort(Entry.comparingByValue());
        Collections.reverse((statistic));
    }
    public List<Entry<String, Integer>> getStatistic(){
        return Collections.unmodifiableList((statistic));
    }
    public int getCount(){
        return count;
    }
}
