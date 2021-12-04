#ifndef SHIPS_H_
#define SHIPS_H_

class Ship {
 private:
  int size;
  int angle;

 public:
  Ship(int size);
  ~Ship();
  void RotateClockwise();
  void RotateCounterClockwise();
};

Ship::Ship(int size) : size(size), angle(0) {}

Ship::~Ship() {}

#endif  // SHIPS_H_