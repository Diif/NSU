using GameStuff.Cards;

namespace GameStuff;
public interface IPlayer
{
  Task SendRequest(int Id, Card[] cards);
}