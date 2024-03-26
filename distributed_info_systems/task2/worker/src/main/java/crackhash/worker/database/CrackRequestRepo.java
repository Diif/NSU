package crackhash.worker.database;

import org.springframework.data.mongodb.repository.MongoRepository;

import crackhash.worker.model.entities.CrackRequest;


public interface CrackRequestRepo extends MongoRepository<CrackRequest, String> {
  
}
