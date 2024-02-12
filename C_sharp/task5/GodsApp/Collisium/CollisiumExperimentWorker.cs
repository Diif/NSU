using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Configuration;
using GameStuff;
using static GameStuff.DeckStuff;
using System.Runtime.CompilerServices;
using GameStuff.Cards;
namespace CollisiumStuff;
public class CollisiumExperimentWorker : ICollisiumWorker
{

  private readonly CollisiumSandbox _collisiumSandbox;
  private readonly IDeckShuffler _deckShuffler;
  
  private IPlayer Musk {get; init;}
  private IPlayer Mark {get; init;}
  private readonly IConfiguration _configuration;
  

  public CollisiumExperimentWorker(
    CollisiumSandbox collisiumSandbox,
    IDeckShuffler deckShuffler,
    IPlayerFactory factory,
    IConfiguration configuration
    )
  {
    _collisiumSandbox = collisiumSandbox;
    _deckShuffler = deckShuffler;
    Mark = factory.GetPlayer1();
    Musk = factory.GetPlayer2();
    _configuration = configuration;
  }
    public Task DoTask()
  {
    int MAX_ITER = (int)_configuration.GetValue(typeof(int), "MatchesToPlay")!;
    int matches = 0;
    var deck = CreateDeck((int)_configuration.GetValue(typeof(int), "MaxCards")!);
    for (int i = 0; i < MAX_ITER; i++)
    {
      if (_collisiumSandbox.PlayRound(Musk, Mark, _deckShuffler, deck))
      {
        matches++;
      }
    }

    Console.WriteLine(((double) matches / MAX_ITER) * 100 + " %");
    return Task.CompletedTask;
  }
  
}