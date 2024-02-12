namespace Strategies;

using GameStuff.Cards;

public class Str2 : GameStuff.ICardPickStrategy
{
  public Str2()
  {
    
  }
  public int Pick(Card[] cards)
  {
   var a = cards.Length;
    while(a-->0)
    {
      if (cards[a].Color == CardColor.Black)
      {
        return a;
      }
    }
      
    
    return 0;
  }
}
