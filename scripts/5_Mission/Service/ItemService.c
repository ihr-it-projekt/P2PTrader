class ItemService
{
	private ref P2PTraderPlayerInventory inventory;
	private ref TStringArray configs;
	private P2PTraderConfig config;
	private ref array<ref P2PTraderItem> itemsFromConfig;
	
	void ItemService(P2PTraderConfig config) {
		this.config = config;
		inventory = new P2PTraderPlayerInventory;
		
		configs = new TStringArray;
		configs.Insert( CFG_VEHICLESPATH );
		configs.Insert( CFG_WEAPONSPATH );
		configs.Insert( CFG_MAGAZINESPATH );
		configs.Insert( "CfgNonAIVehicles" );
		configs.Insert( "CfgAmmo" );
		
		itemsFromConfig = new array<ref P2PTraderItem>;
		
		DebugMessageP2PTrader("Has got Items from config: " + config.traderItemsConfig.items.Count().ToString());
		
		foreach (string itemName: config.traderItemsConfig.items){
			//DebugMessageP2PTrader("Add tradeable item type " + itemName);
			P2PTraderItem item = new P2PTraderItem(itemName);
			item.SetTranslation(GetItemDisplayName(itemName));
			itemsFromConfig.Insert(item);
		}
	}
	
	P2PTraderPlayerMarketOffer GetSelectedMarketOffer(TextListboxWidget source) {
		int markedPos = source.GetSelectedRow();
		P2PTraderPlayerMarketOffer item;
		source.GetItemData(markedPos, 0, item);
		
		return item;
	}
	
	void MoveItemFromListWidgetToListWidget(TextListboxWidget source, TextListboxWidget target = null, bool move = true) {
		int markedPos = source.GetSelectedRow();
		P2PTraderItem item;
		source.GetItemData(markedPos, 0, item);
		
		if (item) {
			if (target) {
				target.AddItem(item.translatedName, item, 0);
			}
			
			if (move) {
				source.RemoveRow(markedPos);
			}
		}
	}
	
	TextListboxWidget GetMarketItemList(TextListboxWidget widget, array<ref P2PTraderPlayerMarketOffer> marketItems, string search) {
		widget.ClearItems();
		search.ToLower();
		
		foreach(P2PTraderPlayerMarketOffer offer: marketItems) {
			if (search == "" || (search != "" && !offer.ContainsItemType(search))) {
				string itemNames;
				foreach(P2PTraderStockItem item: offer.GetOfferItems()) {
					if (item) {
						itemNames = itemNames + item.GetTranslation();
					}
				}
				widget.AddItem(itemNames, offer, 0);
			}
		}
		
		return widget;
	}
	
	TextListboxWidget GetMarketItemListInit(TextListboxWidget widget, array<ref P2PTraderPlayerMarketOffer> marketItems) {
		widget.ClearItems();
		
		foreach(P2PTraderPlayerMarketOffer offer: marketItems) {
			string itemNames;
			foreach(P2PTraderStockItem item: offer.GetOfferItems()) {
				if (item) {
					if (!item.HasTranslation()) {
						item.SetTranslation(GetItemDisplayName(item.GetType()));
					}
					
					itemNames = itemNames + item.GetTranslation();
					
				}
			}
			widget.AddItem(itemNames, offer, 0);
		}
		
		return widget;
	}
	
	TextListboxWidget GetMarketOfferItemList(TextListboxWidget widget, P2PTraderPlayerMarketOffer marketItem) {
		widget.ClearItems();
		
		array <ref P2PTraderStockItem> offerItems = marketItem.GetOfferItems();
		
		foreach(P2PTraderStockItem item: offerItems) {
			if (item) {
				if (!item.HasTranslation()) {
					item.SetTranslation(GetItemDisplayName(item.GetType()));
				}
				
				int pos = widget.AddItem(item.GetTranslation(), item, 0);
				widget.SetItem(pos, "#healt" + item.GetHealth().ToString(), item, 1);
			}
		}
		
		return widget;
	}
	
	TextListboxWidget GetMarketOfferItemAttachmentList(TextListboxWidget widget, P2PTraderStockItem offerItem, bool clearWidget = true) {
		
		if (clearWidget) {
			widget.ClearItems();
		}

		array<ref P2PTraderStockItem> attachedItems = offerItem.GetAttached();
		
		foreach(P2PTraderStockItem item: attachedItems) {
			if (item) {
				if (!item.HasTranslation()) {
					item.SetTranslation(GetItemDisplayName(item.GetType()));
				}
				
				int pos = widget.AddItem(item.GetTranslation(), item, 0);
				widget.SetItem(pos, "#healt" + item.GetHealth().ToString(), item, 1);
				
				GetMarketOfferItemAttachmentList(widget, item, false);
			}
		}
		
		return widget;
	}
	
	P2PTraderStockItem GetSelectedStockItem(TextListboxWidget source) {
		int markedPos = source.GetSelectedRow();
		P2PTraderStockItem item;
		source.GetItemData(markedPos, 0, item);
		
		return item;
	}
	
	TextListboxWidget GetPlayerItemList(TextListboxWidget widget, array<ref P2PTraderItem> playerItems) {
		widget.ClearItems();
		
		foreach(P2PTraderItem item: playerItems) {
			if (item) {
				DebugMessageP2PTrader("Add inventory type " + item.name);
				
				item.SetTranslation(GetItemDisplayName(item.name));
				
				widget.AddItem(item.translatedName, item, 0);
			}
		}
		
		return widget;
	}
	
	void AddTradeableItemsToWidget(TextListboxWidget widget, string search) {		
		widget.ClearItems();
		
		search.ToLower();

		foreach (P2PTraderItem item: itemsFromConfig){
			if (search != "" && !item.translatedNameLower.Contains(search)){
				continue;
			}
			
			widget.AddItem(item.translatedName, item, 0);
		}
	}

	string CreateOffer(DayZPlayer player, TextListboxWidget offer, TextListboxWidget wanted, string offerText) {
		int countOfferItems = offer.GetNumItems();
		int countWantedItems = wanted.GetNumItems();
		
		DebugMessageP2PTrader("has count items" + countOfferItems.ToString() + " " + countWantedItems.ToString());
		
		ref array<ref P2PTraderItem> offerItems = new array<ref P2PTraderItem>;
		ref array<ref P2PTraderItem> wantedItems = new array<ref P2PTraderItem>;
		P2PTraderItem item;
		int x;
		
		DebugMessageP2PTrader("iterate offer");
		for(x = 0; x < countOfferItems; x++) {
			item = null;
			offer.GetItemData(x, 0, item);
			if (item) {
				DebugMessageP2PTrader("add offer" + item.name);
				offerItems.Insert(item);
			}
		}
		DebugMessageP2PTrader("iterate wanted");
		for(x = 0; x < countWantedItems; x++) {
			item = null;
			wanted.GetItemData(x, 0, item);
			if (item) {
				wantedItems.Insert(item);
			}
		}

		if (wantedItems.Count() == 0 && offerItems.Count() == 0) {
		    return "you_can_not_make_an_empty_offer";
		}

		DebugMessageP2PTrader("try send P2P_TRADER_EVENT_NEW_OFFER to server");
		GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER, new Param4<DayZPlayer, ref array<ref P2PTraderItem>, ref array<ref P2PTraderItem>, string>(player, offerItems, wantedItems, offerText), true);
		DebugMessageP2PTrader("try send P2P_TRADER_EVENT_NEW_OFFER to server");
		return "";
	}

	string CreateOfferToPlayer(DayZPlayer player, TextListboxWidget offer, int offerId, string offerText) {
        int countOfferItems = offer.GetNumItems();
        DebugMessageP2PTrader("has count items" + countOfferItems.ToString());

        ref array<ref P2PTraderItem> offerItems = new array<ref P2PTraderItem>;
        DebugMessageP2PTrader("iterate offer");
        for(int x = 0; x < countOfferItems; x++) {
            P2PTraderItem item = null;
            offer.GetItemData(x, 0, item);
            if (item) {
                DebugMessageP2PTrader("add offer" + item.name);
                offerItems.Insert(item);
            }
        }

        if (offerItems.Count() == 0) {
            return "you_can_not_make_an_empty_offer";
        }

        DebugMessageP2PTrader("try send P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER to server");
        GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER, new Param4<DayZPlayer, ref array<ref P2PTraderItem>, int, string>(player, offerItems, offerId, offerText), true);
        DebugMessageP2PTrader("try send P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER to server");
		return "";
	}
	
	P2PTraderPlayerPlayerOffer GetPlayerOffer(P2PTraderPlayerMarketOffer offer, array<ref P2PTraderPlayerPlayerOffer> playerOffers) {
		foreach(P2PTraderPlayerPlayerOffer offerPlayer: playerOffers) {
			if (offer.HasPlayerOfferId(offerPlayer.GetId())) {
				return offerPlayer;
			}
		}
		
		return null;
	}
	
	TextListboxWidget GetPlayerOfferItemList(TextListboxWidget widget, P2PTraderPlayerPlayerOffer offerItem) {
		widget.ClearItems();
		
		array <ref P2PTraderStockItem> offerItems = offerItem.GetOfferItems();
		
		foreach(P2PTraderStockItem item: offerItems) {
			if (item) {
				if (!item.HasTranslation()) {
					item.SetTranslation(GetItemDisplayName(item.GetType()));
				}
				
				int pos = widget.AddItem(item.GetTranslation(), item, 0);
				widget.SetItem(pos, "#healt" + item.GetHealth().ToString(), item, 1);
			}
		}
		
		return widget;
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
	
}