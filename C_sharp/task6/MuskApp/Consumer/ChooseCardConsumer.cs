using SharedModel.Model.Events;
using GameStuff;
using MassTransit;
using SharedModel.Model.Messages;
using SharedModel;
using Strategies;
using GameStuff.Cards;
using SharedModel.Model;

namespace MuskApp;
class ChooseCardConsumer : IConsumer<ChooseCard>
{
    private readonly EventPublisher _publisher;
    private readonly ICardPickStrategy _strategy;
    private readonly ResultWrapper _res;
    public ChooseCardConsumer(EventPublisher publisher, StrategiesFactory factory,ResultWrapper res)
    {
        _publisher = publisher;
        _strategy = factory.GetMuskStr();
        _res = res;
    }
    public async Task Consume(ConsumeContext<ChooseCard> context)
    {
        var command = context.Message;
        Card[] cards = command.Cards.StringToCards();
        _res.Decks.TryAdd(command.Id, cards);

        await _publisher.PublishEvent(new CardChoosen(Id: command.Id, Sender: Players.MUSK, Num: _strategy.Pick(cards)));
    }
}