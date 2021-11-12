#include "factories.h"

Worker* ReadFactory::CreateWorker(std::vector<std::string>& args) {
  return new ReadWorker{args};
}
Worker* WriteFactory::CreateWorker(std::vector<std::string>& args) {
  return new WriteWorker{args};
}
Worker* GrepFactory::CreateWorker(std::vector<std::string>& args) {
  return new GrepWorker{args};
}
Worker* SortFactory::CreateWorker(std::vector<std::string>& args) {
  return new SortWorker{args};
}
Worker* ReplaceFactory::CreateWorker(std::vector<std::string>& args) {
  return new ReplaceWorker{args};
}
Worker* DumpFactory::CreateWorker(std::vector<std::string>& args) {
  return new DumpWorker{args};
}
