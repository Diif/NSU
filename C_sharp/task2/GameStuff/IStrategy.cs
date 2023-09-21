namespace GameStuff;
public interface IStrategy
{
  public int Player1Pick(ArraySegment<Cards> cards);
  public int Player2Pick(ArraySegment<Cards> cards);
}