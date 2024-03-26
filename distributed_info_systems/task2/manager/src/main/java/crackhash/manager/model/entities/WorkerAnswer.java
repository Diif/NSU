package crackhash.manager.model.entities;

import java.util.ArrayList;

import org.springframework.data.annotation.Id;

public record WorkerAnswer(@Id String id, String partId,Integer workerNum, AnswerStatus status, ArrayList<String> data) {}
