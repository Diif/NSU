namespace Strategies;

internal class Random : GameStuff.IStrategy
{
  private static readonly System.Random _random = new();
  public int Player1Pick(ArraySegment<GameStuff.Cards> cards)
  {
    return 0;
    // return _random.Next(0, cards.Count);
  }
  public int Player2Pick(ArraySegment<GameStuff.Cards> cards)
  {
    return 0;
    // return _random.Next(0, cards.Count);
  }


}
