package threadpool;

import java.util.concurrent.LinkedBlockingQueue;

public class ThreadPool {
    private final LinkedBlockingQueue<Runnable> queue;
    private final PoolWorker[] threads;

    public ThreadPool(int numThreads) {
        queue = new LinkedBlockingQueue<>();
        threads = new PoolWorker[numThreads];
        for (int i = 0; i < numThreads; i++) {
            threads[i] = new PoolWorker("WORKER " + i);
        }
    }

    public void startThreadPool(){
        for(PoolWorker worker : threads){
            worker.start();
        }
    }

    public void interruptThreadPool(){
        for(PoolWorker worker : threads){
            worker.interrupt();
        }
    }

    public int getTaskCountInQueue() {
        synchronized (queue) {
            return queue.size();
        }
    }

    public void execute(Runnable task) {
        synchronized (queue) {
            queue.add(task);
            queue.notify();
        }

    }

    private class PoolWorker extends Thread {
        public PoolWorker(String name){
            super(name);
        }
        public void run() {
            Runnable task;
            while (true) {
                synchronized (queue) {
                    try {
                        if (queue.isEmpty()) {
                            queue.wait();
                        }
                    } catch (InterruptedException e) {
                        System.out.println("Worker was interrupted");
                        return;
                    }
                    task = queue.poll();
                }
                try {
                    assert task!=null;
                    task.run();
                    if (this.isInterrupted()) {
                        break;
                    }
                } catch (RuntimeException e) {
                    System.out.println("Worker was interrupted...");
                    return;
                }
            }
        }
    }
}
