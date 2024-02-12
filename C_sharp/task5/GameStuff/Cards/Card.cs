namespace GameStuff.Cards;

public record Card(CardColor Color)
{
  public override string ToString()
  {
        return Color == CardColor.Black ? "BLACK" : "RED";
  }
}