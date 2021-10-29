class Worker {
 public:
  virtual void run() = 0;
};

class RdWorker : public Worker {
 public:
  void run() { int a; }
};

class WrWorker : public Worker {
 public:
  void run() { int a; }
};

class GrWorker : public Worker {
 public:
  void run() { int a; }
};

class SrtWorker : public Worker {
 public:
  void run() { int a; }
};

class RplWorker : public Worker {
 public:
  void run() { int a; }
};

class DpWorker : public Worker {
 public:
  void run() { int a; }
};
