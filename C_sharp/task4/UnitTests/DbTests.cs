namespace UnitTests;

using GameStuff.Cards;
using GameStuff;
using Moq;
using Microsoft.Extensions.Configuration;
using DbStuff;
using Microsoft.EntityFrameworkCore;
using Microsoft.Data.Sqlite;
using DbStuff.Model;

public class DbTests
{

    private SqliteConnection CreateOpenConnection()
    {
        var connection = new SqliteConnection("Filename=:memory:");
        connection.Open();
        return connection;
    }

    private ExperimentContext CreateContext(SqliteConnection connection)
    {
        var contextOptions = new DbContextOptionsBuilder<ExperimentContext>()
            .UseSqlite(connection)
            .Options;
        return new ExperimentContext(contextOptions);
    }

    private IConfiguration CreateConfig()
    {
        var myConfiguration = new Dictionary<string, string>
        {
            {"MaxCards", "36"}
        };

        return new ConfigurationBuilder()
            .AddInMemoryCollection(myConfiguration!)
            .Build();
    }
    [Fact]
    public void TestGenerateExperiments()
    {
        using var connection = CreateOpenConnection();
        using var db = CreateContext(connection);
        var config = CreateConfig();
        var utils = new ExperimentUtils(config, db);
        var shuffler = new Mock<IDeckShuffler>();
        var numExp = 10;
        var numCards = (int)config.GetValue(typeof(int), "MaxCards")!;

        db.Database.EnsureCreated();
        utils.GenerateExperiments(numExp,shuffler.Object);
        
        var exps = db.Experiments;
        
        var count = 0;
        foreach (var e in exps)
        {
            count++;
            Assert.True(e.Cards.Length == numCards);
            Assert.Null(Record.Exception( () => (Card[])e ));
            Assert.True(((Card[])e).Length == numCards);
        }

        Assert.True(count == numExp);
    }


    [Theory]
    [InlineData("RRRRRRRRRRRRRRRRRRBBBBBBBBBBBBBBBBBB")]
    public void TestGetExperiment(string experiment)
    {
        using var connection = CreateOpenConnection();
        using var db = CreateContext(connection);
        var config = CreateConfig();
        var utils = new ExperimentUtils(config, db);

        db.Add(new ExperimentEntity{Cards = experiment});
        db.SaveChanges();

        var exp = utils.GetExperiments();
        Assert.True(exp.Count == 1);
        Assert.True(exp[0].Length == (int)config.GetValue(typeof(int), "MaxCards")!);

        var ind = 0;
        foreach (Card card in exp[0])
        {
            switch (card.Color)
            {
                case CardColor.Red:
                    Assert.True(experiment[ind++] == 'R');
                    break;
                case CardColor.Black:
                    Assert.True(experiment[ind++] == 'B');
                    break;
            }
        }
    }
}