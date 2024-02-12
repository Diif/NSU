using MassTransit;
using Strategies;
using MarkApp;
using SharedModel.Config;

IMarkAddressProvider addressProvider = new AddressProvider();

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddMassTransit( x => 
{
  x.AddConsumer<ChooseCardConsumer>();
  x.UsingRabbitMq((context, cfg) => 
  {
    cfg.ReceiveEndpoint(addressProvider.MarkAskQ, e =>
    {
      e.ConfigureConsumer<ChooseCardConsumer>(context);
    });
  });
});
builder.Services.AddSingleton<StrategiesFactory>();
builder.Services.AddSingleton<ResultWrapper>();
builder.Services.AddSingleton<EventPublisher>();
builder.Services.AddControllers();

var app = builder.Build();

app.MapControllers();
app.Run(addressProvider.MarkUrl);
