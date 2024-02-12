using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Configuration;
using GameStuff;
using static GameStuff.DeckStuff;

namespace CollisiumStuff;
internal class Collisium : IHostedService
{

  private readonly ICollisiumWorker _collisiumWorker;


  public Collisium(ICollisiumWorker worker)
  {
    _collisiumWorker = worker;
  }

  public Task StartAsync(CancellationToken cancellationToken)
  {
    return _collisiumWorker.DoTask();
  }

  public Task StopAsync(CancellationToken cancellationToken)
  {
    return Task.CompletedTask;
  }

}