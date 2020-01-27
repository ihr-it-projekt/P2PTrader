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
			DebugMessageP2PTrader("receive P2P_TRADER_EVENT_NEW_OFFER");
            Param4<DayZPlayer, ref array<ref P2PTraderItem>, ref array<ref P2PTraderItem>, string> parameterOffer;
            if (ctx.Read(parameterOffer)) {
                DayZPlayer player = parameterOffer.param1;
				ref array<ref P2PTraderItem> offerItems = parameterOffer.param2;
				ref array<ref P2PTraderItem> wantedItems = parameterOffer.param3;
				string offerMessage = parameterOffer.param4
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

				if (offer.IsEmpty()) {
                    GetGame().RPCSingleParam(offerPlayer, P2P_TRADER_EVENT_NEW_OFFER_RESPONSE_ERROR, new Param1<string>("#you_can_not_make_an_empty_offer"), true, offerPlayer.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_NEW_OFFER_RESPONSE_ERROR to player: owner is same then ");
                    return;
				}
				
				DebugMessageP2PTrader("Create offer in stock");
				traderStock.AddPlayerToMarketOffer(offer);
				
				GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_RESPONSE, new Param1<bool>(true), true, player.GetIdentity());
                DebugMessageP2PTrader("send P2P_TRADER_EVENT_NEW_OFFER_RESPONSE to player");
            }
        } else if (rpc_type == P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER) {
			DebugMessageP2PTrader("receive P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER");
            Param4<DayZPlayer, ref array<ref P2PTraderItem>, int, string> parameterOffer;
            if (ctx.Read(parameterOffer)) {
                DayZPlayer offerPlayer = parameterOffer.param1;
				ref array<ref P2PTraderItem> offerPlayerItems = parameterOffer.param2;
				int offerId = parameterOffer.param3;
				string offerPlayerMessage = parameterOffer.param4
                DebugMessageP2PTrader("Check Player has items");

				array<EntityAI> itemsPlayer = inventory.GetPlayerItems(offerPlayer);

                P2PTraderPlayerMarketOffer playerMarketOffer = traderStock.GetPlayerToMarketOfferById(offerId);

				if (playerMarketOffer == null) {
                    GetGame().RPCSingleParam(offerPlayer, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR, new Param1<string>("#offer_not_exists"), true, offerPlayer.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR to player: no offer found");
                    return;
				} else if (!P2P_TRADER_DEBUG && playerMarketOffer.GetOwnerId == offerPlayer.GetIdentity().GetPlainId()) {
                    GetGame().RPCSingleParam(offerPlayer, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR, new Param1<string>("#you_can_not_make_yourself_an_offer"), true, offerPlayer.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR to player: owner is same then ");
                    return;
				}

                P2PTraderPlayerPlayerOffer offerFromPlayer = new P2PTraderPlayerPlayerOffer(offerPlayer, offerId);

				DebugMessageP2PTrader("have offer items" + offerPlayerItems.Count().ToString());

				foreach(EntityAI item: itemsPlayer) {
					ItemBase itemPlayerCast = ItemBase.Cast(item);
					foreach(P2PTraderItem offerItem: offerItems) {
						if (itemPlayerCast && offerItem && offerItem.item && offerItem.item.GetHealth() == itemPlayerCast.GetHealth() && offerItem.item.GetType() == itemPlayerCast.GetType() && offerItem.item.GetQuantity() == itemPlayerCast.GetQuantity()) {
                            offerFromPlayer.AddOfferItem(offerItem.item);
							inventory.Remove(itemPlayerCast, offerPlayer);
						}
					}
				}

				DebugMessageP2PTrader("Create offer for player in stock");
				traderStock.AddPlayerToPlayerOffer(offerFromPlayer);
                playerMarketOffer.AddPlayerOffer(offerFromPlayer);

                GetGame().RPCSingleParam(offerPlayer, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE, new Param1<bool>(true), true, offerPlayer.GetIdentity());
                DebugMessageP2PTrader("send P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE to player");
            }
        }
    }
};