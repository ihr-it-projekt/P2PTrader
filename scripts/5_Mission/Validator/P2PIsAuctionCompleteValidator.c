class P2PIsAuctionCompleteValidator
{
	private string errorMessage = "";
	private ref map <int, P2PTraderStockItem> usedItems
	private ref map <int, P2PTraderStockItem> unUsedItems
	
	void P2PIsAuctionCompleteValidator() {
		usedItems = new map <int, P2PTraderStockItem>;
		unUsedItems = new map <int, P2PTraderStockItem>;
	}
	
    bool IsValid(P2PTraderPlayerMarketOffer marketOffer, P2PTraderPlayerPlayerOffer playerOffer) {
		array <ref P2PTraderStockItem> marketOfferItems = marketOffer.GetWantedItems();
		array <P2PTraderStockItem> playerOfferItems = playerOffer.GetAllItems();
		
		
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
	
	string GetErrorMessage() {
		return errorMessage;
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