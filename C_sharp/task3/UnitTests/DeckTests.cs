namespace UnitTests;

using static GameStuff.DeckStuff;
using GameStuff.Cards;
using System.Runtime.InteropServices;

public class DeckTests
{
    [Fact]
    public void TestRedBlackEquality()
    {
        var deck = CreateDeck();
        int red = 0;
        int black = 0;
        foreach (Card c in deck)
        {
            switch (c.Color)
            {
                case CardColor.Black:
                    black++;
                    break;
                case CardColor.Red:
                    red++;
                    break;
            }
        }
        Assert.True(deck.Length == 32);
        Assert.True(black == red);
    }
}