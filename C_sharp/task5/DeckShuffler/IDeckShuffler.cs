namespace GameStuff;

using GameStuff.Cards;

public interface IDeckShuffler
{
  void ShuffleDeck(Card[] deck);
}