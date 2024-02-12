namespace UnitTests;

using static GameStuff.DeckStuff;
using GameStuff.Cards;
using GameStuff;
using Moq;

public class ExperimentTests
{
    [Fact]
    public void TestShuffleCount()
    {
        var shuffler = new Mock<IDeckShuffler>();
        var deck = CreateDeck(36);
        CollisiumSandbox sandbox = new();
        Strategies.StrategiesFactory factory = new();

        shuffler.Setup(c => c.ShuffleDeck(It.IsAny<Card[]>()));
        
        sandbox.PlayRound(factory.GetMarkStr(),factory.GetMuskStr(), shuffler.Object, deck);

        shuffler.Verify(c => c.ShuffleDeck(It.IsAny<Card[]>()), Times.Once);

    }

    [Fact]
    public void TestExperimentIdempotence()
    {
        var shuffler = new Mock<IDeckShuffler>();
        var deck = CreateDeck(36);
        deck[0] = new Card(CardColor.Black);
        deck[15] = new Card(CardColor.Black);
        
        CollisiumSandbox sandbox = new();
        Strategies.StrategiesFactory factory = new();
        
        var res = sandbox.PlayRound(factory.GetMarkStr(),factory.GetMuskStr(), shuffler.Object, deck);

        Assert.True(res);

    }
}