package crackhash.manager.model.internal;

import java.util.ArrayList;
import java.util.concurrent.ConcurrentHashMap;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import com.google.common.collect.ImmutableSet;

@Component
@Scope("singleton")
public class ServiceInfoProviderImpl implements ServiceInfoProvider{
  @Value("${maxTimeoutStreak}")
  private Integer maxTimeoutStreak;
  private boolean recovered = false;

  private final ConcurrentHashMap<Integer, Integer> aliveWorkers = new ConcurrentHashMap<>();
  private final ConcurrentHashMap<Integer, String> workerAddresses = new ConcurrentHashMap<>();
  private final Object aliveWorkersAppearanceMonitor = new Object();

  @Override
  public void increaseStreakForAllWorkers(){
    aliveWorkers.replaceAll((k,v) -> v + 1);
  }

  @Override
  public ImmutableSet<Integer> getAliveWorkersOrWait() throws InterruptedException{
    var workers = getAliveWorkers();
    while (workers.size() < 1) {
      synchronized(aliveWorkersAppearanceMonitor)
      {
        aliveWorkersAppearanceMonitor.wait();
      }
      workers = getAliveWorkers();
    }
    return workers;
  }

  @Override
  public ImmutableSet<Integer> getAliveWorkers(){
    return ImmutableSet.copyOf(aliveWorkers.keySet());
  }

  @Override
  public void nullifyStreakOrAddAlive(int worker){
    assert(worker > 0);
    aliveWorkers.put(worker, 0);
    // perfermance optimization is needed
    synchronized (aliveWorkersAppearanceMonitor)
    {
      aliveWorkersAppearanceMonitor.notifyAll();
    }
  }

  public ArrayList<Integer> removeDeadWorkers(){
    ArrayList<Integer> removedWorkers = new ArrayList<>();
    for (var i = aliveWorkers.entrySet().iterator(); i.hasNext(); )
    {
      var e = i.next();
      if (e.getValue() > maxTimeoutStreak)
      {
        removedWorkers.add(e.getKey());
        i.remove();
      }
    }
    return removedWorkers;
  }

  @Override
  public int getAmountOfAliveWorkers() {
    // return aliveWorkers.size();
    return 10;
  }

  @Override
  public String getWorkerRouteKey(int worker) {
    assert(worker > 0);
    // return workerAddresses.computeIfAbsent(worker, (n) -> "worker" + n);
    return workerAddresses.computeIfAbsent(worker, (n) -> "worker");
  }

  @Override
  public boolean isRecovered() {
    return recovered;
  }
  
  @Override
  public void makeRecovered(){
    recovered = true;
  }
}
