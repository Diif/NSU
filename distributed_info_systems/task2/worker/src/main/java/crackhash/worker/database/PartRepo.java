package crackhash.worker.database;

import org.springframework.data.mongodb.repository.MongoRepository;

import crackhash.worker.model.entities.RequestPart;


public interface PartRepo extends MongoRepository<RequestPart, String> {
  
}
