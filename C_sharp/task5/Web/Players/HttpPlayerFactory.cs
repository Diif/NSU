namespace Web.Players;

using GameStuff;
using Microsoft.Extensions.Configuration;

public class HttpPlayerFactory : IPlayerFactory
{
  private readonly HttpClient _http;
  private readonly string _p1Url;
  private readonly string _p2Url;
  public HttpPlayerFactory(
    HttpClient http,
    IEnumerable<Func<IConfiguration, string>> urls,
    IConfiguration configuration
    )
  {
    _http = http;
    urls = urls.Take(2);
    _p1Url = urls.ElementAt(0)(configuration);
    _p2Url = urls.ElementAt(1)(configuration);
  }
    public IPlayer GetPlayer1()
    {
        return new HttpPlayer(_p1Url, _http);
    }

    public IPlayer GetPlayer2()
    {
        return new HttpPlayer(_p2Url, _http);
    }
}