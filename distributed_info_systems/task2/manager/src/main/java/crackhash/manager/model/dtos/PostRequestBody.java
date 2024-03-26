package crackhash.manager.model.dtos;

import lombok.AllArgsConstructor;
import lombok.Getter;

@Getter
@AllArgsConstructor
public class PostRequestBody {

  private final String hash;
  private final Integer maxLength;
}
