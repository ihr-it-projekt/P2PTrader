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
		
		if (marketOfferItems.Count() >  playerOfferItems.Count()) {
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
					usedItems.Set(posP, itemP);
				}
			}
		}
		
		foreach(int posPU, P2PTraderStockItem itemPU: playerOfferItems) {
			if (usedItems.Get(posPU)) {
					
				continue;
			}
			usedItems.Set(posPU, itemPU);
		}
		
		if (usedItems.Count() != marketOfferItems.Count()) {
			errorMessage = "#you_offer_not_all_wanted_items";
			return false;
		}
		
		return true;
    }
	
	string GetErrorMessage() {
		return errorMessage;
	}
	
	array <P2PTraderStockItem> GetUnUsedItems() {
		return unUsedItems.GetValueArray();
	}
}