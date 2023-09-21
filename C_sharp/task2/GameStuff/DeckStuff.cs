namespace GameStuff;
public static class DeckStuff
{

  private static readonly Random _random = new();
  private static Cards[] _deck;
  public static ArraySegment<GameStuff.Cards> Deck {get; private set;}
  static DeckStuff()
  {
    const int MAX_CARDS = 32;
    _deck = new Cards[MAX_CARDS];
    Deck = new ArraySegment<GameStuff.Cards>(_deck);
    ShuffleDeck(_deck);
  }

  public static ArraySegment<GameStuff.Cards> ResizeDeck(int size)
  {
    _deck = new Cards[size];
    Deck = new ArraySegment<GameStuff.Cards>(_deck);
    ShuffleDeck(Deck);
    return Deck;
  }

  public static void ShuffleDeck(ArraySegment<GameStuff.Cards> deck)
  {
    int redCount = 0;
    int blackCount = 0;

    int half = deck.Count / 2;

    for (int i = 0; i < deck.Count; i++)
    {
      if (redCount == half)
      {
        deck[i] = Cards.Black;
        blackCount++;
      }
      else if (blackCount == half)
      {
        deck[i] = Cards.Red;
        redCount++;
      }
      else 
      {
        if (_random.Next((int)Cards.Black, (int) Cards.Red + 1) == (int) Cards.Black)
        {
          deck[i] = Cards.Black;
          blackCount++;
        }
        else
        {
          deck[i] = Cards.Red;
          redCount++;
        }
      }
    }
  }

  public static void SplitDeck(in ArraySegment<GameStuff.Cards> deck, out ArraySegment<GameStuff.Cards> part1, out ArraySegment<GameStuff.Cards> part2)
  {
    if (deck.Array is null)
    {
      throw new ArgumentNullException(nameof(deck));
    }
    part1 = new ArraySegment<GameStuff.Cards>(deck.Array, deck.Offset, deck.Count / 2);
    part2 = new ArraySegment<GameStuff.Cards>(deck.Array, deck.Offset + deck.Count / 2, deck.Count /2 );
  }

}