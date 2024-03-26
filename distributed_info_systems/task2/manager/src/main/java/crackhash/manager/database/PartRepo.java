package crackhash.manager.database;

import org.springframework.data.mongodb.repository.MongoRepository;

import crackhash.manager.model.entities.PartStatus;
import crackhash.manager.model.entities.RequestPart;
import java.util.List;
import java.util.Optional;



public interface PartRepo extends MongoRepository<RequestPart, String> {
  List<RequestPart> findByWorkerNumAndStatusNot(Integer workerNum, PartStatus status);
  Optional<RequestPart> findFirst1ByRequestId(String requestId);
  List<RequestPart> findByStatus(PartStatus status);
  List<RequestPart> findByStatusAndWorkerNumNotIn(PartStatus status, List<Integer> workerNum);
}
