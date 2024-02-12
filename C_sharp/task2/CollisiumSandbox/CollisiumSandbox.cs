namespace GameStuff;
using GameStuff.Cards;

public class CollisiumSandbox
{
  public bool PlayRound(ICardPickStrategy p1Strat, ICardPickStrategy p2Strat, Card[] p1Cards, Card[] p2Cards)
  {
    int player1Guess = p1Strat.Pick(p1Cards);
    int player2Guess = p2Strat.Pick(p2Cards);
    if (p2Cards[player1Guess] == p1Cards[player2Guess])
    {
      return true;
    }
    return false;
  }
}