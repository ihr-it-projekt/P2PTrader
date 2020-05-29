class P2PTraderPlayerPlayerOffer extends P2PTraderBaseOffer
{
	private int playerToMarketOfferId;
	private string message;
	
	void P2PTraderPlayerPlayerOffer(string ownerId, string ownerName, int playerToMarketOfferId, string message = "") {
		this.playerToMarketOfferId = playerToMarketOfferId;
		this.ownerId = ownerId;
		this.ownerName = ownerName;
		this.offerItems = new array<ref P2PTraderStockItem>;
		this.message = message;
		this.SetCreationDate();
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
	
	void SetOfferItems(ref array <ref P2PTraderStockItem> offerItems) {
		this.offerItems = offerItems;
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