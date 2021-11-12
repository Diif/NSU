#ifndef FACTORIES_H_
#define FACTORIES_H_

#include "workers.h"

class BaseFactory {
 public:
  virtual Worker* CreateWorker(std::vector<std::string>& args) = 0;
};

class ReadFactory : public BaseFactory {
 public:
  Worker* CreateWorker(std::vector<std::string>& args) override;
};

class WriteFactory : public BaseFactory {
 public:
  Worker* CreateWorker(std::vector<std::string>& args) override;
};

class GrepFactory : public BaseFactory {
 public:
  Worker* CreateWorker(std::vector<std::string>& args) override;
};

class SortFactory : public BaseFactory {
 public:
  Worker* CreateWorker(std::vector<std::string>& args) override;
};

class ReplaceFactory : public BaseFactory {
 public:
  Worker* CreateWorker(std::vector<std::string>& args) override;
};

class DumpFactory : public BaseFactory {
 public:
  Worker* CreateWorker(std::vector<std::string>& args) override;
};

#endif  //  FACTORIES_H_
