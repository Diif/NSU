package crackhash.worker.services;

import crackhash.worker.model.dtos.CrackRequestDto;

public interface ICrackRequestService {
  void addRequest(CrackRequestDto crackReques);
} 