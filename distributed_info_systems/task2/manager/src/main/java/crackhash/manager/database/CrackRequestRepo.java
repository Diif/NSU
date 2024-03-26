package crackhash.manager.database;

import org.springframework.data.mongodb.repository.MongoRepository;

import crackhash.manager.model.entities.CrackRequest;
import crackhash.manager.model.entities.RequestStatus;

import java.util.List;



public interface CrackRequestRepo extends MongoRepository<CrackRequest, String> {
  List<CrackRequest> findByTotalParts(Integer totalParts);
  List<CrackRequest> findByStatusAndTotalPartsNot(RequestStatus status, Integer totalParts);
}
