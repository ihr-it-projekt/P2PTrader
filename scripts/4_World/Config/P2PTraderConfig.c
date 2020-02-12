class P2PTraderConfig
{
	ref P2PTraderItemsConfig traderItemsConfig;
	ref P2PTraderConfigParams traderConfigParams

    void P2PTraderConfig()
    {
  		this.traderItemsConfig = new P2PTraderItemsConfig;
  		this.traderConfigParams = new P2PTraderConfigParams;
	}
}