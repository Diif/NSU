package crackhash.worker.model.entities;

import java.util.ArrayList;

import crackhash.worker.model.dtos.CrackRequestDto;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class CrackRequest {
  public enum CrackStatus {IN_PROGRESS, READY}

  private final Integer id;
  private final String hash;
  private final Integer maxLen;
  private final Integer partNum;
  private final Integer partTotal;
  private CrackStatus status = CrackStatus.IN_PROGRESS;
  private ArrayList<String> result = new ArrayList<>();

  public CrackRequest(CrackRequestDto dto){
    this.id = dto.getId();
    this.hash = dto.getHash();
    this.maxLen = dto.getMaxLen();
    this.partNum = dto.getPartNum();
    this.partTotal = dto.getPartTotal();
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
