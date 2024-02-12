using System.Text;
using GameStuff.Cards;

namespace Web.Dto;

public record ExperimentDto(string Cards)
{
  public static explicit operator Card[] (ExperimentDto e)
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
          _ => throw new System.Runtime.CompilerServices.SwitchExpressionException(c)
      };
    }
    return cards;
  }

  public static explicit operator ExperimentDto (Card[] cards)
  {
    _ = cards ?? throw new ArgumentNullException(nameof(cards));
    
    StringBuilder stringBuilder = new();
    foreach (var card in cards)
      {
        switch (card.Color)
        {
          case CardColor.Red:
            stringBuilder.Append('R');
            break;
          case CardColor.Black:
            stringBuilder.Append('B');
            break;
        }
      }
    
    return new ExperimentDto(Cards: stringBuilder.ToString());
  }
}