namespace UnitTests;

using static GameStuff.DeckStuff;
using GameStuff.Cards;
using GameStuff;

public class StrategyTests
{
    [Fact]
    public void TestRandomStrategyIdempotence()
    {
        var deck = CreateDeck();

        Strategies.StrategiesFactory factory = new();

        SplitDeck(deck,out Card[] part1, out Card[] part2);

        var res = factory.GetMarkStr().Pick(part1);
        Assert.Equal<Card>(deck[0], deck[res]);
    }
}