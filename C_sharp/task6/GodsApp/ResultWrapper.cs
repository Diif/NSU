using System.Collections.Concurrent;
using SharedModel.Model.Dtos;

namespace GodsApp;

class ResultWrapper : IDisposable
{
  public readonly BlockingCollection<AnswerCardDto> Queue;

  public int Match = 0;
  public int Total = 0;

  public ResultWrapper()
  {
    Queue = new BlockingCollection<AnswerCardDto>(new ConcurrentQueue<AnswerCardDto>());
  }

    public void Dispose()
    {
      Queue.Dispose();
    }
}