import logic.DataHandler;
import logic.Graph;
import logic.NetworkHandler;
import pojo.Detail;
import test.GraphTest;

import java.io.IOException;
import java.net.MalformedURLException;
import java.util.List;
import java.util.logging.*;


public class Main {
    private static final Logger logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);

    public static void main(String[] args) {
        setupGlobalLogger();

        // run with -ea for tests: java -jar -ea FILE.jar <URL>
        testProg();

        if(args.length == 0){
            logger.severe("Invalid args. You must pass the url.");
            System.exit(1);
        }

        NetworkHandler networkHandler = null;
        try {
            networkHandler = new NetworkHandler(args[0]);
        } catch (MalformedURLException e){
            logger.severe("Invalid url.\n\t" + e.getLocalizedMessage());
            System.exit(1);
        }

        List<Detail> test = null;
        try {
            test = networkHandler.getDataFromServer();
        } catch (Exception e){
            logger.severe("Can't get data from server.\n\t" + e.getLocalizedMessage());
            System.exit(1);
        }

        Graph graph = DataHandler.createGraph(test);

        graph.printMatrix();

    }

    private static void setupGlobalLogger(){
        logger.setLevel(Level.FINE);
        FileHandler fileHandler = null;
        try {
            fileHandler = new FileHandler("log.txt");
        } catch (IOException e){
            System.err.println("Can't create file logger.");
        }
        assert fileHandler != null;
        fileHandler.setFormatter(new SimpleFormatter());

        logger.addHandler(fileHandler);
    }

    static void testProg(){
        GraphTest.testAdjacencyMatrix();
    }

}