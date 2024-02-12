using Microsoft.AspNetCore.Mvc;
using SharedModel;
using SharedModel.Model.Dtos;

namespace MuskApp;

[ApiController]
[Route("/")]
public class CommandController : ControllerBase
{
  private readonly ResultWrapper _res;
  public CommandController(ResultWrapper res)
  {
    _res = res;
  }

  [HttpPost]
  public AnswerCardDto SendResult(AskCardDto ask)
  {
    _res.Decks.TryRemove(ask.Id, out var cards);
    var color = cards[ask.Num].Color;

    return new AnswerCardDto(ask.Id, color);
    
  }

}