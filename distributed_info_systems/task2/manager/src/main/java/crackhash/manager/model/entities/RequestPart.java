package crackhash.manager.model.entities;

import org.springframework.data.annotation.Id;
import org.springframework.data.annotation.Version;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;

@AllArgsConstructor
@Getter
@Setter
public class RequestPart {
  @Id
  private final String id;
  @Version
  private Integer version;
  private final String requestId;
  private final String hash;
  private final Integer maxLen;
  private Integer totalParts;
  private final Integer partNum;
  @Setter
  private Integer workerNum;
  @Setter
  private PartStatus status;
}
