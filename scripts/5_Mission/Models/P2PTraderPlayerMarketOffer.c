class P2PTraderPlayerMarketOffer extends P2PTraderBaseOffer
{
    static string TYPE_ALL = "all";
    static string TYPE_INSTANT_BUY = "instant_buy";
    static string TYPE_AUCTION = "auction";
	private string ownerId;
	private string ownerName;
	private string offerMessage;
	private int id;
	private ref array <ref P2PTraderStockItem> offerItems;
	private ref array <ref P2PTraderStockItem> wantedItems;
	private ref array <int> otherPlayerOffersIds;
	private string offerType;
	
	
	void P2PTraderPlayerMarketOffer(DayZPlayer owner, string offerType, string offerMessage = "") {
		this.ownerId = owner.GetIdentity().GetId();
		this.ownerName = owner.GetIdentity().GetName();
		this.offerMessage = offerMessage;
		this.offerItems = new array<ref P2PTraderStockItem>;
		this.wantedItems = new array<ref P2PTraderStockItem>;
		this.otherPlayerOffersIds = new array<int>;
		this.SetCreationDate();
		this.offerType = offerType;
		
	}
	
	bool IsOfferType(string offerType) {
	    if (!this.offerType || this.offerType == "") {
	        this.offerType = this.TYPE_AUCTION;
	    }

		return this.offerType == offerType;
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
	
	bool HasPlayerOfferId(int id){
		int index = otherPlayerOffersIds.Find(id);
		
		return -1 != index;
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
	
	bool Contains(string search) {
		foreach(P2PTraderStockItem item: offerItems) {
			if(item.Contains(search)) {
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