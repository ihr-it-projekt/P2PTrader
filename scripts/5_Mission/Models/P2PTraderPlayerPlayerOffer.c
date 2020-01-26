class P2PTraderPlayerPlayerOffer 
{
	private string ownerId;
	private ref array <ItemBase> offerItems;
	private int id;
	private int playerToMarketOfferId;
	
	void P2PTraderPlayerPlayerOffer(DayZPlayer owner, int playerToMarketOfferId) {
		this.playerToMarketOfferId = playerToMarketOfferId;
		this.ownerId = owner.GetIdentity().GetPlainId();
		this.offerItems = new array<ItemBase>;
	}
	
	void SetId(int id){
		this.id = id;
	}
	
	int GetId() {
		return id;
	}
	
	int GetPlayerToMarketOfferId() {
		return playerToMarketOfferId;
	}
	
	void SetPlayerMarketOfferInactive() {
		playerToMarketOfferId = 0;
	}
	
	void AddOfferItem(ItemBase item) {
		offerItems.Insert(item);
	}
}