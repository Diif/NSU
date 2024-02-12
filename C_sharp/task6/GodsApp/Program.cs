using MassTransit;
using GodsApp;
using GodsApp.Collisium;
using SharedModel.Config;
using GodsApp.Sender;
using GameStuff;
using Strategies;

IGodsAddressProvider addressProvider = new AddressProvider();

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddMassTransit( x => 
{
  x.AddConsumer<CardChecker>();
  x.UsingRabbitMq((cont, cfg) => 
  {
    cfg.ConfigureEndpoints(cont);
  });
});
builder.Services.AddSingleton<IAddressProvider, AddressProvider>();
builder.Services.AddSingleton<IMuskAddressProvider, AddressProvider>();
builder.Services.AddSingleton<IMarkAddressProvider, AddressProvider>();
builder.Services.AddSingleton<ResultWrapper>();
builder.Services.AddSingleton<ICardSender,CardSender>();
builder.Services.AddSingleton<IDeckShuffler, RandomDeckShuffler>();
builder.Services.AddSingleton<ICollisiumSandbox, CollisiumSandbox>();
builder.Services.AddSingleton<IPlayerFactory, MassTransitPlayerFactory>();
builder.Services.AddSingleton<ICollisiumWorker,CollisiumMassTransitWorker >();
builder.Services.AddHttpClient();
builder.Services.AddHostedService<Collisium>();

var app = builder.Build();

app.Run(addressProvider.GodsUrl);
