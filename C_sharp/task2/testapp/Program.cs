using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using GameStuff;
class Program
{
  public static void Main(string[] args)
  {
    CreateHostBuilder(args).Build().Run();
  }

   public static IHostBuilder CreateHostBuilder(string[] args)        	
  {
    return Host.CreateDefaultBuilder(args)
      .ConfigureServices((hostContext, services) =>
        {
          services.AddHostedService<CollisiumExperimentWorker>();
          services.AddScoped<CollisiumSandbox>();
          services.AddScoped<IDeckShuffler,DeckShuffler>();
          // services.AddScoped<ICardPickStrategy, Strategies.Random>();
          // services.AddScoped<ICardPickStrategy, Strategies.Random>();
          // Maybe just replace with transient strategy?
          services.AddScoped<Strategies.StrategiesFactory>();
          });
  }
}
