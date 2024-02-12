using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using GameStuff;
using DbStuff;
using CollisiumStuff;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
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
          services.AddHostedService<Collisium>();
          services.AddScoped<ICollisiumWorker,CollisiumExperimentWorker>();
          services.AddScoped<ICollisiumWorker,CollisiumDbExperimentWorker>();
          services.AddScoped<CollisiumSandbox>();
          services.AddDbContext<DbStuff.Model.ExperimentContext>(o => o.UseSqlite(
            hostContext.Configuration.GetConnectionString("ExperimentContext")));
          services.AddScoped<IDeckShuffler,DeckShuffler>();
          services.AddScoped<Strategies.StrategiesFactory>();
          services.AddScoped<ExperimentUtils>();
          });
  }
}
