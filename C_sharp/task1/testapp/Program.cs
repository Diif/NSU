class Program
{
  public static void Main(string[] args)
  {

    GameStuff.IStrategy random = Strategies.StrategiesFactory.random;

    var deck = GameStuff.DeckStuff.Deck;

    GameStuff.DeckStuff.SplitDeck(deck, out ArraySegment<GameStuff.Cards> part1, out ArraySegment<GameStuff.Cards> part2);

    int matches = 0;
    const int NUM_GAMES = 1000000;
    for (int i = 0; i < NUM_GAMES; i++)
    {
      GameStuff.DeckStuff.ShuffleDeck(deck);
      int player1Guess = random.Player1Pick(part1);
      int player2Guess = random.Player2Pick(part2);
      if (part2[player1Guess] == part1[player2Guess])
      {
        matches++;
      }
    }

    Console.WriteLine("Res: " + (double) matches / NUM_GAMES* 100 + "%");

  }
}
