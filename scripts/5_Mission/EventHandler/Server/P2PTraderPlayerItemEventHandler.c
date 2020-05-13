class P2PTraderPlayerItemEventHandler
{
	private ref P2PTraderPlayerInventory inventory;
	private ref map<string, string> itemsMap;
	private ref map<string, string> itemsCategoryMap;
	private P2PTraderConfigParams config;
	
    void P2PTraderPlayerItemEventHandler(P2PTraderConfigParams config, P2PTraderItemsCategoryConfig itemConfig) {
		this.config = config;
		itemsMap = new map<string, string>();
		itemsCategoryMap = new map<string, string>();
		array<ref TStringArray> itemsInventory = itemConfig.GetItemsInventory();
		foreach(int categoryIndex, TStringArray itemsFromConfig: itemsInventory) {
			foreach(string itemName: itemsFromConfig) {
				itemsMap.Insert(itemName, itemName);
				string categoryName = itemConfig.GetCategoryName(categoryIndex);
				itemsCategoryMap.Insert(itemName, categoryName);
			}
		}
		
		DebugMessageP2PTrader("Register OfferEventHandler");
        inventory = new P2PTraderPlayerInventory;
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
    }

    void ~P2PTraderPlayerItemEventHandler() {
        GetDayZGame().Event_OnRPC.Remove(HandleEvents);
    }

    void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (!IsServerP2PTrader()) {
            return;
        }

        if (rpc_type == P2P_TRADER_EVENT_GET_PLAYER_ITEMS) {
			DebugMessageP2PTrader("receive P2P_TRADER_EVENT_GET_PLAYER_ITEMS");
            Param1<DayZPlayer> parameterPlayerItems;
            if (ctx.Read(parameterPlayerItems)) {
                DayZPlayer player = parameterPlayerItems.param1;
				array<EntityAI> items = inventory.GetPlayerItems(player);
				array<ref P2PTraderItem> playerItems = new array<ref P2PTraderItem>;
		
				foreach(EntityAI item: items) {
					if (item && !item.GetType().Contains("Survivor")) {
						if (item.GetHealth() == 0) {
							DebugMessageP2PTrader("Item helth is zero" + item.GetType());
							continue;
						}
						
						if (config.useItemsConfigForPlayerInventory && item && !itemsMap.Get(item.GetType())) {
							continue;
						}

						P2PTraderItem traderItem = new P2PTraderItem(item.GetType(), itemsCategoryMap.Get(item.GetType()), item);
						playerItems.Insert(traderItem);
					}
				}
				
                GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_GET_PLAYER_ITEMS_RESPONSE, new Param1<ref array<ref P2PTraderItem>>(playerItems), true, player.GetIdentity());
                DebugMessageP2PTrader("send P2P_TRADER_EVENT_GET_PLAYER_ITEMS_RESPONSE to player");
            } else {
              	GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_GET_PLAYER_ITEMS_RESPONSE_ERROR, new Param1<string>("#error"), true,  player.GetIdentity());
            }
        }
    }

};