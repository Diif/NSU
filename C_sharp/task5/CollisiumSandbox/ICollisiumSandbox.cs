namespace GameStuff;
using GameStuff.Cards;

public interface ICollisiumSandbox
{
  bool PlayRound(IPlayer p1, IPlayer p2,IDeckShuffler shuffler, Card[] deck);
}