package logic.infographic;

import logic.Graph;
import pojo.Detail;

import java.util.HashMap;
import java.util.Map;

public class Infographics {

    private final Graph graph;
    private char[][] infoMatrix;
    private int centerX;
    private int centerY;
    private DetailRepresentation[] detailPlaces;
    private final int ROOT_DETAIL_ID = 1;

    public Infographics(Graph graph){
        this.graph = graph;
        detailPlaces = new DetailRepresentation[graph.getMatrixSideLen()];
        HashMap<Integer, Detail> map = graph.getNodes();
        for (int i = 1; i <= graph.getMatrixSideLen(); i++){
            Detail detail = map.get(i);
            detailPlaces[i] = new DetailRepresentation(detail.getSymbol_count(), detail.getSymbol(),i);
        }
        initInfoMatrix();
        createInfographics();
    }

    private void initInfoMatrix(){
        int maxDetailsLen = 0;
        for(Map.Entry<Integer, Detail> x : graph.getNodes().entrySet()){
            maxDetailsLen += x.getValue().getSymbol_count();
        }

        centerX = maxDetailsLen - 1;
        centerY = maxDetailsLen - 1;
        //now we have enough space for any case, "out of bounds" situation is unreachable
        infoMatrix = new char[maxDetailsLen*2][maxDetailsLen*2];

    }

    //greedy strategy maybe...
    private void createInfographics(){
        int totalDetails = graph.getMatrixSideLen();

        DetailRepresentation rootDetail = detailPlaces[ROOT_DETAIL_ID - 1];
        rootDetail.setCoords(centerX, centerY);
        rootDetail.setDirection(Direction.BOT);
        placeDetail(rootDetail);


        //place all neighbors of root detail
        for (int i = 0; i < graph.getMatrixSideLen(); i++){
            if(graph.getAdjacencyMatrix()[ROOT_DETAIL_ID - 1][i] == 0){
                continue;
            }
//            recPlace(ROOT_DETAIL_ID, i+1);
        }
    }

//    private boolean recPlace(int parentId, int ownId){
//        DetailRepresentation parent = detailPlaces[parentId-1];
//        Direction parentDir = parent.getDirection();
//        Coordinates parentCoords = parent.getCoords();
//        int parentLen = parent.getLength();
//        switch (parentDir) {
//            case BOT:
//            case TOP:
//            //try to put right
//            for (int i = 0; i < parentLen; i++) {
//
//            }
//            //try to put left
//            for (int i = 0; i < parentLen; i++) {
//
//            }
//            break;
//            case LEFT:
//            case RIGHT:
//        }
//    }
//
//    private boolean putDetailIfPossible(DetailRepresentation detailRepresentation){
//        if(!isFreePlace(detailRepresentation)){
//            return false;
//        }
//        placeDetail(detailRepresentation);
//    }

    private boolean isFreePlace(DetailRepresentation detailRepresentation){
        Coordinates coordinates = detailRepresentation.getCoords();
        int x = coordinates.getX();
        int y = coordinates.getY();
        int len = detailRepresentation.getLength();
        switch (detailRepresentation.getDirection()){
            case TOP:
                for (int i = 0; i < len; i++){
                    if(infoMatrix[x][y-i] != 0){
                        return false;
                    }
                }
                break;
            case BOT:
                for (int i = 0; i < len; i++){
                    if(infoMatrix[x][y+i] != 0){
                        return false;
                    }
                }
                break;
            case LEFT:
                for (int i = 0; i < len; i++){
                    if(infoMatrix[x-i][y] != 0){
                        return false;
                    }
                }
                break;
            case RIGHT:
                for (int i = 0; i < len; i++){
                    if(infoMatrix[x+i][y] != 0){
                        return false;
                    }
                }
                break;
            case NONE:
                break;
        }
        return true;
    }

    private void placeDetail(DetailRepresentation detailRepresentation){
        detailRepresentation.setPlaced(true);
        Coordinates coordinates = detailRepresentation.getCoords();
        int x = coordinates.getX();
        int y = coordinates.getY();
        int len = detailRepresentation.getLength();
        char symb = detailRepresentation.getSymb();
        switch (detailRepresentation.getDirection()){
            case TOP:
                for (int i = 0; i < len; i++){
                    infoMatrix[x][y-i] = symb;
                }
                break;
            case BOT:
                for (int i = 0; i < len; i++){
                    infoMatrix[x][y+i] = symb;
                }
                break;
            case LEFT:
                for (int i = 0; i < len; i++){
                    infoMatrix[x-i][y] = symb;
                }
                break;
            case RIGHT:
                for (int i = 0; i < len; i++){
                    infoMatrix[x+i][y] = symb;
                }
                break;
            case NONE:
                break;
        }
    }

}
