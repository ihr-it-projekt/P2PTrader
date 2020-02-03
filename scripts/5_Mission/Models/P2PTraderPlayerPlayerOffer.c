class P2PTraderPlayerPlayerOffer 
{
	private string ownerId;
	private ref array <P2PTraderStockItem> offerItems;
	private int id;
	private int playerToMarketOfferId;
	
	void P2PTraderPlayerPlayerOffer(DayZPlayer owner, int playerToMarketOfferId) {
		this.playerToMarketOfferId = playerToMarketOfferId;
		this.ownerId = owner.GetIdentity().GetPlainId();
		this.offerItems = new array<P2PTraderStockItem>;
	}
	
	void SetId(int id){
		this.id = id;
	}
	
	int GetId() {
		return id;
	}

    string GetOwnerId() {
        return ownerId;
    }
	
	int GetPlayerToMarketOfferId() {
		return playerToMarketOfferId;
	}
	
	void SetPlayerMarketOfferInactive() {
		playerToMarketOfferId = 0;
	}

	bool IsPlayerMarketOfferActive() {
	    return 0 != playerToMarketOfferId;
	}

    bool IsEmpty() {
        return offerItems.Count() == 0;
    }
	
	void AddOfferItem(P2PTraderStockItem item) {
		offerItems.Insert(item);
	}
}