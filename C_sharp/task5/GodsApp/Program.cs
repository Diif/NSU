using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using GameStuff;
using DbStuff;
using CollisiumStuff;
using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Hosting;

class Program
{
  // todo 3 отдельных аппы, на контролленрах , хттпКлиент вставлять через специальный метод DiC

  public static void Main(string[] args)
  {
    var muskUrl = new Func<IConfiguration, string>(conf => (string)conf.GetValue(typeof(string), "MuskUrl")!);
    var muskStr = new Func<Strategies.StrategiesFactory,ICardPickStrategy>((f) => f.GetMuskStr());

    var markUrl = new Func<IConfiguration, string>(conf => (string)conf.GetValue(typeof(string), "MarkUrl")!);
    var markStr = new Func<Strategies.StrategiesFactory,ICardPickStrategy>((f) => f.GetMarkStr());

    Thread markThread = StartPlayerThread(args, markUrl, markStr);
    Thread muskThread = StartPlayerThread(args, muskUrl, muskStr);
    Thread.Sleep(1500);

    Thread godsThread = StartGodsThread(args, markUrl, muskUrl);
  }

  private static Thread StartPlayerThread(
    string[] args,
    Func<IConfiguration, string> url,
    Func<Strategies.StrategiesFactory,ICardPickStrategy> str
    )
  {
    Thread thread = new( () => CreateHostBuilderPlayer(args,url,str).Build().Run());
    thread.Start();
    return thread;
  }

   private static IHostBuilder CreateHostBuilderPlayer(
    string[] args,
    Func<IConfiguration, string> getUrl,
    Func<Strategies.StrategiesFactory,ICardPickStrategy> getStragy )        	
  {
    return Host.CreateDefaultBuilder(args)
      .ConfigureServices((hostContext, services) =>
        {
          services.AddHostedService<Web.Services.PlayerWebService>();
          services.AddSingleton<Strategies.StrategiesFactory>();
          services.AddSingleton(getUrl);
          services.AddSingleton(getStragy);
        });
  }

  private static Thread StartGodsThread(
    string[] args,
    Func<IConfiguration, string> p1Url,
    Func<IConfiguration, string> p2Url )
  {
    Thread godThread = new( () => CreateHostBuilderGods(args,p1Url,p2Url).Build().Run());
    godThread.Start();
    return godThread;
  }
  private static IHostBuilder CreateHostBuilderGods(
    string[] args,
    Func<IConfiguration, string> p1Url,
    Func<IConfiguration, string> p2Url)        	
  {
    return Host.CreateDefaultBuilder(args)
      .ConfigureServices((hostContext, services) =>
        {
          services.AddHostedService<Collisium>();
          services.AddSingleton(p1Url);
          services.AddSingleton(p2Url);
          services.AddSingleton<HttpClient>();
          services.AddHttpClient();
          services.AddSingleton<IPlayerFactory,Web.Players.HttpPlayerFactory>();
          services.AddScoped<ICollisiumWorker,CollisiumWithDbWorker>();
          services.AddScoped<CollisiumSandbox>();
          services.AddDbContext<DbStuff.Model.ExperimentContext>(o => o.UseSqlite(
            hostContext.Configuration.GetConnectionString("ExperimentContext")));
          services.AddScoped<IDeckShuffler,IdentityDeckShuffler>();
          services.AddScoped<ExperimentUtils>();
        });
  }
}
