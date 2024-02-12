namespace GameStuff;

using GameStuff.Cards;
public static class DeckStuff
{
  private static readonly int _MAX_CARDS = 32;
  public static Card[] CreateDeck()
  {
    var deck = new Card[_MAX_CARDS];
    for(int i = 0; i < _MAX_CARDS; i+=2)
    {
      deck[i] = new Card(CardColor.Black);
      deck[i+1] = new Card(CardColor.Red);
    }
    return deck;
  }

  public static void SplitDeck(in Card[] deck, out Card[] part1, out Card[] part2)
  {
    int half = _MAX_CARDS / 2;
    part1 = new Card[half];
    part2 = new Card[half];
    for (int i = 0; i < half; i++)
    {
      part1[i] = deck[i];
      part2[i] = deck[half + i];
    }
  }

}