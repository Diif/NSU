namespace Strategies;
using GameStuff;
public class StrategiesFactory
{
  public StrategiesFactory(IEnumerable<ICardPickStrategy> inner)
  {

  }
  public ICardPickStrategy GetMarkStr()
  {
    return new Str2();
  }

  public ICardPickStrategy GetMuskStr()
  {
    return new Str2();
  }
}