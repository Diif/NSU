package logic;

import pojo.Detail;

import java.util.HashMap;
import java.util.List;
import java.util.logging.Logger;

public class DataHandler {

    private static final Logger logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);

    public static Graph createGraph(List<Detail> details){
        // assuming details in JSON have uniq id.
        HashMap<Integer, Detail> detailsMap = new HashMap<>();
        for (Detail x : details){
            detailsMap.put(x.getId(), x);
        }
        return createGraph(detailsMap);
    }

    public static Graph createGraph(HashMap<Integer, Detail> details){
        Graph graph =new Graph(details,details.size());
        logger.fine("DataHandler: graph created.");
        return graph;
    }



}
