namespace Web.Services;

using GameStuff;
using GameStuff.Cards;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
public class PlayerWebService : IHostedService
{
  private readonly ICardPickStrategy _strategy;
  private readonly string _url;
  public PlayerWebService(
    Func<IConfiguration,string> getUrl,
    Func<Strategies.StrategiesFactory, ICardPickStrategy> getStrategy,
    IConfiguration configuration,
    Strategies.StrategiesFactory factory)
  {
    _url = getUrl(configuration);
    _strategy = getStrategy(factory);
  }
  public Task StartAsync(CancellationToken cancellationToken)
  {
    var app = WebApplication.CreateBuilder().Build();
    app.MapPost("/", (Dto.ExperimentDto experiment) => 
    {
      Card[] cards = (Card[])experiment;
      return new Dto.AnswerDto(Number: _strategy.Pick(cards));
    });
    return app.RunAsync(_url);
  }

  public Task StopAsync(CancellationToken cancellationToken)
  {
    return Task.CompletedTask;
  }
}
