class P2PTraderPlayerPlayerOffer 
{
	private string ownerId;
	private string ownerName;
	private ref array <ref P2PTraderStockItem> offerItems;
	private int id;
	private int playerToMarketOfferId;
	private string message;
	
	void P2PTraderPlayerPlayerOffer(string ownerId, string ownerName, int playerToMarketOfferId, string message = "") {
		this.playerToMarketOfferId = playerToMarketOfferId;
		this.ownerId = ownerId;
		this.ownerName = ownerName;
		this.offerItems = new array<ref P2PTraderStockItem>;
		this.message = message;
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
	
	string GetOwnerName() {
		return ownerName;
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
		this.offerItems.Insert(item);
	}
	
	void SetOfferItems(ref array <ref P2PTraderStockItem> offerItems) {
		this.offerItems = offerItems;
	}
	
	array <ref P2PTraderStockItem> GetOfferItems() {
		return offerItems;
	}
	
	string GetMessage() {
		return message;
	}
	
	string GetName() {
		string name = "";
		
		foreach(P2PTraderStockItem item: offerItems) {
			name += item.GetTranslation() + "; ";
		}
		
		return name;
	}
}