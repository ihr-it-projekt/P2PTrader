class P2PTraderConfig
{
	ref P2PTraderItemsCategoryConfig traderItemsConfig;
	ref P2PTraderConfigParams traderConfigParams

    void P2PTraderConfig()
    {
  		this.traderItemsConfig = new P2PTraderItemsCategoryConfig;
  		this.traderConfigParams = new P2PTraderConfigParams;
	}
}