#include "game_field.h"
GameField::GameField(int field_size) { field_ = new char[field_size]; }

GameField::~GameField() { delete[] field_; }
