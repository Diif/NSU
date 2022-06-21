package model;

public class Dealer extends Thread{
    private final CarStorage carStorage;
    private int delay;
    private final int id;
    private Car lastCar;

    public Dealer(CarStorage carStorage, int delay, int id){
        super("Dealer Thread " + id);
        this.carStorage = carStorage;
        this.delay = delay;
        this.id = id;
    }

    public int getDelay() {
        return delay;
    }

    public void setDelay(int delay) {
        this.delay = delay;
    }

    public void run(){
        while(true){
            try {
                carStorage.getCar(id);
                sleep(delay);
            } catch (InterruptedException e){
                System.out.println("Dealer thread was interrupted.");
                return;
            }

        }
    }

}
