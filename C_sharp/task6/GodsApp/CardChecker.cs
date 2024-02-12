namespace GodsApp;

using System.Threading.Tasks;
using MassTransit;
using SharedModel.Config;
using SharedModel.Model.Events;
using SharedModel.Model;
using SharedModel.Model.Dtos;

class CardChecker : IConsumer<CardChoosen>, IDisposable
{
    private readonly string _markUrl;

    private readonly string _muskUrl;
    private readonly HttpClient _markClient;
    private readonly HttpClient _muskClient;
    private readonly ResultWrapper _res;
    public CardChecker(
        IMuskAddressProvider muskAddressProvider,
        IMarkAddressProvider markAddressProvider,
        IHttpClientFactory _httpFactory,
        ResultWrapper result
        )
    {
        _res = result;
        _markUrl = markAddressProvider.MarkUrl;
        _muskUrl = muskAddressProvider.MuskUrl;
        _markClient = _httpFactory.CreateClient();
        _markClient.BaseAddress = new Uri(markAddressProvider.MarkUrl);
        _muskClient = _httpFactory.CreateClient();
        _muskClient.BaseAddress = new Uri(muskAddressProvider.MuskUrl);
    }
    public async Task Consume(ConsumeContext<CardChoosen> context)
    {
        HttpResponseMessage? response = null;
        var dto = new AskCardDto(Id: context.Message.Id,  Num: context.Message.Num);
        switch (context.Message.Sender)
        {
            case Players.MUSK:       
                response = await _markClient.PostAsJsonAsync(_markUrl,dto);
                break;
            case Players.MARK:
                response = await _muskClient.PostAsJsonAsync(_muskUrl,dto);
                break;
        }
        
        var res = Newtonsoft.Json.JsonConvert.DeserializeObject<AnswerCardDto>(response!.Content.ReadAsStringAsync().Result);
        _res.Queue.Add(res!);

    }

    public void Dispose()
    {
        _markClient.Dispose();
        _muskClient.Dispose();
    }
}
