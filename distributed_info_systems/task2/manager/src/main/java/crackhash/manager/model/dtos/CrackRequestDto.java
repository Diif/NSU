package crackhash.manager.model.dtos;

import crackhash.manager.model.entities.CrackRequest;
import lombok.Getter;

@Getter
public class CrackRequestDto {
  private final String id;
  
  private final String hash;

  private final int maxLen;

  private final int partNum;

  private final int partTotal;

  public CrackRequestDto(CrackRequest cr, int partNum, int partTotal){
    id = cr.getId();
    hash = cr.getHash();
    maxLen = cr.getMaxLen();
    this.partNum = partNum;
    this.partTotal = partTotal;
  }
  
  @Override
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    result = prime * result + ((id == null) ? 0 : id.hashCode());
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
    CrackRequestDto other = (CrackRequestDto) obj;
    if (id == null) {
      if (other.id != null)
        return false;
    } else if (!id.equals(other.id))
      return false;
    return true;
  }
  
}
