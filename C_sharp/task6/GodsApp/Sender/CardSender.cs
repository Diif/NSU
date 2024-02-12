using MassTransit;
using SharedModel.Model.Messages;

namespace GodsApp.Sender;

class CardSender : ICardSender
{
  private readonly IBus _bus;

  public CardSender(IBus bus)
  {
    _bus = bus;
  }

  public async Task SendCommand(ChooseCard command, Uri uri)
  {
    var endpoint = await _bus.GetSendEndpoint(uri);
    await endpoint.Send(command);
  }

}