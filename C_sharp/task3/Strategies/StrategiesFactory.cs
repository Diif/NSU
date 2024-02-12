namespace Strategies;
using GameStuff;
public class StrategiesFactory
{
  public ICardPickStrategy GetMarkStr()
  {
    return new Random();
  }

  public ICardPickStrategy GetMuskStr()
  {
    return new Random();
  }
}