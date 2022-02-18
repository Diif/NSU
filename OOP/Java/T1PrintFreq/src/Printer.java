import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Map.Entry;
import java.util.List;

public class Printer{
    private final Handler handler;
    Printer(Handler fileHandler) throws RuntimeException{
        handler = fileHandler;
        if(null == handler){
            System.err.println("Error: Printer get null handler.");
        }
    }

    public void printStatisticToFile(String file_name){
        if(null == handler){
            return;
        }
        PrintWriter writer;
        try{
            writer = new PrintWriter(file_name);
        }catch(FileNotFoundException e) {
            System.err.println("Error: problems with write file.");
            return;
        }
        List<Entry<String, Integer>> statistic = handler.getStatistic();
        int count = handler.getCount();

        for (Entry<String, Integer> stat: statistic ) {
            writer.printf("%s,%d,%.3f%%\n",stat.getKey(), stat.getValue(), Double.valueOf(stat.getValue()) /count );
        }
        writer.close();
    }

}