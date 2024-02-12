using System.Runtime.CompilerServices;
using GameStuff.Cards;

namespace DbStuff.Model;

public class ExperimentEntity
{
  public int Id { get; set;}
  public string Cards { get; set;} 

  public static explicit operator Card[] (ExperimentEntity e)
  {
    _ = e ?? throw new ArgumentNullException(nameof(e));
    
    Card[] cards = new Card[e.Cards.Length];
    int ind = 0;
    foreach (char c in e.Cards)
    {
      cards[ind++] = c switch
      {
          'B' => new Card(CardColor.Black),
          'R' => new Card(CardColor.Red),
          _ => throw new SwitchExpressionException(c)
      };
    }
    return cards;
  }

}
