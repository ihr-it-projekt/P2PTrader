class P2PItemService
{
	private ref P2PTraderPlayerInventory inventory;
	private ref TStringArray configs;
	private ref array<ref P2PTraderItem> itemsFromConfig;
	private P2PTraderCategoryCollection categoryItemsInventory;
	P2PTraderConfigParams configParams;

	void P2PItemService(P2PTraderConfig config) {
		inventory = new P2PTraderPlayerInventory;
		configParams = config.traderConfigParams;
		
		configs = new TStringArray;
		configs.Insert( CFG_VEHICLESPATH );
		configs.Insert( CFG_WEAPONSPATH );
		configs.Insert( CFG_MAGAZINESPATH );
		configs.Insert( "CfgNonAIVehicles" );
		configs.Insert( "CfgAmmo" );
		
		itemsFromConfig = new array<ref P2PTraderItem>;
		P2PTraderCategoryCollection categoryItems = config.traderItemsConfig.GetItems();
		categoryItemsInventory = config.traderItemsConfig.GetItems();
				
		if (categoryItems) {
		    array<ref P2PTraderCategory> categories = categoryItems.GetCategories();
			foreach (P2PTraderCategory category: categories){
				int categoryId = category.GetId();
				array<ref P2PTraderCategoryItem> catItems = category.GetItems();

				foreach(P2PTraderCategoryItem itemCat: catItems) {
					P2PTraderItem item = new P2PTraderItem(itemCat.GetName(), categoryId);
					item.SetTranslation(GetItemDisplayName(itemCat.GetName()), config.traderConfigParams.enableOrigenItemsNameInView);
					itemsFromConfig.Insert(item);
				}
			}
		}
	}
	
	void InitMarketItems(array<ref P2PTraderPlayerMarketOffer> marketItems) {
		foreach(P2PTraderPlayerMarketOffer offer: marketItems) {
			if (!offer) {
				continue;
			}
			
			array <ref P2PTraderStockItem> offerItems = offer.GetOfferItems();
			
			if (!offerItems) {
				continue;
			}
			foreach(P2PTraderStockItem item: offerItems) {
				if (item) {
					item.SetTranslation(GetItemDisplayName(item.GetType()), configParams.enableOrigenItemsNameInView);
				}
			}
			
			if (offerItems.Count() == 0) {
				array <ref P2PTraderStockItem> wantedItems = offer.GetWantedItems();
				foreach(P2PTraderStockItem itemWanted: wantedItems) {
					if (itemWanted) {
						itemWanted.SetTranslation(GetItemDisplayName(itemWanted.GetType()), configParams.enableOrigenItemsNameInView);
					}
				}
			}
		}
	}
	
	ref array <ref P2PTraderPlayerPlayerOffer> GetPlayerOffersForMarketOffer(P2PTraderPlayerMarketOffer selectedMarketOffer, array<ref P2PTraderPlayerPlayerOffer> allActiveOffers) {
		ref array <ref P2PTraderPlayerPlayerOffer> offers = new array <ref P2PTraderPlayerPlayerOffer>;
		
		if (!selectedMarketOffer) {
			return offers;
		}
		
		foreach(P2PTraderPlayerPlayerOffer offer: allActiveOffers) {
			if (!offer) {
				continue;
			}
			if (selectedMarketOffer.GetId() == offer.GetPlayerToMarketOfferId()) {
				offers.Insert(offer);
			}
		}
		
		return offers;
	}
	
	P2PTraderStockItem GetSelectedItemPlayerOffer(TextListboxWidget source) {
		int markedPos = source.GetSelectedRow();
		if (markedPos == -1) {
		    return null;
		}

		P2PTraderStockItem item;
		source.GetItemData(markedPos, 0, item);
		
		return item;
	}
	
	P2PTraderPlayerPlayerOffer GetSelectedStockItem(TextListboxWidget source) {
		int markedPos = source.GetSelectedRow();
		
		if (-1 == markedPos) {
			return null;
		}
		
		P2PTraderPlayerPlayerOffer item;
		source.GetItemData(markedPos, 0, item);
		
		return item;
	}
	
	P2PTraderPlayerMarketOffer GetSelectedMarketOffer(TextListboxWidget source) {
		int markedPos = source.GetSelectedRow();
		
		if (markedPos == -1) {
			return null;
		}
		
		P2PTraderPlayerMarketOffer item;
		source.GetItemData(markedPos, 0, item);
		
		return item;
	}
	
	TextListboxWidget GetMarketItemList(TextListboxWidget widget, array<ref P2PTraderPlayerMarketOffer> marketItems, string search, string offerType, int categoryIndex) {
		widget.ClearItems();
		string itemNames;
		foreach(P2PTraderPlayerMarketOffer offer: marketItems) {
			if(!offer) {
				continue;
			}
			
			bool isOfferType = P2PTraderPlayerMarketOffer.TYPE_ALL == offerType;
			if(!isOfferType) {
				isOfferType = offer.IsOfferType(offerType);
			}
			
			if (categoryIndex != -1 && !offer.IsCategory(categoryIndex)) {
				continue;
			}
			
			if (isOfferType && (search == "" || offer.Contains(search))) {
				itemNames = "";
				array <ref P2PTraderStockItem> offerItems = offer.GetOfferItems();
				foreach(P2PTraderStockItem item: offerItems) {
					if (item) {
						DebugMessageP2PTrader("use item translation");
						itemNames = itemNames + item.GetTranslation();
					}
				}
				
				if (offerItems.Count() == 0) {
					itemNames = "*";
					array <ref P2PTraderStockItem> wantedItems = offer.GetWantedItems();
					foreach(P2PTraderStockItem itemWanted: wantedItems) {
						if (itemWanted) {
							itemNames = itemNames + itemWanted.GetTranslation();
						}
					}
				}
				widget.AddItem(itemNames, offer, 0);
			}
		}
		
		return widget;
	}
	
	TextListboxWidget GetMarketOfferItemList(TextListboxWidget widget, P2PTraderPlayerMarketOffer marketItem) {
		widget.ClearItems();
		
		if (!marketItem) {
			return widget;
		}
		
		array <ref P2PTraderStockItem> offerItems = marketItem.GetOfferItems();
		
		if (!offerItems) {
			return widget;
		}
		
		foreach(P2PTraderStockItem item: offerItems) {
			if (item) {
				if (!item.HasTranslation()) {
					item.SetTranslation(GetItemDisplayName(item.GetType()), configParams.enableOrigenItemsNameInView);
				}
				
				widget.AddItem(item.GetTranslation(), item, 0);
			}
		}

		return widget;
	}
	
	TextListboxWidget GetActiveOffersForStockItem(TextListboxWidget playerOffers, array <ref P2PTraderPlayerPlayerOffer> activeOffers) {
		playerOffers.ClearItems();
        foreach(P2PTraderPlayerPlayerOffer activeOffer: activeOffers) {
			string name = "";
		
			array <ref P2PTraderStockItem> offerItems = activeOffer.GetOfferItems();
			foreach(P2PTraderStockItem item: offerItems) {
				if (!item.HasTranslation()) {
					item.SetTranslation(GetItemDisplayName(item.GetType()), configParams.enableOrigenItemsNameInView);
				}
				
				name += item.GetTranslation() + "; ";
			}
						
			playerOffers.AddItem(name, activeOffer, 0);
		}
		
		return playerOffers;
	}
	
	TextListboxWidget GetMarketOfferItemAttachmentList(TextListboxWidget widget, P2PTraderStockItem offerItem, bool clearWidget = true) {
		if (clearWidget) {
			widget.ClearItems();
		}

		array<ref P2PTraderStockItem> attachedItems = offerItem.GetAttached();
		
		foreach(P2PTraderStockItem item: attachedItems) {
			if (item) {
				if (!item.HasTranslation()) {
					item.SetTranslation(GetItemDisplayName(item.GetType()), configParams.enableOrigenItemsNameInView);
				}
				
				int pos = widget.AddItem(item.GetTranslation(), item, 0);
				
				GetMarketOfferItemAttachmentList(widget, item, false);
			}
		}
		
		return widget;
	}
	
	TextListboxWidget GetPlayerItemList(TextListboxWidget widget, array<ref P2PTraderItem> playerItems) {
		widget.ClearItems();
		
		foreach(P2PTraderItem item: playerItems) {
			if (item) {
				if (!item.HasTranslation()) {
					item.SetTranslation(GetItemDisplayName(item.GetType()), configParams.enableOrigenItemsNameInView);
				}
				widget.AddItem(item.GetTranslation(), item, 0);
			}
		}
		
		return widget;
	}
	
	TextListboxWidget GetTraderStockItemList(TextListboxWidget widget, array <ref P2PTraderStockItem> offerItems) {
		widget.ClearItems();
				
		foreach(P2PTraderStockItem item: offerItems) {
			if (item) {
				if (!item.HasTranslation()) {
					item.SetTranslation(GetItemDisplayName(item.GetType()), configParams.enableOrigenItemsNameInView);
				}
				
				widget.AddItem(item.GetTranslation(), item, 0);
			}
		}
		
		return widget;
	}
	
	void AddTradableItemsToWidgetByCategory(TextListboxWidget widget, string search, int catId) {
		widget.ClearItems();

        int addedItems = 0;
		foreach (P2PTraderItem item: itemsFromConfig){
			if (catId != -1 && item.GetCategory() != catId) {
				continue;
			}
			
			if (!item.Contains(search)){
				continue;
			}
			
			widget.AddItem(item.GetTranslation(), item, 0);
			addedItems = addedItems + 1;
		}
	}
	
	void AddTradableItemsToWidget(TextListboxWidget widget, string search) {
		widget.ClearItems();

        int addedItems = 0;
		foreach (P2PTraderItem item: itemsFromConfig){
			if (!item.Contains(search)){
				continue;
			}
			
			widget.AddItem(item.GetTranslation(), item, 0);
			addedItems = addedItems + 1;
		}
	}

	string CreateOffer(DayZPlayer player, TextListboxWidget offer, TextListboxWidget wanted, string offerText, string offerType) {
		int countOfferItems = offer.GetNumItems();
		int countWantedItems = wanted.GetNumItems();
		
		ref array<ref P2PTraderItem> offerItems = new array<ref P2PTraderItem>;
		ref array<ref P2PTraderItem> wantedItems = new array<ref P2PTraderItem>;
		P2PTraderItem item;
		int x;
		
		for(x = 0; x < countOfferItems; x++) {
			item = null;
			offer.GetItemData(x, 0, item);
			if (item) {
				offerItems.Insert(item);
			}
		}
		for(x = 0; x < countWantedItems; x++) {
			item = null;
			wanted.GetItemData(x, 0, item);
			if (item) {
				wantedItems.Insert(item);
			}
		}

		if (wantedItems.Count() == 0 && offerItems.Count() == 0) {
		    return "#you_can_not_make_an_empty_offer";
		}

		GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER, new Param5<DayZPlayer, ref array<ref P2PTraderItem>, ref array<ref P2PTraderItem>, string, string>(player, offerItems, wantedItems, offerText, offerType), true);
		return "";
	}

	string CreateOfferToPlayer(DayZPlayer player, TextListboxWidget offer, P2PTraderPlayerMarketOffer selectedMarketOffer, string offerText) {
		int offerId = selectedMarketOffer.GetId();
        int countOfferItems = offer.GetNumItems();

        ref array<ref P2PTraderItem> offerItems = new array<ref P2PTraderItem>;
        for(int x = 0; x < countOfferItems; x++) {
            P2PTraderItem item = null;
            offer.GetItemData(x, 0, item);
            if (item) {
                offerItems.Insert(item);
            }
        }

        if (offerItems.Count() == 0) {
            return "you_can_not_make_an_empty_offer";
        }
		
        GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER, new Param4<DayZPlayer, ref array<ref P2PTraderItem>, int, string>(player, offerItems, offerId, offerText), true);

		return "";
	}
	
	ref P2PTraderPlayerPlayerOffer GetPlayerSingleOffersForMarketOffer(P2PTraderPlayerMarketOffer offer, array<ref P2PTraderPlayerPlayerOffer> playerOffers) {
		foreach(P2PTraderPlayerPlayerOffer offerPlayer: playerOffers) {
			if (offer.GetId() == offerPlayer.GetPlayerToMarketOfferId()) {
				return offerPlayer;
			}
		}
		return null;
	}
	
	string GetItemDisplayName(string itemClassname){
		string cfg;
		string displayName;
		
		foreach (string itemName: configs){
			cfg = itemName + " " + itemClassname + " displayName";

	    	GetGame().ConfigGetText(cfg, displayName);
			
			if (displayName != ""){
				displayName.Replace("$UNT$", "");
			
				break;
			}
		}
		
		if (displayName == "") {
			displayName = itemClassname;
		}
	
	    return displayName;
	}
	
	P2PTraderCategoryCollection GetCategoryItemsInventory() {
		return categoryItemsInventory;
	}
}
