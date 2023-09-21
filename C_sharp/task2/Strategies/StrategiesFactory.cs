namespace Strategies;

public static class StrategiesFactory
{
  public static readonly GameStuff.IStrategy random = new Random();

}