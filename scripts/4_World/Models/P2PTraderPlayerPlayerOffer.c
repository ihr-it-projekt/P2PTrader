class P2PTraderPlayerPlayerOffer extends P2PTraderBaseOffer
{
    static string ACTIVE = "active";
    static string INACTIVE = "inactive";
    static string ACCEPTED = "accepted";
	private string ownerId;
	private string ownerName;
	private ref array <ref P2PTraderStockItem> offerItems;
	private int id;
	private int playerToMarketOfferId;
	private string message;
	private string state = P2PTraderPlayerPlayerOffer::ACTIVE;
	
	void P2PTraderPlayerPlayerOffer(string ownerId, string ownerName, int playerToMarketOfferId, string message = "") {
		this.playerToMarketOfferId = playerToMarketOfferId;
		this.ownerId = ownerId;
		this.ownerName = ownerName;
		this.offerItems = new array<ref P2PTraderStockItem>;
		this.message = message;
		this.SetCreationDate();
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
	    state = P2PTraderPlayerPlayerOffer::INACTIVE;
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
	
	array <P2PTraderStockItem> GetAllItems() {
		array<P2PTraderStockItem> allItems = new array<P2PTraderStockItem>;
		
		if (offerItems.Count() > 0) {
			foreach(P2PTraderStockItem item: offerItems) {
				allItems.Insert(item);
				array<ref P2PTraderStockItem> attachedItems = item.GetAttached();
				if (attachedItems.Count() > 0) {
					foreach(P2PTraderStockItem aItem: attachedItems) {
						allItems.Insert(aItem);
					}
				}
			}
		}
		
		return allItems;
	}
	
	void ResetTranslation() {
		foreach(P2PTraderStockItem offerItem: offerItems) {
			offerItem.ResetTranslation();
		}
	}
	
}