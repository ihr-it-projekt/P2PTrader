class P2PTraderStock
{
	const static string INACTIVE_OFFER = "inactive";
	const static string ACCEPTED_OFFER = "accepted";
	const static string OPEN_OFFER = "open";
	
    private const static string	SETTINGSFILE = "P2PTraderStock.json";
	private const static string	CONFIGSFOLDERP2P = "$profile:P2PTrader\\";
	private const static string	CONFIGSBACKUPFOLDERP2P = "$profile:P2PTrader\\Backup\\";

	private ref array<ref P2PTraderPlayerMarketOffer> stock;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerOffersInactive;
	private ref array<ref P2PTraderPlayerPlayerOffer> acceptedPlayerOffers;
	private int idCounter = 1;

    void P2PTraderStock()
    {
		if (!IsServerP2PTrader()){
			return;
		}
  		if (!FileExist(CONFIGSFOLDERP2P + SETTINGSFILE)){
			stock = new array<ref P2PTraderPlayerMarketOffer>;
			playerOffers = new array<ref P2PTraderPlayerPlayerOffer>;
			playerOffersInactive = new array<ref P2PTraderPlayerPlayerOffer>;
            acceptedPlayerOffers = new array<ref P2PTraderPlayerPlayerOffer>;
			DebugMessageP2PTrader("Create stock file");
			Save();
		} else {
			CreateBackup("backup-start-");
			Load();
		}
    }
	
	void ~P2PTraderStock(){
		Save();
		CreateBackup("backup-shout-down-");
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
	
	void AcceptPlayerToPlayerOffer(P2PTraderPlayerMarketOffer marketOfferItems, P2PTraderPlayerPlayerOffer playerOffer) {
		foreach(int index, P2PTraderPlayerMarketOffer stockOffer: stock) {
			if (marketOfferItems.GetId() == stockOffer.GetId()) {
				array<P2PTraderPlayerPlayerOffer> playerPlayerOffers = GetPlayerPlayerOfferForPlayerMarkertOffers(marketOfferItems);
				foreach(P2PTraderPlayerPlayerOffer playerPlayerOffer: playerPlayerOffers) {
					if (playerOffer.GetId() == playerPlayerOffer.GetId()) {
						ref P2PTraderPlayerPlayerOffer acceptedOffer = new P2PTraderPlayerPlayerOffer(playerOffer.GetOwnerId(), playerOffer.GetOwnerName(), marketOfferItems.GetId());
						idCounter++;
						acceptedOffer.SetId(idCounter);
						acceptedOffer.SetOfferItems(marketOfferItems.GetOfferItems());
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
	
	void AcceptPlayerToMarketOffer(P2PTraderPlayerMarketOffer marketOffer, P2PTraderPlayerPlayerOffer playerOffer) {
		foreach(int index, P2PTraderPlayerMarketOffer stockOffer: stock) {
			if (marketOffer.GetId() == stockOffer.GetId()) {
				ref P2PTraderPlayerPlayerOffer acceptedOffer = new P2PTraderPlayerPlayerOffer(marketOffer.GetOwnerId(), marketOffer.GetOwnerName(), marketOffer.GetId());
				idCounter++;
				acceptedOffer.SetId(idCounter);
				acceptedOffer.SetOfferItems(playerOffer.GetOfferItems());
				acceptedPlayerOffers.Insert(acceptedOffer);
				RemovePlayerToPlayerOffer(playerOffer, true);
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
	
	ref array<P2PTraderPlayerMarketOffer> GetMarketOffersFromPlayer(DayZPlayer player) {
		string playerId = player.GetIdentity().GetId();
		
		ref array<P2PTraderPlayerMarketOffer> playerStockOffers = new array<P2PTraderPlayerMarketOffer>;
		
		foreach(P2PTraderPlayerMarketOffer stockOffer: stock) {
			if (stockOffer.GetOwnerId() == playerId) {
				playerStockOffers.Insert(stockOffer);
			}
		}
		
		return playerStockOffers;
	}
	
	array<ref P2PTraderPlayerPlayerOffer> GetOffersFromAllPlayer() {
		return playerOffers;
	}
	array<ref P2PTraderPlayerPlayerOffer> GetAcceptedOffersFromAllPlayer() {
		return acceptedPlayerOffers;
	}
	array<ref P2PTraderPlayerPlayerOffer> GetInactiveOffersFromAllPlayer() {
		return playerOffersInactive;
	}
	
	ref array<ref P2PTraderPlayerPlayerOffer> GetOffersFromPlayer(PlayerIdentity player, string offerType) {
		string playerId = player.GetId();
		array<ref P2PTraderPlayerPlayerOffer> playerPlayerOffers = new array<ref P2PTraderPlayerPlayerOffer>;
		
		array<ref P2PTraderPlayerPlayerOffer> offerToCheck = playerOffersInactive;
		
		if (offerType == ACCEPTED_OFFER) {
			offerToCheck = acceptedPlayerOffers;
		}else if (offerType == OPEN_OFFER) {
			offerToCheck = playerOffers;
		}
		
		foreach (P2PTraderPlayerPlayerOffer playerOffer: offerToCheck) {
			if (playerId == playerOffer.GetOwnerId()){
				playerPlayerOffers.Insert(playerOffer);
			}
		}
		
		
		return playerPlayerOffers;
	}
	
	int GetCountPlayerOffers(DayZPlayer player) {
		PlayerIdentity playerIdent = player.GetIdentity();
		
		int count = 0;
		
		DebugMessageP2PTrader("Check OPEN_OFFER");
		count = count + this.GetOffersFromPlayer(playerIdent, OPEN_OFFER).Count();
		
		DebugMessageP2PTrader("Check INACTIVE_OFFER count is: " + count.ToString());
		count = count + this.GetOffersFromPlayer(playerIdent, INACTIVE_OFFER).Count();
		
		DebugMessageP2PTrader("Check ACCEPTED_OFFER count is: " + count.ToString());
		count = count + this.GetOffersFromPlayer(playerIdent, ACCEPTED_OFFER).Count();
		
		return count;
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
		string playerId = player.GetId();
		array<ref P2PTraderPlayerPlayerOffer> playerPlayerOffers = new array<ref P2PTraderPlayerPlayerOffer>;
		
		foreach (P2PTraderPlayerPlayerOffer playerOffer: playerOffersInactive) {
			if (playerId == playerOffer.GetOwnerId()){
				playerPlayerOffers.Insert(playerOffer);
			}
		}
		
		return playerPlayerOffers; 
	}
	
	array<ref P2PTraderPlayerPlayerOffer> GetAcceptedOffersFromPlayer(PlayerIdentity player) {
		string playerId = player.GetId();
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

    void Save(){
        if (IsServerAndMultiplayerP2PTrader()) {
			if (!FileExist(CONFIGSFOLDERP2P)) {
                MakeDirectory(CONFIGSFOLDERP2P);
                DebugMessageP2PTrader("create folder");
            }
			
			
			DebugMessageP2PTrader("save stock file: " + CONFIGSFOLDERP2P +  SETTINGSFILE);
			JsonFileLoader<P2PTraderStock>.JsonSaveFile(CONFIGSFOLDERP2P +  SETTINGSFILE, this);
		}
    }
	
	private void CreateBackup(string suffix) {
		static int hour;
        static int minute;
        static int second;
        GetHourMinuteSecondUTC(hour, minute, second);

        static int year;
        static int month;
        static int day;

        GetYearMonthDay(year, month, day);

        string time = hour.ToString() + "-" + minute.ToString() + "-" + second.ToString();
        string date = year.ToString() + "-" + month.ToString() + "-" + day.ToString();
		
		if (!FileExist(CONFIGSBACKUPFOLDERP2P)) {
            MakeDirectory(CONFIGSBACKUPFOLDERP2P);
            DebugMessageP2PTrader("create backup folder");
        }

		string fileName = suffix + date + "-" + time +"-";	
		CopyFile(CONFIGSFOLDERP2P + SETTINGSFILE , CONFIGSBACKUPFOLDERP2P + fileName + SETTINGSFILE);
	}
	
}