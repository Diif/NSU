using GameStuff.Cards;

namespace GameStuff;
public class RandomDeckShuffler : IDeckShuffler
{
  private static readonly Random _random = new();

  // Assumes that deck is correct
  public void ShuffleDeck(Card[] deck)
  {
    for (int i = 0; i < deck.Length; i++)
    {
      int place = _random.Next(0, deck.Length);
      (deck[i], deck[place]) = (deck[place], deck[i]);
    }
  }
}