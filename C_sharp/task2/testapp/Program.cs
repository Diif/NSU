using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
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
          // services.AddScoped<CollisiumSandbox>();
          // services.AddScoped<IDeckShufller, DeckShufller>();
          // Зарегистрировать партнеров и их стратегии
          });

  }
}
