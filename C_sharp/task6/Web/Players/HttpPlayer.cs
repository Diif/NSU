namespace Web.Players;

using System.Net.Http.Json;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using GameStuff;
using GameStuff.Cards;

public class HttpPlayer : IPlayer
{
  private readonly string _url;
  private readonly HttpClient _http;
    public HttpPlayer(string url, HttpClient http)
    {
      _url = url;
      _http = http;
    }
    public Task<int> Pick(Card[] cards)
    {
      var t = new Task<int>
      ( () => 
        {
          var e = (Dto.ExperimentDto)cards;
          HttpResponseMessage response = _http.PostAsJsonAsync(_url, e).Result;
          var res = Newtonsoft.Json.JsonConvert.DeserializeObject<Dto.AnswerDto>(response.Content.ReadAsStringAsync().Result);
          return res!.Number;
        }
      );
      t.Start();
      return t;
    }
}