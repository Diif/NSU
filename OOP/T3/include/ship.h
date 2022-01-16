#ifndef SHIPS_H_
#define SHIPS_H_

class Ship {
 private:
  int size_;
  int angle_;

 public:
  enum ShipType {
    TORPEDO_BOAT = 1,
    DESTROYER = 2,
    CRUISER = 3,
    BATTLESHIP = 4
  };

  Ship(int size);
  ~Ship();
  int GetSize();
  int GetAngle();
  void ChangeShip(ShipType type);
  void RotateClockwise();
  void RotateCounterClockwise();
  void RestoreAngle();
};

#endif  // SHIPS_H_