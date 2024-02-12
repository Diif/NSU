using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Configuration;
using GameStuff;
using DbStuff;

namespace CollisiumStuff;
public class CollisiumDbExperimentWorker : ICollisiumWorker
{

  private readonly CollisiumSandbox _collisiumSandbox;
  private readonly IDeckShuffler _deckShuffler;
  
  private readonly IPlayer _p1;
  private readonly IPlayer _p2;
  private readonly IConfiguration _configuration;
  private readonly ExperimentUtils _experimentUtils;
  

  public CollisiumDbExperimentWorker(
    CollisiumSandbox collisiumSandbox,
    IDeckShuffler deckShuffler,
    IPlayerFactory factory,
    IConfiguration configuration,
    ExperimentUtils experimentUtils
    )
  {
    _collisiumSandbox = collisiumSandbox;
    _deckShuffler = deckShuffler;
    _p1 = factory.GetPlayer1();
    _p2 = factory.GetPlayer2();
    _configuration = configuration;
    _experimentUtils = experimentUtils;
  }

  public Task DoTask()
  {
    int NUM_EXPERIMENTS = (int)_configuration.GetValue(typeof(int), "DbExperimentsMatches")!;

    _experimentUtils.ClearExperiments();
    _experimentUtils.GenerateExperiments(NUM_EXPERIMENTS, _deckShuffler);
    int matches = 0;
    var exprs = _experimentUtils.GetExperiments();
    foreach(var e in exprs)
    {
      if (_collisiumSandbox.PlayRound(_p1, _p2,_deckShuffler, e))
      {
        matches++;
      }
    }
    
    Console.WriteLine(((double) matches / NUM_EXPERIMENTS) * 100 + " %");
    return Task.CompletedTask;
  }
  
}