#ifndef WORKFLOW_EXECUTOR_H_
#define WORKFLOW_EXECUTOR_H_

#include <map>

#include "workers.h"
class WorkflowExecutor {
 private:
  std::vector<int> operations_order_;
  std::map<int, Worker*> workers_;
  int PopOperation();
  Worker* GetWorker(int id);

 public:
  WorkflowExecutor();
  ~WorkflowExecutor();
  bool IsIdFree(int id);
  void PutWorker(int id, Worker* worker);
  void PushOperation(int ind);
  void Execute();
};
#endif  // WORKFLOW_EXECUTOR_H_