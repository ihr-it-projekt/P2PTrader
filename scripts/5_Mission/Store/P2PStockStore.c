class P2PStockStore
{
	private ref array<ref P2POfferFileMatch> fileMatchCollectionStock;
	private ref array<ref P2POfferFileMatch> fileMatchCollectionOffers;
	private ref array<ref P2POfferFileMatch> fileMatchCollectionOffersInactive;
	private ref array<ref P2POfferFileMatch> fileMatchCollectionOffersAccepted;
	
	void SaveStock(P2PTraderStock traderStock) {
		fileMatchCollectionStock = new array<ref P2POfferFileMatch>;
		fileMatchCollectionOffers = new array<ref P2POfferFileMatch>;
		fileMatchCollectionOffersInactive = new array<ref P2POfferFileMatch>;
		fileMatchCollectionOffersAccepted = new array<ref P2POfferFileMatch>;
		
		SaveMarketOffer(traderStock.GetStock(), fileMatchCollectionStock);
		SavePlayerOffer(traderStock.GetOffersFromAllPlayer(), fileMatchCollectionOffers);
		SavePlayerOffer(traderStock.GetInactiveOffersFromAllPlayer(), fileMatchCollectionOffersInactive);
		SavePlayerOffer(traderStock.GetAcceptedOffersFromAllPlayer(), fileMatchCollectionOffersAccepted);
		
		P2PJsonFileLoader<array<ref P2POfferFileMatch>>.JsonSaveFile(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionStock.json", fileMatchCollectionStock);
		P2PJsonFileLoader<array<ref P2POfferFileMatch>>.JsonSaveFile(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionOffers.json", fileMatchCollectionOffers);
		P2PJsonFileLoader<array<ref P2POfferFileMatch>>.JsonSaveFile(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionOffersInactive.json", fileMatchCollectionOffersInactive);
		P2PJsonFileLoader<array<ref P2POfferFileMatch>>.JsonSaveFile(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionOffersAccepted.json", fileMatchCollectionOffersAccepted);
    }
	
	P2PTraderStock LoadStock(ref P2PTraderStock stockFile) {
		int id = 0;
				
		if (FileExist(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionStock.json")) {
			JsonFileLoader<array<ref P2POfferFileMatch>>.JsonLoadFile(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionStock.json", fileMatchCollectionStock);
			if (fileMatchCollectionStock) {
				id = LoadMarketOffer(id, stockFile.stock, fileMatchCollectionStock);
			}
		}
		
		if (FileExist(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionOffers.json")) {
			JsonFileLoader<array<ref P2POfferFileMatch>>.JsonLoadFile(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionOffers.json", fileMatchCollectionOffers);
			if (fileMatchCollectionOffers) {
				id = LoadPlayerOffer(id, stockFile.playerOffers, fileMatchCollectionOffers);
			}
		}
		
		if (FileExist(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionOffersInactive.json")) {
			JsonFileLoader<array<ref P2POfferFileMatch>>.JsonLoadFile(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionOffersInactive.json", fileMatchCollectionOffersInactive);
			if (fileMatchCollectionOffersInactive) {
				id = LoadPlayerOffer(id, stockFile.playerOffersInactive, fileMatchCollectionOffersInactive);
			}
		}
		
		if (FileExist(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionOffersAccepted.json")) {
			JsonFileLoader<array<ref P2POfferFileMatch>>.JsonLoadFile(CONFIGS_STOCK_FOLDER_P2P + "fileMatchCollectionOffersAccepted.json", fileMatchCollectionOffersAccepted);
			if (fileMatchCollectionOffersAccepted) {
				id = LoadPlayerOffer(id, stockFile.acceptedPlayerOffers, fileMatchCollectionOffersAccepted);
			}
		}
		
		stockFile.idCounter = id + 1;
		
		return stockFile;
	}
	
	static void RemoveById(int id) {
		if (FileExist(CONFIGS_STOCK_FOLDER_P2P +  id + ".json")) {
			DeleteFile(CONFIGS_STOCK_FOLDER_P2P +  id + ".json");
		}
	}
	
	private void SaveMarketOffer(array<ref P2PTraderPlayerMarketOffer> marketOffers, array<ref P2POfferFileMatch> fileMatchCollection) {
		foreach(P2PTraderPlayerMarketOffer offer: marketOffers) {
			ref P2POfferFileMatch match = new P2POfferFileMatch(offer.GetId(), offer.getAllItemTypes(), offer.getAllCategoryIds());
			
			RemoveById(offer.GetId());
			
			P2PJsonFileLoader<P2PTraderPlayerMarketOffer>.JsonSaveFile(match.fileName, offer);
			fileMatchCollection.Insert(match);
		}
	}
	
	private int LoadMarketOffer(int currentId, ref array<ref P2PTraderPlayerMarketOffer> offers, array<ref P2POfferFileMatch> fileMatchCollection) {
		foreach(P2POfferFileMatch match: fileMatchCollection) {
			ref P2PTraderPlayerMarketOffer offer;
			JsonFileLoader<P2PTraderPlayerMarketOffer>.JsonLoadFile(match.fileName, offer);
			
			if (offer) {
				if (currentId < offer.GetId()) {
					currentId = offer.GetId();
				}
				
				offer.UpdateCategories(match.types, match.categoryIds);
				
				offers.Insert(offer);
			}
		}
		
		return currentId;
	}
	
	private void SavePlayerOffer(array<ref P2PTraderPlayerPlayerOffer> offers, array<ref P2POfferFileMatch> fileMatchCollection) {
		foreach(P2PTraderPlayerPlayerOffer offer: offers) {
			ref P2POfferFileMatch match = new P2POfferFileMatch(offer.GetId(), offer.getAllItemTypes(), offer.getAllCategoryIds());
			
			RemoveById(offer.GetId());
			
			P2PJsonFileLoader<P2PTraderPlayerPlayerOffer>.JsonSaveFile(match.fileName, offer);
			fileMatchCollection.Insert(match);
		}
	}
	
	
	private int LoadPlayerOffer(int currentId, notnull ref array<ref P2PTraderPlayerPlayerOffer> offers, notnull array<ref P2POfferFileMatch> fileMatchCollection) {
		foreach(P2POfferFileMatch match: fileMatchCollection) {
			ref P2PTraderPlayerPlayerOffer offer;
			JsonFileLoader<P2PTraderPlayerPlayerOffer>.JsonLoadFile(match.fileName, offer);
			
			if (offer) {
				if (currentId < offer.GetId()) {
					currentId = offer.GetId();
				}
				offer.UpdateCategories(match.types, match.categoryIds);
				offers.Insert(offer);
			}
		}
		
		return currentId;
	}
}

class P2POfferFileMatch
{
	int id;
	ref array<string> types;
	ref array<int> categoryIds;
	string fileName;
	
	void P2POfferFileMatch(int id, ref array<string> types, ref array<int> categoryIds) {
		this.id = id;
		this.types = types;
		this.categoryIds = categoryIds;
		
		this.fileName = CONFIGS_STOCK_FOLDER_P2P +  id.ToString() + ".json";
	}
}
