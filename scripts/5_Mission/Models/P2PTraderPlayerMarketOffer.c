class P2PTraderPlayerMarketOffer
{
	private string ownerId;
	private int id;
	private ref array <ref P2PTraderStockItem> offerItems;
	private ref array <ref P2PTraderStockItem> wantedItems;
	private ref array <ref P2PTraderPlayerPlayerOffer> otherPlayerOffers;
	
	
	void P2PTraderPlayerMarketOffer(DayZPlayer owner) {
		this.ownerId = owner.GetIdentity().GetPlainId();
		this.offerItems = new array<ref P2PTraderStockItem>;
		this.wantedItems = new array<ref P2PTraderStockItem>;
		this.otherPlayerOffers = new array<ref P2PTraderPlayerPlayerOffer>;
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
	
	
}