#ifndef COORDINATES_H_
#define COORDINATES_H_
class Coordinates {
 private:
  int x = 0;
  int y = 0;

 public:
  Coordinates();
  ~Coordinates();
  void SetCoordinates(char clmn, int row);
  void SetAbsCoordinates(int column, int row);
  void SetByTitle(int title);
  int GetTitleByCoords();
  int GetX();
  int GetY();
};

#endif  // GAME_FIELD_H