#include "workers.h"

class BaseFactory {
 public:
  virtual Worker* CreateWorker() = 0;
};

class RdFactory : BaseFactory {};

class WrFactory : BaseFactory {};

class GrFactory : BaseFactory {};

class SrtFactory : BaseFactory {};

class RplFactory : BaseFactory {};

class DpFactory : BaseFactory {};