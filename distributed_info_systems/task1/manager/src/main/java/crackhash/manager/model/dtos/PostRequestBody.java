package crackhash.manager.model.dtos;

public class PostRequestBody {

  private String hash;
  private Integer maxLength;

  public String getHash() {
    return hash;
  }

  public void setHash(String hash) {
    this.hash = hash;
  }

  public Integer getMaxLength() {
    return maxLength;
  }

  public void setMaxLength(Integer maxLength) {
    this.maxLength = maxLength;
  }
}
