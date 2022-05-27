package model;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Date;

public class CarStorageManager extends Thread implements PropertyChangeListener{
    private final CarManufactory carManufactory;
    private final Object monitor = new Object();
    private final int capacity;
    private int size;
    private Car lastCar;
    private final boolean logMode;
    private BufferedWriter logWriter;

    @Override
    public void propertyChange(PropertyChangeEvent event){
        synchronized(monitor) {
            size = (Integer) event.getNewValue();
            lastCar = (Car) event.getOldValue();
            monitor.notify();
        }
    }

    public CarStorageManager(CarStorage carStorage, CarManufactory carManufactory, boolean logMode){
        super("StorageManager Thread");
        assert carStorage!= null;
        assert carManufactory != null;
        carStorage.addListener(this);
        this.carManufactory = carManufactory;
        capacity = carStorage.capacity();
        size = carStorage.size();
        this.logMode = logMode;
        if(logMode){
            try {
                logWriter = new BufferedWriter(new FileWriter("log.txt"));
            } catch (IOException e){
                System.err.println(e.getLocalizedMessage());
            }
        }
    }

    public void run(){
        int ORDER_SIZE = 10;
        synchronized (monitor) {
            while (true) {
                try {
                    if (size < capacity && carManufactory.getOrdersCount() <= capacity) {
                        for (int i = 0; i < ORDER_SIZE; i++) {
                            carManufactory.addCarOrder();
                        }
                    }
                    monitor.wait();
                    writeLog();
                } catch (InterruptedException e) {
                    System.out.println("CarStorageManager Thread was interrupted");
                    try {
                        logWriter.close();
                    } catch (IOException ignored){}
                    return;
                }
            }
        }
    }

private void writeLog(){
        Date time = new Date();
        try {
            logWriter.write(time + ": Dealer <" + lastCar.getDealerId() + ">: Auto <" + lastCar.getCarId() + ">(Body " + lastCar.getBodyId() + " Engine " + lastCar.getEngineId() + " Accessory " + lastCar.getAccessoryId() + ")\n");
            logWriter.flush();
        } catch (IOException e){
            System.err.println("Logger exc: " + e.getLocalizedMessage());
        }
}

}
