using GameStuff.Cards;

namespace GameStuff;
public interface IPlayer
{
  Task<int> Pick(Card[] cards);
}