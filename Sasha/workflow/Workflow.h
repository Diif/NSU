#ifndef WORKFLOW_H
#define WORKFLOW_H
#include <map>

#include "Worker.h"

using namespace std;

class Workflow {
  map<int, Worker*> workers_;
};

#endif  // WORKFLOW_H