using DbStuff.Model;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Storage;
using GameStuff;
using GameStuff.Cards;
using System.Text;


namespace DbStuff;
public class ExperimentUtils : IDisposable
{
  private readonly ExperimentContext _db;

  private readonly int _NUM_CARDS;

  public ExperimentUtils(IConfiguration configuration, ExperimentContext db)
  {
    _db = db;
    db.Database.EnsureDeleted();
    db.Database.EnsureCreated();
    
    _NUM_CARDS = (int)configuration.GetValue(typeof(int), "MaxCards")!;
  }

  ~ExperimentUtils()
  {
    _db.Dispose();
  }

  public void Dispose()
  {
    _db.Dispose();
    GC.SuppressFinalize(this);
  }
  public void ClearExperiments()
  {
    _db.Experiments.Where(o => true).ExecuteDelete();
  }

    public void GenerateExperiments(int num, IDeckShuffler shuffler)
  {
    Card[] deck = DeckStuff.CreateDeck(_NUM_CARDS);
    StringBuilder stringBuilder = new();
    while (num-->0)
    {
      shuffler.ShuffleDeck(deck);
      foreach (var card in deck)
      {
        switch (card.Color)
        {
          case CardColor.Red:
            stringBuilder.Append('R');
            break;
          case CardColor.Black:
            stringBuilder.Append('B');
            break;
        }
      }
      _db.Add(new ExperimentEntity(){Cards = stringBuilder.ToString()});
      stringBuilder.Clear();
    }
    _db.SaveChanges();
  }

  public List<Card[]> GetExperiments()
  {
    var dbSet = _db.Experiments;
    List<Card[]> res = new();
    foreach (var ent in dbSet)
    {
      res.Add((Card[])ent);
    }
    return res;
  }
}