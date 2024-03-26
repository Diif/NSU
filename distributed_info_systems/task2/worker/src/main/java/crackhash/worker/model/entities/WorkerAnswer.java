package crackhash.worker.model.entities;

import java.util.ArrayList;

import org.springframework.data.annotation.Id;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;

@AllArgsConstructor
@Setter
@Getter
public class WorkerAnswer{

  @Id
  private final String id;
  private final String partId;
  private final Integer workerNum;
  private AnswerStatus status;
  private final ArrayList<String> data;
}