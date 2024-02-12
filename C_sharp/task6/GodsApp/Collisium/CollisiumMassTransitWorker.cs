using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Configuration;
using GameStuff;
using static GameStuff.DeckStuff;
using System.Runtime.CompilerServices;
using GameStuff.Cards;
using SharedModel.Model.Dtos;
namespace GodsApp.Collisium;
class CollisiumMassTransitWorker : ICollisiumWorker
{

  private readonly ICollisiumSandbox _collisiumSandbox;
  private readonly IDeckShuffler _deckShuffler;
  
  private IPlayer Musk {get; init;}
  private IPlayer Mark {get; init;}
  private readonly IConfiguration _configuration;
  private readonly ResultWrapper _result;
  

  public CollisiumMassTransitWorker(
    ICollisiumSandbox collisiumSandbox,
    IDeckShuffler deckShuffler,
    IPlayerFactory factory,
    IConfiguration configuration,
    ResultWrapper result
    )
  {
    _collisiumSandbox = collisiumSandbox;
    _deckShuffler = deckShuffler;
    Mark = factory.GetMark();
    Musk = factory.GetMusk();
    _configuration = configuration;
    _result = result;
  }
    public Task DoTask()
  {
    int MAX_ITER = (int)_configuration.GetValue(typeof(int), "MatchesToPlay")!;
    var deck = CreateDeck((int)_configuration.GetValue(typeof(int), "MaxCards")!);

    for (int i = 0; i < MAX_ITER; i++)
    {
      _collisiumSandbox.AskPlayers(Musk, Mark, _deckShuffler, deck,i);
    }

    Console.WriteLine(HandleResponses(MAX_ITER) + "%");
    
    return Task.CompletedTask;
  }

  private double HandleResponses(int MAX_ITER)
  {
    Dictionary<int, CardColor> map = new();

    int WAIT_TIME_MILL = 60000;
    while(CheckExitCond(MAX_ITER) && _result.Queue.TryTake(out var ans,WAIT_TIME_MILL))
    {
      HandleMapWithAns(map, ans);
    }

    return _result.Total != 0 ?
      (double) _result.Match / _result.Total * 100  :
      0;
    
  }

  private bool CheckExitCond(int MAX_ITER)
  {
    return _result.Total != MAX_ITER;
  } 
  
  private void HandleMapWithAns(Dictionary<int, CardColor> map, AnswerCardDto ans)
  {
    if (map.TryGetValue(ans!.Id, out var partRes))
      {
        if (partRes == ans.Color)
        {
          _result.Match += 1;
        }
        _result.Total += 1;
        map.Remove(ans.Id);
      }
      else
      {
        map[ans.Id] = ans.Color;
      }
  }

}