class P2PTraderStock
{
    private const static string	SETTINGSFILE = "P2PTraderStock.json";
	private const static string	CONFIGSFOLDERP2P = "$profile:P2PTrader\\";
	
	private ref array<ref P2PTraderPlayerMarketOffer> stock;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerOffersInactive;
	private int idCounter = 1;

    void P2PTraderStock()
    {
  		if (!FileExist(CONFIGSFOLDERP2P + SETTINGSFILE))
		{
			stock = new array<ref P2PTraderPlayerMarketOffer>;
			playerOffers = new array<ref P2PTraderPlayerPlayerOffer>;
			playerOffersInactive = new array<ref P2PTraderPlayerPlayerOffer>;
			Save();
		} else {
			Load();
		}
    }
	
	void AddPlayerToMarketOffer(ref P2PTraderPlayerMarketOffer newOffer) {
		idCounter++;
		
		newOffer.SetId(idCounter);
		stock.Insert(newOffer);
		
		Save();
	}

    P2PTraderPlayerMarketOffer GetPlayerToMarketOfferById(int id) {
        foreach(P2PTraderPlayerMarketOffer offer: stock) {
            if (id == offer.GetId()) {
                return offer;
            }
        }

        return null;
    }
	
	void RemovePlayerToMarketOffer(P2PTraderPlayerMarketOffer offerToRemove) {
		foreach(int index, P2PTraderPlayerMarketOffer stockOffer: stock) {
			if (offerToRemove.GetId() == stockOffer.GetId()) {
				stock.RemoveOrdered(index);
				array<P2PTraderPlayerPlayerOffer> playerPlayerOffers = GetPlayerPlayerOfferForPlayerMarkertOffers(offerToRemove);
				foreach(P2PTraderPlayerPlayerOffer playerPlayerOffer: playerPlayerOffers) {
					playerPlayerOffer.SetPlayerMarketOfferInactive();
					playerOffersInactive.Insert(playerPlayerOffer);
					RemovePlayerToPlayerOffer(playerPlayerOffer, true);
				}
				Save();
				return;
			}
		}
	}
	
	void AddPlayerToPlayerOffer(P2PTraderPlayerPlayerOffer newOffer) {
		idCounter++;
		newOffer.SetId(idCounter);
		playerOffers.Insert(newOffer);
		Save();
	}
	
	void RemovePlayerToPlayerOffer(P2PTraderPlayerPlayerOffer offerToRemove, bool dontSave = false) {
		bool mustSave = false;
		foreach(int index, P2PTraderPlayerPlayerOffer playerOffer: playerOffers) {
			if (offerToRemove.GetId() == playerOffer.GetId()) {
				playerOffers.RemoveOrdered(index);
				mustSave = true;
			}
		}
		
		if (!dontSave && mustSave) {
			Save();
		}
	}
	
	void RemovePlayerToPlayerOfferInactive(P2PTraderPlayerPlayerOffer offerToRemove) {
		foreach(int index, P2PTraderPlayerPlayerOffer playerOffer: playerOffersInactive) {
			if (offerToRemove.GetId() == playerOffer.GetId()) {
				playerOffers.RemoveOrdered(index);
				Save();
				return;
			}
		}
	}
	
	array<P2PTraderPlayerPlayerOffer> GetPlayerPlayerOfferForPlayerMarkertOffers(P2PTraderPlayerMarketOffer offer) {
		array<P2PTraderPlayerPlayerOffer> playerPlayerOffers = new array<P2PTraderPlayerPlayerOffer>;
		
		foreach(P2PTraderPlayerPlayerOffer playerPlayerOffer: playerOffers) {
			if (offer.GetId() == playerPlayerOffer.GetPlayerToMarketOfferId()) {
				playerPlayerOffers.Insert(playerPlayerOffer);
			}
		}
		
		return playerPlayerOffers;
	}
	
    private void Load() 
    {
        if (IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGSFOLDERP2P + SETTINGSFILE)) {
			DebugMessageP2PTrader("load stock file");
			JsonFileLoader<P2PTraderStock>.JsonLoadFile(CONFIGSFOLDERP2P + SETTINGSFILE, this);
        }
    }

    private void Save()
    {
        if (IsServerAndMultiplayerP2PTrader()) {
			if (!FileExist(CONFIGSFOLDERP2P)) {
                MakeDirectory(CONFIGSFOLDERP2P);
                DebugMessageP2PTrader("create folder");
            }
			DebugMessageP2PTrader("save stock file");
			JsonFileLoader<P2PTraderStock>.JsonSaveFile(CONFIGSFOLDERP2P + SETTINGSFILE, this);
		}
    }
	
}