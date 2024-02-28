package crackhash.worker.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import crackhash.worker.model.dtos.CrackRequestDto;
import crackhash.worker.services.ICrackRequestService;

@RestController
public class CrackController {
	
	@Autowired
	private final ICrackRequestService service;

	public CrackController(ICrackRequestService service){
		this.service = service;
	}

  @PostMapping(value = "internal/api/worker/hash/crack/task")
	public ResponseEntity<Void> postTask(@RequestBody CrackRequestDto crackReques){
		service.addRequest(crackReques);
		return new ResponseEntity<>(HttpStatus.OK);
	}
}