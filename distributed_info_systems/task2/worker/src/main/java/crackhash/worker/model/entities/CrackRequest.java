package crackhash.worker.model.entities;

import java.util.ArrayList;
import java.util.Objects;

import org.springframework.data.annotation.Id;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;

@AllArgsConstructor
@Getter
@Setter
public class CrackRequest {

  @Id
  private final String id;
  private final String hash;
  private final Integer maxLen;
  private final Integer totalParts;
  private RequestStatus status;
  private Integer acs;
  private ArrayList<String> result;

  @Override
  public int hashCode() {
    return Objects.hash(id);
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
    if (id.equals(other.id))
      return true;
    return false;
  }  

}
