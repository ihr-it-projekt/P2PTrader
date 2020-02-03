class P2PTraderPlayerMarketOffer
{
	private string ownerId;
	private string ownerName;
	private string offerMessage;
	private int id;
	private ref array <ref P2PTraderStockItem> offerItems;
	private ref array <ref P2PTraderStockItem> wantedItems;
	private ref array <int> otherPlayerOffersIds;
	
	
	void P2PTraderPlayerMarketOffer(DayZPlayer owner, string offerMessage = "") {
		this.ownerId = owner.GetIdentity().GetPlainId();
		this.ownerName = owner.GetIdentity().GetName();
		this.offerMessage = offerMessage;
		this.offerItems = new array<ref P2PTraderStockItem>;
		this.wantedItems = new array<ref P2PTraderStockItem>;
		this.otherPlayerOffersIds = new array<int>;
	}
	
	void SetId(int id){
		this.id = id;
	}
	
	int GetId() {
		return id;
	}
	
	void AddOfferItem(ref P2PTraderStockItem item) {
		offerItems.Insert(item);
	}
	
	void AddWantedItem(ref P2PTraderStockItem item) {
		wantedItems.Insert(item);
	}

	void AddPlayerOffer(P2PTraderPlayerPlayerOffer offer) {
        otherPlayerOffersIds.Insert(offer.GetId());
	}

	void RemovePlayerOffer(P2PTraderPlayerPlayerOffer offer) {
	    foreach(int index, int offerId: otherPlayerOffersIds) {
	        if(offerId == offer.GetId()) {
                otherPlayerOffersIds.Remove(index);
	        }
	    }
	}

	bool IsEmpty() {
	    return offerItems.Count() == 0 && wantedItems.Count() == 0;
	}

	string GetOwnerId() {
	    return ownerId;
	}
	
	string GetOwnerName() {
	    return ownerName;
	}
	
	bool ContainsItemType(string search) {
		foreach(P2PTraderStockItem item: offerItems) {
			if(item.GetTranslation().Contains(search)) {
				return true;
			}
		}
		
		return false;
	}

    array <ref P2PTraderStockItem> GetOfferItems() {
	   return offerItems;
	}

    array <ref P2PTraderStockItem> GetWantedItems() {
	   return wantedItems;
	}

	string GetOfferMessage() {
	    return offerMessage;
	}
	
}