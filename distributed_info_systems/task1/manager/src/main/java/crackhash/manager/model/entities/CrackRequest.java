package crackhash.manager.model.entities;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.concurrent.atomic.AtomicInteger;

import lombok.Getter;

public class CrackRequest {
  public enum CrackStatus {IN_PROGRESS, READY, ERROR}

  private final static AtomicInteger idGenerator = new AtomicInteger(0);

  private final Integer id;
  private final String hash;
  private final Integer maxLen;
  private CrackStatus status = CrackStatus.IN_PROGRESS;
  private AtomicInteger acs = new AtomicInteger(0);
  private ArrayList<String> result = new ArrayList<>();
  @Getter
  private final Calendar expirationTime;

  public CrackRequest(String hash, int maxLen, int timeoutSec){
    this.id = idGenerator.getAndIncrement();
    this.hash = hash;
    this.maxLen = maxLen;
    expirationTime = Calendar.getInstance();
    expirationTime.add(Calendar.SECOND, timeoutSec);
  }

  public int getAcs(){
    return acs.get();
  }

  public int increaseAcs(){
    return acs.incrementAndGet();
  }

  public Integer getId() {
    return id;
  }

  public CrackStatus getStatus() {
    return status;
  }

  public void setStatus(CrackStatus status) {
    this.status = status;
  }

  public ArrayList<String> getResult() {
    if (status.equals(CrackStatus.READY))
    {
      return result;
    }
    return null;
  }

  public synchronized void addResult(ArrayList<String> workerRes) {
    result.addAll(workerRes);
  }

  public String getHash() {
    return hash;
  }


  public Integer getMaxLen() {
    return maxLen;
  }

  @Override
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    result = prime * result + (int) (id ^ (id >>> 32));
    return result;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (obj == null)
      return false;
    if (getClass() != obj.getClass())
      return false;
    CrackRequest other = (CrackRequest) obj;
    if (id != other.id)
      return false;
    return true;
  }  

}
