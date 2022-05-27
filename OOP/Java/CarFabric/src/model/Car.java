package model;

public class Car {
    private final Body body;
    private final Engine engine;
    private final Accessory accessory;
    private int dealerId;

    public Car(Body body, Engine engine, Accessory accessory){
        this.body = body;
        this.engine = engine;
        this.accessory = accessory;
    }

    public void setDealerId(int id){
        dealerId = id;
    }

    public int getDealerId(){
        return dealerId;
    }

    public String getCarId(){
        return String.valueOf(body.getId()) + engine.getId() + accessory.getId();
    }

    public int getBodyId(){
        return body.getId();
    }
    public int getEngineId(){
        return engine.getId();
    }
    public int getAccessoryId(){
        return accessory.getId();
    }


}
