package crackhash.worker.database;

import org.springframework.data.mongodb.repository.MongoRepository;

import crackhash.worker.model.entities.AnswerStatus;
import crackhash.worker.model.entities.WorkerAnswer;
import java.util.List;
import java.util.Optional;


public interface AnswerRepo extends MongoRepository<WorkerAnswer, String> {
  List<WorkerAnswer> findByStatusAndWorkerNum(AnswerStatus status, Integer workerNum);
  Optional<WorkerAnswer> findFirst1ByPartId(String partId);
}
