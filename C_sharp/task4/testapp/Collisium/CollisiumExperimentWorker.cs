using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Configuration;
using GameStuff;
using static GameStuff.DeckStuff;
namespace CollisiumStuff;
public class CollisiumExperimentWorker : ICollisiumWorker
{

  private readonly CollisiumSandbox _collisiumSandbox;
  private readonly IDeckShuffler _deckShuffler;
  
  private readonly ICardPickStrategy _muskStr;
  private readonly ICardPickStrategy _markStr;
  private readonly IConfiguration _configuration;
  

  public CollisiumExperimentWorker(
    CollisiumSandbox collisiumSandbox,
    IDeckShuffler deckShuffler,
    Strategies.StrategiesFactory factory,
    IConfiguration configuration
    )
  {
    _collisiumSandbox = collisiumSandbox;
    _deckShuffler = deckShuffler;
    _muskStr = factory.GetMarkStr();
    _markStr = factory.GetMuskStr();
    _configuration = configuration;
  }

  public Task DoTask()
  {
    int MAX_ITER = (int)_configuration.GetValue(typeof(int), "MatchesToPlay")!;
    int matches = 0;
    var deck = CreateDeck((int)_configuration.GetValue(typeof(int), "MaxCards")!);
    for (int i = 0; i < MAX_ITER; i++)
    {
      if (_collisiumSandbox.PlayRound(_muskStr, _markStr, _deckShuffler, deck))
      {
        matches++;
      }
    }

    Console.WriteLine(((double) matches / MAX_ITER) * 100 + " %");
    return Task.CompletedTask;
  }
  
}