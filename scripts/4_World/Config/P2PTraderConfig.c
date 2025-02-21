class P2PTraderConfig {
    ref P2PTraderItemsCategoryConfig traderItemsConfig;
    ref P2PTraderConfigParams traderConfigParams

    void P2PTraderConfig() {
        traderItemsConfig = new P2PTraderItemsCategoryConfig;
        traderConfigParams = new P2PTraderConfigParams;
    }
}