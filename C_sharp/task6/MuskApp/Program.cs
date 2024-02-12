using Strategies;
using MassTransit;
using MuskApp;
using SharedModel.Config;

IMuskAddressProvider addressProvider = new AddressProvider();

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddMassTransit( x => 
{
  x.AddConsumer<ChooseCardConsumer>();
  x.UsingRabbitMq((context, cfg) => 
  {
    cfg.ReceiveEndpoint(addressProvider.MuskAskQ, e =>
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
app.Run(addressProvider.MuskUrl);
