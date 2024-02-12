namespace GameStuff;

using GameStuff.Cards;
public static class DeckStuff
{
  private static readonly int _MAX_CARDS = 32;
  public static readonly Card[] Deck;
  static DeckStuff()
  {
    Deck = new Card[_MAX_CARDS];
    for(int i = 0; i < _MAX_CARDS; i+=2)
    {
      Deck[i] = new Card(CardColor.Black);
      Deck[i+1] = new Card(CardColor.Red);
    }
  }

  public static void SplitDeck(out Card[] part1, out Card[] part2)
  {
    int half = _MAX_CARDS / 2;
    part1 = new Card[half];
    part2 = new Card[half];
    for (int i = 0; i < half; i++)
    {
      part1[i] = Deck[i];
      part2[i] = Deck[half + i];
    }
  }

}