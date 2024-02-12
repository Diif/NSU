using System.Collections.Concurrent;
using GameStuff.Cards;

namespace MuskApp;
public class ResultWrapper
{
  public readonly ConcurrentDictionary<int,Card[]> Decks = new();

}