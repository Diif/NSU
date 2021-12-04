#include "player.h"

Player& PlayerFactory::CreatePlayer(PlayerType type) {
  if (type == PLAYER) {
    return *(new RealPlayer{});
  }
  if (type == SMART) {
    return *(new SmartPlayer{});
  }
  if (type == RANDOM) {
    return *(new RandomPlayer{});
  }
}