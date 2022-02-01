#include "workflow_executor.h"

void WorkflowExecutor::PutWorker(int id, Worker* worker) {
  workers_[id] = worker;
}

Worker* WorkflowExecutor::GetWorker(int id) { return workers_[id]; }

bool WorkflowExecutor::IsIdFree(int id) {
  int count = workers_.count(id);
  if (count) {
    return false;
  }
  return true;
}

void WorkflowExecutor::Execute() {
  std::vector<std::string> text_in_lines;
  for (size_t i = operations_order_.size(); i; i--) {
    int worker_id = PopOperation();
    int count = workers_.count(worker_id);
    if (count != 1) {
      throw(SequenceStructureException());
    }
    Worker* cur_worker = GetWorker(worker_id);
    cur_worker->Run(text_in_lines);
  }
}

void WorkflowExecutor::PushOperation(int ind) {
  operations_order_.push_back(ind);
}

int WorkflowExecutor::PopOperation() {
  int operation = operations_order_[0];
  operations_order_.erase(operations_order_.begin());
  return operation;
}

WorkflowExecutor::WorkflowExecutor() {}

WorkflowExecutor::~WorkflowExecutor() {
  std::map<int, Worker*>::iterator iter = workers_.begin();
  std::map<int, Worker*>::iterator end = workers_.end();
  while (iter != end) {
    delete (iter->second);
  }
}
