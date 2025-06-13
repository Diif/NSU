package logic;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import pojo.Detail;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.List;
import java.util.logging.Logger;

public class NetworkHandler {
    private URL url;
    private static final Logger logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);
    private final ObjectMapper mapper;

    public NetworkHandler(String stringUrl) throws MalformedURLException {
        mapper = new ObjectMapper();
        try {
            url = new URL(stringUrl);
        } catch (MalformedURLException e){
            logger.info("NetworkHandler: Trying to add protocol to URL...");
            String protocol = "http://";
            url = new URL(protocol + stringUrl);
        }
        logger.fine("NetworkHandler: NetworkHandler was created.");
    }

    public List<Detail> getDataFromServer() throws Exception {
        if(null == url){
            logger.severe("Illegal call.");
            throw new Exception("Unreachable code");
        }

        HttpURLConnection connection;
        try {
            connection = (HttpURLConnection) url.openConnection();
        } catch (IOException e){
            logger.severe("NetworkHandler: Can't open url connection:\n\t" + e.getLocalizedMessage());
            throw e;
        }

        connection.setRequestProperty("accept", "application/json");
        int response_code = connection.getResponseCode();

        List<Detail> detailList;
        if(response_code == HttpURLConnection.HTTP_OK){
            detailList = mapper.readValue(connection.getInputStream(), new TypeReference<List<Detail>>() {});
        } else {
            logger.severe("NetworkHandler: bad response code:\n\t");
            throw  new IOException("bad response code");
        }
        logger.fine("NetworkHandler: got data from server.");
        return detailList;
    }
}
