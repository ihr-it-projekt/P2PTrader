class P2PTraderOfferEventHandler
{
	private ref P2PTraderPlayerInventory inventory;
	private P2PTraderStock traderStock;
	
    void P2PTraderOfferEventHandler(P2PTraderStock traderStock) {
		this.traderStock = traderStock;
        DebugMessageP2PTrader("Register P2PTraderOfferEventHandler");
        inventory = new P2PTraderPlayerInventory;
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
    }

    void ~P2PTraderOfferEventHandler() {
        GetDayZGame().Event_OnRPC.Remove(HandleEvents);
    }

    void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (!IsServerP2PTrader()) {
            return;
        }

        if (rpc_type == P2P_TRADER_EVENT_NEW_OFFER) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_NEW_OFFER");
            Param3<DayZPlayer, ref array<ref P2PTraderItem>, ref array<ref P2PTraderItem>> parameterOffer;
            if (ctx.Read(parameterOffer)) {
                DayZPlayer player = parameterOffer.param1;
				ref array<ref P2PTraderItem> offerItems = parameterOffer.param2;
				ref array<ref P2PTraderItem> wantedItems = parameterOffer.param3;
                DebugMessageP2PTrader("Check Player has items");
				
				array<EntityAI> items = inventory.GetPlayerItems(player);
				
				P2PTraderPlayerMarketOffer offer = new P2PTraderPlayerMarketOffer(player);
				
				DebugMessageP2PTrader("have offer items" + offerItems.Count().ToString());
				DebugMessageP2PTrader("have wanted items" + wantedItems.Count().ToString());
				
				
				foreach(EntityAI item: items) {
					ItemBase itemCast = ItemBase.Cast(item);
					foreach(P2PTraderItem offerItem: offerItems) {
						if (itemCast && offerItem && offerItem.item && offerItem.item.GetHealth() == itemCast.GetHealth() && offerItem.item.GetType() == itemCast.GetType() && offerItem.item.GetQuantity() == itemCast.GetQuantity()) {
							offer.AddOfferItem(offerItem.item);
							inventory.Remove(itemCast, player);
						}
					}
				}
				
				foreach(P2PTraderItem itemWantToHave: wantedItems) {
					offer.AddWantedItem(itemWantToHave.item);
				}
				
				DebugMessageP2PTrader("Create offer in stock");
				traderStock.AddPlayerToMarketOffer(offer);
				
                if (true){
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_RESPONSE, new Param1<bool>(true), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_NEW_OFFER_RESPONSE to player");
                } else {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_RESPONSE_ERROR, new Param1<string>("#error"), true,  player.GetIdentity());
                }
            }
        }
    }

};