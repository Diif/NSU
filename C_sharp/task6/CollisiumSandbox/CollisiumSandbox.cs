namespace GameStuff;
using GameStuff.Cards;

public class CollisiumSandbox : ICollisiumSandbox
{

  public void AskPlayers(IPlayer p1, IPlayer p2,IDeckShuffler shuffler, Card[] deck, int id)
  {
    shuffler.ShuffleDeck(deck);
    DeckStuff.SplitDeck(deck, out Card[] p1Cards, out Card[] p2Cards);

    p1.SendRequest(id, p1Cards);
    p2.SendRequest(id, p2Cards);
  }
}