package model;

import java.lang.reflect.InvocationTargetException;
import java.util.concurrent.atomic.AtomicInteger;

public class Supplier<T extends Detail> extends Thread{
    private final Storage<T> storage;
    private final Class<T> detailClass;
    private int delay;
    private static final AtomicInteger numGen = new AtomicInteger(0);

    public Supplier(Storage<T> storage, int delay, Class<T> detailClass){
        super("Supplier Thread");
        assert storage != null;
        assert delay > 0;
        this.storage = storage;
        this.delay = delay;
        this.detailClass = detailClass;
    }

    public void setDelay(int delay){
        this.delay = delay;
    }

    public int getDelay(){return delay;}

    public void run(){
        while(true){
            try {
                sleep(delay);
                storage.putDetail(detailClass.getDeclaredConstructor(Integer.class).newInstance(numGen.incrementAndGet()));
            } catch (InterruptedException e){
                System.out.println("Supplier was interrupted");
                return;
            } catch (InvocationTargetException e) {
                throw new RuntimeException(e);
            } catch (InstantiationException e) {
                throw new RuntimeException(e);
            } catch (IllegalAccessException e) {
                throw new RuntimeException(e);
            } catch (NoSuchMethodException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
