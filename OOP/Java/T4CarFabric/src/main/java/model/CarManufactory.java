package model;

import threadpool.ThreadPool;

import java.util.concurrent.atomic.AtomicInteger;

public class CarManufactory {
    private final ThreadPool threadPool;
    private final CarStorage carStorage;
    private final Storage<Body> bodyStorage;
    private final Storage<Engine> engineStorage;
    private final Storage<Accessory> accessoryStorage;


    public CarManufactory(int numWorkers, CarStorage carStorage, Storage<Body> bodyStorage,
                          Storage<Engine> engineStorage, Storage<Accessory> accessoryStorage){
        threadPool = new ThreadPool(numWorkers);
        this.carStorage = carStorage;
        this.bodyStorage = bodyStorage;
        this.engineStorage = engineStorage;
        this.accessoryStorage = accessoryStorage;
    }

    public void addCarOrder(){
        threadPool.execute(() -> {
            try {
                carStorage.putCar(new Car(bodyStorage.getDetail(),
                        engineStorage.getDetail(), accessoryStorage.getDetail()));
            } catch (InterruptedException e) {
                throw new RuntimeException("INTERRUPT");
            }
        });
    }

    public void startManufactory(){
        threadPool.startThreadPool();
    }

    public void interruptManufactory(){
        threadPool.interruptThreadPool();
    }
    public int getOrdersCount(){
        return threadPool.getTaskCountInQueue();
    }

}
