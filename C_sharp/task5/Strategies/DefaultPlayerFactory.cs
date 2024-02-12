using GameStuff;
using GameStuff.Cards;

namespace Strategies;

class DefaultPlayerFactory : IPlayerFactory
  {
    private readonly StrategiesFactory _strategiesFactory;
    public DefaultPlayerFactory(StrategiesFactory strategiesFactory)
    {
      _strategiesFactory =  strategiesFactory;
    }
    class Player : IPlayer
    {
      private ICardPickStrategy Strategy {get;init;}
      public Player(ICardPickStrategy strategy)
      {
        Strategy = strategy;
      }
        public Task<int> Pick(Card[] cards)
        {
            return Task.FromResult(Strategy.Pick(cards));
        }
    }

    public IPlayer GetPlayer1()
    {
        return new Player(_strategiesFactory.GetMuskStr());
    }

    public IPlayer GetPlayer2()
    {
        return new Player(_strategiesFactory.GetMarkStr());
    }
}