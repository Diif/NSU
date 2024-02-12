using Microsoft.Extensions.Configuration;


namespace SharedModel.Config;

public interface IAddressProvider : IGodsAddressProvider, IMarkAddressProvider, IMuskAddressProvider
{
  
}