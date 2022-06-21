package model;

import model.confighandler.ConfigHandler;

public class GameModel {
    private final int DEFAULT_DELAY = 1000;
    private  Storage<Body> bodyStorage;
    private  Storage<Engine> engineStorage;
    private  Storage<Accessory> accessoryStorage;

    private  Supplier<Body> bodySupplier;
    private  Supplier<Engine> engineSupplier;
    private  Supplier<Accessory>[] accessorySuppliers;

    private  CarStorage carStorage;
    private  CarStorageManager carStorageManager;

    private  CarManufactory carManufactory;

    private  Dealer[] dealers;

    private final ConfigHandler configHandler;

    public GameModel(){
        configHandler = new ConfigHandler();
    }

    public void loadConfig(String pathname){
        configHandler.loadConfigOptions(pathname);
    }

    public void initModel(){
          bodyStorage = new Storage<>(configHandler.getOption("storageBodySize"));
          engineStorage = new Storage<>(configHandler.getOption("storageEngineSize"));
          accessoryStorage = new Storage<>(configHandler.getOption("storageAccessorySize"));

          bodySupplier = new Supplier<>(bodyStorage,DEFAULT_DELAY, Body.class);
          engineSupplier = new Supplier<>(engineStorage, DEFAULT_DELAY, Engine.class);

          int accessorySuppliesCount = configHandler.getOption("accessorySupplies");
          accessorySuppliers = new Supplier[accessorySuppliesCount];
          for(int i = 0; i < accessorySuppliesCount; i++) {
              accessorySuppliers[i] = new Supplier<Accessory>(accessoryStorage,DEFAULT_DELAY,Accessory.class);
          }

          carStorage = new CarStorage(configHandler.getOption("storageCarSize"));
          carManufactory = new CarManufactory(configHandler.getOption("workers"),carStorage,bodyStorage,engineStorage,accessoryStorage);
          boolean logMode = configHandler.getOption("logMode") == 1;
          carStorageManager = new CarStorageManager(carStorage,carManufactory, logMode);

          int dealersCount = configHandler.getOption("dealers");
          dealers = new Dealer[dealersCount];
          for (int i = 0; i < dealersCount; i++){
              dealers[i] = new Dealer(carStorage, DEFAULT_DELAY,i);
          }
    }

    public void startProduction(){
        bodySupplier.start();
        engineSupplier.start();
        for (Supplier<Accessory> accessorySupplier : accessorySuppliers) {
            accessorySupplier.start();
        }
        carStorageManager.start();
        for(Dealer dealer : dealers){
            dealer.start();
        }
        carManufactory.startManufactory();
    }

    public void interruptProduction(){
        bodySupplier.interrupt();
        engineSupplier.interrupt();
        for (Supplier<Accessory> accessorySupplier : accessorySuppliers) {
            accessorySupplier.interrupt();
        }
        carStorageManager.interrupt();
        for(Dealer dealer : dealers){
            dealer.interrupt();
        }
        carManufactory.interruptManufactory();
    }

    public int getSupplierBodyDelay(){
        return bodySupplier.getDelay();
    }

    public void setSupplierBodyDelay(int delay){
        bodySupplier.setDelay(delay);
    }

    public int getSupplierEngineDelay(){
        return engineSupplier.getDelay();
    }

    public void setSupplierEngineDelay(int delay){
        engineSupplier.setDelay(delay);
    }

    public int getSupplierAccessoryDelay(){
        return accessorySuppliers[0].getDelay();
    }

    public void setSupplierAccessoryDelay(int delay){
        for(Supplier<Accessory> supplier : accessorySuppliers){
            supplier.setDelay(delay);
        }
    }

    public int getDealersDelay(){return dealers[0].getDelay();}

    public void setDealersDelay(int delay){
        for(Dealer dealer : dealers){
            dealer.setDelay(delay);
        }
    }

    public int getBodyStorageCapacity(){
        return bodyStorage.capacity();
    }

    public int getEngineStorageCapacity(){
        return engineStorage.capacity();
    }

    public int getAccessoryStorageCapacity(){
        return accessoryStorage.capacity();
    }

    public int getCarStorageCapacity(){return carStorage.capacity();}
    public int getManufactoryTaskCount(){
        return carManufactory.getOrdersCount();
    }

    public int getBodyStorageSize(){
        return bodyStorage.size();
    }
    public int getEngineStorageSize(){
        return engineStorage.size();
    }
    public int getAccessoryStorageSize(){
        return accessoryStorage.size();
    }
    public int getCarStorageSize(){
        return carStorage.size();
    }

    public int getTotalBodiesCount(){
        return bodyStorage.getTotalCount();
    }
    public int getTotalEnginesCount(){
        return engineStorage.getTotalCount();
    }
    public int getTotalAccessoriesCount(){
        return accessoryStorage.getTotalCount();
    }
    public int getTotalCarsCount(){
        return carStorage.getTotalCount();
    }

}
