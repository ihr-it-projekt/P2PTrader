class P2PTraderPlayerOfferEventHandler
{
	private ref P2PTraderPlayerInventory inventory;
	private P2PTraderStock traderStock;
	
    void P2PTraderPlayerOfferEventHandler(P2PTraderStock traderStock) {
		this.traderStock = traderStock;
        DebugMessageP2PTrader("Register P2PTraderPlayerOfferEventHandler");
        inventory = new P2PTraderPlayerInventory;
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
    }

    void ~P2PTraderPlayerOfferEventHandler() {
        GetDayZGame().Event_OnRPC.Remove(HandleEvents);
    }

    void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (!IsServerP2PTrader()) {
            return;
        }
		
		int offerId;
		
        if (rpc_type == P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS) {
			DebugMessageP2PTrader("receive P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS");
            Param2<DayZPlayer, int> parameterRemoveOffer;
            if (ctx.Read(parameterRemoveOffer)) {
                DayZPlayer player = parameterRemoveOffer.param1;
				offerId = parameterRemoveOffer.param2;
				
				P2PTraderPlayerPlayerOffer playerOffer = traderStock.GetPlayerOfferById(offerId);

                if (playerOffer == null) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS_ERROR, new Param1<string>("#offer_not_exists"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS_ERROR to player: no offer found");
                    return;
                } else if (playerOffer.GetOwnerId() != player.GetIdentity().GetPlainId()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS_ERROR, new Param1<string>("#you_can_only_remove_your_own_offer"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS_ERROR to player: owner is same then ");
                    return;
                }

				inventory.AddCollection(player, playerOffer.GetOfferItems());
				
				traderStock.RemovePlayerToPlayerOffer(playerOffer);
				
				GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS_RESPONSE, new Param1<bool>(true), true, player.GetIdentity());
                DebugMessageP2PTrader("send P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS_RESPONSE to player");
            }
        }
    }
};