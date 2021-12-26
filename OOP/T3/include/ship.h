#ifndef SHIPS_H_
#define SHIPS_H_

class Ship {
 private:
  int size;
  int angle;

 public:
  Ship(int size);
  ~Ship();
  int GetSize();
  int GetAngle();
  void RotateClockwise();
  void RotateCounterClockwise();
};

#endif  // SHIPS_H_