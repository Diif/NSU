package crackhash.manager.model.internal;

import java.util.ArrayList;

import com.google.common.collect.ImmutableSet;

public interface ServiceInfoProvider {

  ImmutableSet<Integer> getAliveWorkersOrWait() throws InterruptedException;

  public void increaseStreakForAllWorkers();

  public ImmutableSet<Integer> getAliveWorkers();
  
  public String getWorkerRouteKey(int workerNum);

  public int getAmountOfAliveWorkers();

  public void nullifyStreakOrAddAlive(int worker);

  public ArrayList<Integer> removeDeadWorkers();

  public boolean isRecovered();

  public void makeRecovered();

}
