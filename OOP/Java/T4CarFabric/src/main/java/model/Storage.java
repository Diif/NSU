package model;

import java.util.Stack;

public class Storage<T extends Detail> {
    private final Stack<T> storage;
    private final int capacity;
    private int detailCounter;

    public Storage(int capacity){
        storage = new Stack<T>();
        storage.ensureCapacity(capacity);
        this.capacity = capacity;
        detailCounter = 0;
    }

    public synchronized T getDetail() throws InterruptedException{
        while(true) {
            if (storage.empty()) {
                    wait();
            } else {
                break;
            }
        }
        T detail = storage.pop();
        notify();
        return detail;
    }

    public synchronized void putDetail(T detail) throws InterruptedException{
        while(true) {
            if (storage.size() >= capacity) {
                    wait();
            } else {
                break;
            }
        }
        detailCounter++;
        storage.push(detail);
        notify();
    }

    public int capacity(){
        return capacity;
    }
    public int getTotalCount(){return detailCounter;}
    public int size(){return storage.size();}
}
