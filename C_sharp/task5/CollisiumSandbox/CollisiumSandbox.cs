namespace GameStuff;
using GameStuff.Cards;

public class CollisiumSandbox : ICollisiumSandbox
{
  public bool PlayRound(IPlayer p1, IPlayer p2,IDeckShuffler shuffler, Card[] deck)
  {
    shuffler.ShuffleDeck(deck);
    DeckStuff.SplitDeck(deck, out Card[] p1Cards, out Card[] p2Cards);
    var player1Guess = p1.Pick(p1Cards);
    var player2Guess = p2.Pick(p2Cards);
    if (p2Cards[player1Guess.Result] == p1Cards[player2Guess.Result])
    {
      return true;
    }
    return false;
  }
}