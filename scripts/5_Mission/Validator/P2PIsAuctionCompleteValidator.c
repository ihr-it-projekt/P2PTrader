class P2PIsAuctionCompleteValidator extends P2PBaseValidator
{
	private ref map <int, P2PTraderStockItem> usedItems
	private ref map <int, P2PTraderStockItem> unUsedItems
	private ref array <ref P2PTraderStockItem> marketOfferItems;
	private ref array <P2PTraderStockItem> playerOfferItems;
	
	void P2PIsAuctionCompleteValidator(P2PTraderPlayerMarketOffer marketOffer, P2PTraderPlayerPlayerOffer playerOffer) {
		usedItems = new map <int, P2PTraderStockItem>;
		unUsedItems = new map <int, P2PTraderStockItem>;
		marketOfferItems = marketOffer.GetWantedItems();
        playerOfferItems = playerOffer.GetAllItems();
	}
	
    protected override bool DoValidate() {
		if (playerOfferItems.Count() == 0 || marketOfferItems.Count() >  playerOfferItems.Count()) {
			errorMessage = "#you_offer_to_less_items";
			return false;
		}
		
		foreach(P2PTraderStockItem itemM: marketOfferItems) {
			bool found = false;
			foreach(int posP, P2PTraderStockItem itemP: playerOfferItems) {
				if (usedItems.Get(posP)) {
					continue;
				}
				
				if (itemM.GetType() == itemP.GetType() && itemM.GetHealth() <= itemP.GetHealth() && itemM.GetQuantity() <= itemP.GetQuantity()) {
					DebugMessageP2PTrader("has found one item: " + itemP.GetType());
					usedItems.Set(posP, itemP);
				}
			}
		}
		
		foreach(int posPU, P2PTraderStockItem itemPU: playerOfferItems) {
			if (usedItems.Get(posPU)) {
					
				continue;
			}
			unUsedItems.Set(posPU, itemPU);
		}
		
		if (usedItems.Count() == 0 || usedItems.Count() != marketOfferItems.Count()) {
			errorMessage = "#you_offer_not_all_wanted_items";
			return false;
		}
		
		return true;
    }
	
	array <P2PTraderStockItem> GetUsedItems() {
		array <P2PTraderStockItem> collection = new array <P2PTraderStockItem>;
		foreach(P2PTraderStockItem item: usedItems) {
			DebugMessageP2PTrader("used item: " + item.GetType());
			collection.Insert(item);
		}
		return collection;
	}
	
	array <P2PTraderStockItem> GetUnUsedItems() {
		array <P2PTraderStockItem> collection = new array <P2PTraderStockItem>;
		foreach(P2PTraderStockItem item: unUsedItems) {
			DebugMessageP2PTrader("unused item: " + item.GetType());
			collection.Insert(item);
		}
		return collection;
	}
}