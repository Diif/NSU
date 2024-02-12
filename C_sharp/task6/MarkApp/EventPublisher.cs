using MassTransit;
using SharedModel.Model.Events;

namespace MarkApp;

class EventPublisher
{
  private readonly IBus _bus;

  public EventPublisher(IBus bus)
  {
    _bus = bus;
  }

  public async Task PublishEvent(CardChoosen evt)
  {
    await _bus.Publish(evt);
  }
   
}