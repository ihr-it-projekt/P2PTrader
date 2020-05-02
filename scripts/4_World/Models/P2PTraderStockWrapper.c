class P2PTraderStockWrapper
{
    const static string STOCK_DB = "STOCK_DB";
    const static string STOCK_LOCAL = "STOCK_LOCAL";

    ref P2PTraderStock stock;
    ref P2PTraderStockDb stockDb;
	private P2PTraderConfig config;

    void P2PTraderStockWrapper(P2PTraderConfig config)
    {
		this.config = config;
		if (config.traderConfigParams.useDBStock) {
			stockDb = new P2PTraderStockDb(config);
		}
		stock = new P2PTraderStock;
    }
	
	void ~P2PTraderStockWrapper(){

	}
	
	void AddPlayerToMarketOffer(ref P2PTraderPlayerMarketOffer newOffer) {
		if (config.traderConfigParams.useDBStock) {
			stockDb.AddPlayerToMarketOffer(newOffer);
		} else {
			stock.AddPlayerToMarketOffer(newOffer);
		}
	}
	
	void AddPlayerToPlayerOffer(P2PTraderPlayerPlayerOffer newOffer) {
		if (config.traderConfigParams.useDBStock) {
            stockDb.AddPlayerToPlayerOffer(newOffer);
        } else {
            stock.AddPlayerToPlayerOffer(newOffer);
        }
	}

    P2PTraderPlayerMarketOffer GetPlayerToMarketOfferById(int id) {
        if (config.traderConfigParams.useDBStock) {
            return stockDb.GetPlayerToMarketOfferById(id);
        } else {
            return stock.GetPlayerToMarketOfferById(id);
        }
    }
	
	void RemovePlayerToMarketOffer(P2PTraderPlayerMarketOffer offerToRemove) {
		if (config.traderConfigParams.useDBStock) {
            stockDb.RemovePlayerToMarketOffer(offerToRemove);
        } else {
            stock.RemovePlayerToMarketOffer(offerToRemove);
        }
	}
	
	void AcceptPlayerToPlayerOffer(P2PTraderPlayerMarketOffer marketOfferItems, P2PTraderPlayerPlayerOffer playerOffer) {
        if (config.traderConfigParams.useDBStock) {
            return stockDb.AcceptPlayerToPlayerOffer(marketOfferItems, playerOffer);
        } else {
            return stock.AcceptPlayerToPlayerOffer(marketOfferItems, playerOffer);
        }
	}
	
	void AcceptPlayerToMarketOffer(P2PTraderPlayerMarketOffer marketOffer, P2PTraderPlayerPlayerOffer playerOffer) {
        if (config.traderConfigParams.useDBStock) {
            return stockDb.AcceptPlayerToMarketOffer(marketOffer, playerOffer);
        } else {
            return stock.AcceptPlayerToMarketOffer(marketOffer, playerOffer);
        }
	}
	
	void RemovePlayerToPlayerOffer(P2PTraderPlayerPlayerOffer offerToRemove, bool dontSave = false) {
       if (config.traderConfigParams.useDBStock) {
           stockDb.RemovePlayerToPlayerOffer(offerToRemove, dontSave);
       } else {
           stock.RemovePlayerToPlayerOffer(offerToRemove, dontSave);
       }
	}

	array<ref P2PTraderPlayerMarketOffer> GetStock() {
	    if (config.traderConfigParams.useDBStock) {
            return stockDb.GetStock();
        } else {
            return stock.GetStock();
        }
	}
	
	ref array<P2PTraderPlayerMarketOffer> GetMarketOffersFromPlayer(DayZPlayer player) {
	    if (config.traderConfigParams.useDBStock) {
            return stockDb.GetMarketOffersFromPlayer(player);
        } else {
            return stock.GetMarketOffersFromPlayer(player);
        }
	}
	
	array<ref P2PTraderPlayerPlayerOffer> GetOffersFromAllPlayer() {
	    if (config.traderConfigParams.useDBStock) {
            return stockDb.GetOffersFromAllPlayer();
        } else {
            return stock.GetOffersFromAllPlayer();
        }
	}
	array<ref P2PTraderPlayerPlayerOffer> GetAcceptedOffersFromAllPlayer() {
	    if (config.traderConfigParams.useDBStock) {
            return stockDb.GetAcceptedOffersFromAllPlayer();
        } else {
            return stock.GetAcceptedOffersFromAllPlayer();
        }
	}
	array<ref P2PTraderPlayerPlayerOffer> GetInactiveOffersFromAllPlayer() {
	    if (config.traderConfigParams.useDBStock) {
            return stockDb.GetInactiveOffersFromAllPlayer();
        } else {
            return stock.GetInactiveOffersFromAllPlayer();
        }
	}
	
	ref array<ref P2PTraderPlayerPlayerOffer> GetOffersFromPlayer(PlayerIdentity player, string offerType) {
	    if (config.traderConfigParams.useDBStock) {
            return stockDb.GetOffersFromPlayer(player, offerType);
        } else {
            return stock.GetOffersFromPlayer(player, offerType);
        }
	}
	
	int GetCountPlayerOffers(DayZPlayer player) {
	    if (config.traderConfigParams.useDBStock) {
            return stockDb.GetCountPlayerOffers(player);
        } else {
            return stock.GetCountPlayerOffers(player);
        }
	}
	
	P2PTraderPlayerPlayerOffer GetPlayerOfferById(int id) {
	    if (config.traderConfigParams.useDBStock) {
            return stockDb.GetPlayerOfferById(id);
        } else {
            return stock.GetPlayerOfferById(id);
        }
	}
	
	array<ref P2PTraderPlayerPlayerOffer> GetInactiveOffersFromPlayer(PlayerIdentity player) {
	    if (config.traderConfigParams.useDBStock) {
            return stockDb.GetInactiveOffersFromPlayer(player);
        } else {
            return stock.GetInactiveOffersFromPlayer(player);
        }
	}
	
	array<ref P2PTraderPlayerPlayerOffer> GetAcceptedOffersFromPlayer(PlayerIdentity player) {
	    if (config.traderConfigParams.useDBStock) {
            return stockDb.GetAcceptedOffersFromPlayer(player);
        } else {
            return stock.GetAcceptedOffersFromPlayer(player);
        }
	}
	
	void Save(){
	    if (!config.traderConfigParams.useDBStock) {
		    stock.Save();
        }
	}
}