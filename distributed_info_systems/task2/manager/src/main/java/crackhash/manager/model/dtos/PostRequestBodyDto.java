package crackhash.manager.model.dtos;

import lombok.AllArgsConstructor;
import lombok.Getter;

@Getter
@AllArgsConstructor
public class PostRequestBodyDto {
  private final String hash;

  private final int maxLen;  
}
