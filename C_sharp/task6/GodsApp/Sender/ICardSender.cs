using MassTransit;
using SharedModel.Model.Messages;

namespace GodsApp.Sender;

interface ICardSender
{

  Task SendCommand(ChooseCard command,Uri uri);

}