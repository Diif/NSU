using GameStuff.Cards;

namespace GameStuff;
public interface ICardPickStrategy
{
  int Pick(Card[] cards);
}