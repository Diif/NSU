namespace GodsApp;

using GameStuff;
using GodsApp.Sender;
using SharedModel.Config;
class MassTransitPlayerFactory : IPlayerFactory
{
  private readonly ICardSender _cardSender;
  private readonly Uri _markQUrl;
  private readonly Uri _muskQUrl;
  public MassTransitPlayerFactory(
    ICardSender cardSender,
    IMuskAddressProvider muskAddressProvider,
    IMarkAddressProvider markAddressProvider
    )
  {
    _cardSender = cardSender;
    _muskQUrl = new Uri("queue:" + muskAddressProvider.MuskAskQ);
    _markQUrl = new Uri("queue:" + markAddressProvider.MarkAskQ);
  }
    public IPlayer GetMusk()
    {
        return new MassTransitPlayer(_muskQUrl, _cardSender);
    }

    public IPlayer GetMark()
    {
        return new MassTransitPlayer(_markQUrl, _cardSender);
    }
}