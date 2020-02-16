class P2PTraderStock
{
    private const static string	SETTINGSFILE = "P2PTraderStock.json";
	private const static string	CONFIGSFOLDERP2P = "$profile:P2PTrader\\";
	
	private ref array<ref P2PTraderPlayerMarketOffer> stock;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerOffersInactive;
	private ref array<ref P2PTraderPlayerPlayerOffer> acceptedPlayerOffers;
	private int idCounter = 1;

    void P2PTraderStock()
    {
		if (!IsServerP2PTrader()) {
			return;
		}
  		if (!FileExist(CONFIGSFOLDERP2P + SETTINGSFILE))
		{
			stock = new array<ref P2PTraderPlayerMarketOffer>;
			playerOffers = new array<ref P2PTraderPlayerPlayerOffer>;
			playerOffersInactive = new array<ref P2PTraderPlayerPlayerOffer>;
            acceptedPlayerOffers = new array<ref P2PTraderPlayerPlayerOffer>;
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
				array<P2PTraderPlayerPlayerOffer> playerPlayerOffers = GetPlayerPlayerOfferForPlayerMarkertOffers(offerToRemove);
				foreach(P2PTraderPlayerPlayerOffer playerPlayerOffer: playerPlayerOffers) {
					RemovePlayerToPlayerOffer(playerPlayerOffer, true);
					playerPlayerOffer.SetPlayerMarketOfferInactive();
					playerOffersInactive.Insert(playerPlayerOffer);
				}
				stock.Remove(index);
				Save();
				break;
			}
		}
	}
	
	void AcceptPlayerToPlayerOffer(P2PTraderPlayerMarketOffer marketOffer, P2PTraderPlayerPlayerOffer playerOffer) {
		foreach(int index, P2PTraderPlayerMarketOffer stockOffer: stock) {
			if (marketOffer.GetId() == stockOffer.GetId()) {
				array<P2PTraderPlayerPlayerOffer> playerPlayerOffers = GetPlayerPlayerOfferForPlayerMarkertOffers(marketOffer);
				foreach(P2PTraderPlayerPlayerOffer playerPlayerOffer: playerPlayerOffers) {
					if (playerOffer.GetId() == playerPlayerOffer.GetId()) {
						ref P2PTraderPlayerPlayerOffer acceptedOffer = new P2PTraderPlayerPlayerOffer(playerOffer.GetOwnerId(), playerOffer.GetOwnerName(), marketOffer.GetId());
						idCounter++;
						acceptedOffer.SetId(idCounter);
						acceptedOffer.SetOfferItems(marketOffer.GetOfferItems());
						acceptedPlayerOffers.Insert(acceptedOffer);
						RemovePlayerToPlayerOffer(playerPlayerOffer, true);
					} else {
						playerPlayerOffer.SetPlayerMarketOfferInactive();
						RemovePlayerToPlayerOffer(playerPlayerOffer, true);
						playerOffersInactive.Insert(playerPlayerOffer);
					}
				}
				stock.Remove(index);
				Save();
				break;
			}
		}
	}
	
	P2PTraderPlayerPlayerOffer AddPlayerToPlayerOffer(P2PTraderPlayerPlayerOffer newOffer) {
		idCounter++;
		newOffer.SetId(idCounter);
		playerOffers.Insert(newOffer);
		Save();
		return newOffer;
	}
	
	void RemovePlayerToPlayerOffer(P2PTraderPlayerPlayerOffer offerToRemove, bool dontSave = false) {
		bool mustSave = false;
		foreach(int index, P2PTraderPlayerPlayerOffer playerOffer: playerOffers) {
			if (offerToRemove.GetId() == playerOffer.GetId()) {
				playerOffers.Remove(index);
				mustSave = true;
				break;
			}
		}
		
		foreach(int indexI, P2PTraderPlayerPlayerOffer playerOfferInactive: playerOffersInactive) {
			if (mustSave) {
				break;
			}
			if (offerToRemove.GetId() == playerOfferInactive.GetId()) {
				playerOffersInactive.Remove(indexI);
				mustSave = true;
			}
		}
		
		foreach(int indexA, P2PTraderPlayerPlayerOffer acceptedPlayerOffer: acceptedPlayerOffers) {
			if (mustSave) {
				break;
			}
			if (offerToRemove.GetId() == acceptedPlayerOffer.GetId()) {
				acceptedPlayerOffers.Remove(indexA);
				mustSave = true;
			}
		}
		
		if (!dontSave && mustSave) {
			Save();
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
	
	array<ref P2PTraderPlayerMarketOffer> GetStock() {
		return stock;
	}
	
	
	
	array<ref P2PTraderPlayerPlayerOffer> GetOffersFromAllPlayer() {
		return playerOffers;
	}
	
	array<ref P2PTraderPlayerPlayerOffer> GetOffersFromPlayer(PlayerIdentity player) {
		string playerId = player.GetPlainId();
		array<ref P2PTraderPlayerPlayerOffer> playerPlayerOffers = new array<ref P2PTraderPlayerPlayerOffer>;
		
		foreach (P2PTraderPlayerPlayerOffer playerOffer: playerOffers) {
			if (playerId == playerOffer.GetOwnerId()){
				playerPlayerOffers.Insert(playerOffer);
			}
		}
		
		return playerPlayerOffers; 
	}
	
	P2PTraderPlayerPlayerOffer GetPlayerOfferById(int id) {
		foreach (P2PTraderPlayerPlayerOffer playerOffer: playerOffers) {
			if (id == playerOffer.GetId()){
				
				return playerOffer;
			}
		}
		foreach (P2PTraderPlayerPlayerOffer playerOfferInacive: playerOffersInactive) {
			if (id == playerOfferInacive.GetId()){
				
				return playerOfferInacive;
			}
		}
		foreach (P2PTraderPlayerPlayerOffer acceptedPlayerOffer: acceptedPlayerOffers) {
			if (id == acceptedPlayerOffer.GetId()){
				
				return acceptedPlayerOffer;
			}
		}
		
		return null; 
	}
	
	array<ref P2PTraderPlayerPlayerOffer> GetInactiveOffersFromPlayer(PlayerIdentity player) {
		string playerId = player.GetPlainId();
		array<ref P2PTraderPlayerPlayerOffer> playerPlayerOffers = new array<ref P2PTraderPlayerPlayerOffer>;
		
		foreach (P2PTraderPlayerPlayerOffer playerOffer: playerOffersInactive) {
			if (playerId == playerOffer.GetOwnerId()){
				playerPlayerOffers.Insert(playerOffer);
			}
		}
		
		return playerPlayerOffers; 
	}
	
	array<ref P2PTraderPlayerPlayerOffer> GetAcceptedOffersFromPlayer(PlayerIdentity player) {
		string playerId = player.GetPlainId();
		array<ref P2PTraderPlayerPlayerOffer> playerPlayerOffers = new array<ref P2PTraderPlayerPlayerOffer>;
		
		foreach (P2PTraderPlayerPlayerOffer playerOffer: acceptedPlayerOffers) {
			if (playerId == playerOffer.GetOwnerId()){
				playerPlayerOffers.Insert(playerOffer);
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