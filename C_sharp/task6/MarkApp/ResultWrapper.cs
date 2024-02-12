using System.Collections.Concurrent;
using GameStuff.Cards;

namespace MarkApp;
public class ResultWrapper
{
  public readonly ConcurrentDictionary<int,Card[]> Decks = new();

}