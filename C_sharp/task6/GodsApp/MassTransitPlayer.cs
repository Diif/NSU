namespace GodsApp;

using System.Threading.Tasks;
using GameStuff;
using GameStuff.Cards;
using GodsApp.Sender;
using SharedModel.Model.Messages;
using SharedModel;

class MassTransitPlayer : IPlayer
{
  private readonly Uri _uri;
  private readonly ICardSender _cardSender;
  public MassTransitPlayer(Uri uri, ICardSender cardSender)
  {
    _uri = uri;
    _cardSender = cardSender;
  }
  public async Task SendRequest(int Id, Card[] cards)
  {
    await _cardSender.SendCommand(new ChooseCard(Id: Id, Cards: cards.CardsToString()), _uri);
  }
}