using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Configuration;
using GameStuff;
using static GameStuff.DeckStuff;
using DbStuff;
using GameStuff.Cards;
namespace CollisiumStuff;
public class CollisiumWithDbWorker : ICollisiumWorker
{

  private readonly CollisiumSandbox _collisiumSandbox;
  private readonly IDeckShuffler _deckShuffler;
  private readonly IPlayer _p1;
  private readonly IPlayer _p2;
  private readonly ExperimentUtils _utils;
  
  public CollisiumWithDbWorker(
    CollisiumSandbox collisiumSandbox,
    IDeckShuffler deckShuffler,
    IPlayerFactory playerFactory,
    ExperimentUtils utils
    )
  {
    _collisiumSandbox = collisiumSandbox;
    _deckShuffler = deckShuffler;
    _p1 = playerFactory.GetPlayer1();
    _p2 = playerFactory.GetPlayer2();
    _utils = utils;
  }

  public Task DoTask()
  {
    var exps = _utils.GetExperiments();
    int MAX_ITER = exps.Count;
    int matches = 0;
    for (int i = 0; i < MAX_ITER; i++)
    {
      if (_collisiumSandbox.PlayRound(_p1,_p2, _deckShuffler, (Card[])exps[i]))
      {
        matches++;
      }
    }

    Console.WriteLine(((double) matches / MAX_ITER) * 100 + " %");
    return Task.CompletedTask;
  }
  
}