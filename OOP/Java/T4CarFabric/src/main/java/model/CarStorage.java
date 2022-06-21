package model;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.Stack;

public class CarStorage {
    private final Stack<Car> storage;
    private final int capacity;
    private final PropertyChangeSupport support;
    private int carCounter;

    public CarStorage(int capacity){
        storage = new Stack<Car>();
        storage.ensureCapacity(capacity);
        this.capacity = capacity;
        support = new PropertyChangeSupport(this);
    }

    public void addListener(PropertyChangeListener listener){
        support.addPropertyChangeListener(listener);
    }

    public void removeListener(PropertyChangeListener listener){
        support.removePropertyChangeListener(listener);
    }

    public synchronized Car getCar(int dealerId) throws InterruptedException{
        while(true) {
            if (storage.empty()) {
                    wait();
            } else {
                break;
            }
        }
        Car car = storage.pop();
        car.setDealerId(dealerId);
        support.firePropertyChange("carSupply", car,storage.size());
        notify();
        return car;
    }

    public synchronized void putCar(Car car) throws  InterruptedException{
        while(true) {
            if (storage.size() >= capacity) {
                    wait();
            } else {
                break;
            }
        }
        carCounter++;
        storage.push(car);
        notify();
    }

    public int capacity(){
        return capacity;
    }
    public int size(){return storage.size();}
    public int getTotalCount(){return carCounter;}
}
