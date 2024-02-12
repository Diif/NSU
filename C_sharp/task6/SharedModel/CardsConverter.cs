using System.Text;
using GameStuff.Cards;

namespace SharedModel;


public static class CardsExtension
{
  public static string CardsToString(this Card[] cards)
  {
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
    return stringBuilder.ToString();
  }

  public static Card[] StringToCards(this string cardsStr)
  {
    Card[] cards = new Card[cardsStr.Length];
    int ind = 0;
    foreach (char c in cardsStr)
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
}