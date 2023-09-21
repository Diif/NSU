using Microsoft.Extensions.Hosting;

public class CollisiumExperimentWorker : IHostedService
{
  public Task StartAsync(CancellationToken cancellationToken)
  {
    System.Console.WriteLine("SETSTSTFD");
    return Task.CompletedTask;
  }

  public Task StopAsync(CancellationToken cancellationToken)
  {
    return Task.CompletedTask;
  }

}