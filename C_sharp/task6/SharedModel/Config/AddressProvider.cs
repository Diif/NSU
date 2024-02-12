using Microsoft.Extensions.Configuration;


namespace SharedModel.Config;

public class AddressProvider : IAddressProvider
{
  private readonly IConfiguration _conf;
  public AddressProvider ()
  {
    var myConfiguration = new Dictionary<string, string>
        {
            {"GodsUrl", "http://localhost:5001"},
            {"MuskUrl", "http://localhost:5002"},
            {"MuskAskQ","musk-ask-queue"},
            {"MarkUrl", "http://localhost:5003"},
            {"MarkAskQ","mark-ask-queue"}};

        _conf = new ConfigurationBuilder()
            .AddInMemoryCollection(myConfiguration!)
            .Build();
    // _conf =  new ConfigurationBuilder().
            //  .AddJsonFile("addresses.json").Build();
  }
  public string GodsUrl
  {
    get
    {
      return (string)_conf.GetValue(typeof(string), "GodsUrl")!;
    }

  }

  public string MarkUrl
  {
    get
    {
      return (string)_conf.GetValue(typeof(string), "MarkUrl")!;
    }
  }

  public string MarkAskQ
  {
    get
    {
      return (string)_conf.GetValue(typeof(string), "MarkAskQ")!;
    }
  }

  public string MarkAnwQ
  {
    get
    {
      return (string)_conf.GetValue(typeof(string), "MarkAnwQ")!;
    }
  }

  public string MuskUrl
  {
    get
    {
      return (string)_conf.GetValue(typeof(string), "MuskUrl")!;
    }
  }

  public string MuskAskQ
  {
    get
    {
      return (string)_conf.GetValue(typeof(string), "MuskAskQ")!;
    }
  }

  public string MuskAnwQ 
  {
    get
    {
      return (string)_conf.GetValue(typeof(string), "MuskAnwQ")!;
    }
  }
}