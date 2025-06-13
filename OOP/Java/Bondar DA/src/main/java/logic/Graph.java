package logic;

import pojo.Detail;

import java.util.HashMap;
import java.util.Map;
import java.util.logging.Logger;

public class Graph {

    private static final Logger logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);
    private HashMap<Integer, Detail> nodes;
    private final int matrixSideLen;
    byte[][] adjacencyMatrix;

    public Graph(HashMap<Integer, Detail> nodes, int sideLen){
        this.matrixSideLen = sideLen;
        if(sideLen <= 0){
            logger.severe("Invalid size of graph.");
            throw new RuntimeException("Invalid graph size.");
        }
        this.nodes = nodes;
        //zeroes by default
        adjacencyMatrix = new byte[sideLen][sideLen];
        fillAdjacencyMatrix();
    }

    public void printMatrix(){
        System.out.println("Adjacency matrix:");
        System.out.print("  ");
        for(int i = 0; i < matrixSideLen; i++) {
            System.out.print(nodes.get(i+1).getSymbol() + " ");
        }
        System.out.println("");
        for(int i = 0; i < matrixSideLen; i++){
            System.out.print(nodes.get(i+1).getSymbol() + " ");
            for (int j = 0; j < matrixSideLen; j++){
                System.out.print(adjacencyMatrix[i][j] + " ");
            }
            System.out.print("\n");
        }
    }

    private void fillAdjacencyMatrix(){
        for (Map.Entry<Integer, Detail> x : nodes.entrySet()){
            int[] referenceId = x.getValue().getReference_id();
            if(null == referenceId){
                continue;
            }
            int curNodeId = x.getKey();
            for(int i = 0; i < referenceId.length; i++){
                int neighbourId = referenceId[i];
                setConnection(curNodeId, neighbourId, (byte) 1);;
            }
        }
        logger.fine("Graph: Adjacency matrix was created.");
    }

    public void setConnection(int node1, int node2, byte val){
        // assuming ids start from 1
        node1--;
        node2--;
        if((val != 0 && val!=1) || (node1 >= matrixSideLen || node2 >= matrixSideLen) || (node1 == node2)){
            logger.info("Graph: Invalid setConnection call in graph.");
            return;
        }
        adjacencyMatrix[node1][node2] = val;
        adjacencyMatrix[node2][node1] = val;
        logger.fine("Graph: created new connection.");
    }

    public int getMatrixSideLen() {
        return matrixSideLen;
    }

    public byte[][] getAdjacencyMatrix() {
        return adjacencyMatrix;
    }

    public HashMap<Integer, Detail> getNodes() {
        return nodes;
    }
}
