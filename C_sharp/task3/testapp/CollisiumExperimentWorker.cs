using Microsoft.Extensions.Hosting;
using GameStuff;
using static GameStuff.DeckStuff;

public class CollisiumExperimentWorker : IHostedService
{

  private readonly CollisiumSandbox _collisiumSandbox;
  private readonly IDeckShuffler _deckShuffler;
  
  private readonly ICardPickStrategy _muskStr;
  private readonly ICardPickStrategy _markStr;
  

  public CollisiumExperimentWorker(
    CollisiumSandbox collisiumSandbox,
    IDeckShuffler deckShuffler,
    Strategies.StrategiesFactory factory)
  {
    _collisiumSandbox = collisiumSandbox;
    _deckShuffler = deckShuffler;
    _muskStr = factory.GetMarkStr();
    _markStr = factory.GetMuskStr();
  }
  public Task StartAsync(CancellationToken cancellationToken)
  {
    const int MAX_ITER = 1000000;
    int matches = 0;
    var deck = CreateDeck();
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

  public Task StopAsync(CancellationToken cancellationToken)
  {
    return Task.CompletedTask;
  }

}