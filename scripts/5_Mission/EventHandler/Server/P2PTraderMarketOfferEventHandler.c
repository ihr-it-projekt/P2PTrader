class P2PTraderMarketOfferEventHandler
{
	private ref P2PTraderPlayerInventory inventory;
	private P2PTraderStock traderStock;
	
    void P2PTraderMarketOfferEventHandler(P2PTraderStock traderStock) {
		this.traderStock = traderStock;
        DebugMessageP2PTrader("Register P2PTraderMarketOfferEventHandler");
        inventory = new P2PTraderPlayerInventory;
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
    }

    void ~P2PTraderMarketOfferEventHandler() {
        GetDayZGame().Event_OnRPC.Remove(HandleEvents);
    }

    void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (!IsServerP2PTrader()) {
            return;
        }
		
		int offerId;
		P2PTraderPlayerMarketOffer playerMarketOffer;
		DayZPlayer player;

        if (rpc_type == P2P_TRADER_EVENT_TAKE_OFFER) {
			DebugMessageP2PTrader("receive P2P_TRADER_EVENT_TAKE_OFFER");
            Param3<DayZPlayer, int, int> parameterTakeOffer;
            if (ctx.Read(parameterTakeOffer)) {
                player = parameterTakeOffer.param1;
				int playerOfferId = parameterTakeOffer.param2;
				offerId = parameterTakeOffer.param3;
				
				DebugMessageP2PTrader("offer id: " + offerId.ToString() + "player offer id" + playerOfferId.ToString());

                playerMarketOffer = traderStock.GetPlayerToMarketOfferById(offerId);
                P2PTraderPlayerPlayerOffer playerPlayerOffer = traderStock.GetPlayerOfferById(playerOfferId);

                if (playerMarketOffer == null) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR, new Param1<string>("#offer_not_exists"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR to player: no market offer found");
                    return;
                } else if (playerPlayerOffer == null) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR, new Param1<string>("#player_offer_not_exists"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR to player: no player offer found");
                    return;
                } else if (playerMarketOffer.GetOwnerId() != player.GetIdentity().GetId()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR, new Param1<string>("#you_can_only_use_your_own_order"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR to player: is not owner of market offer");
                    return;
                } else if (playerPlayerOffer.GetOwnerId() == player.GetIdentity().GetId()) {
					GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR, new Param1<string>("#you_can_not_accept_your_own_order"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR to player: is owner of player offer");
                    return;
				}

				inventory.AddCollection(player, playerPlayerOffer.GetOfferItems());
				
				traderStock.AcceptPlayerToPlayerOffer(playerMarketOffer, playerPlayerOffer);
				
				GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE, new Param1<bool>(true), true, player.GetIdentity());
                DebugMessageP2PTrader("send P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE to player");
            }
        } else if (rpc_type == P2P_TRADER_EVENT_REMOVE_OFFER) {
			DebugMessageP2PTrader("receive P2P_TRADER_EVENT_REMOVE_OFFER");
            Param2<DayZPlayer, int> parameterRemoveOffer;
            if (ctx.Read(parameterRemoveOffer)) {
                player = parameterRemoveOffer.param1;
				offerId = parameterRemoveOffer.param2;
                playerMarketOffer = traderStock.GetPlayerToMarketOfferById(offerId);

                if (playerMarketOffer == null) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE_ERROR, new Param1<string>("#offer_not_exists"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR to player: no offer found");
                    return;
                } else if (playerMarketOffer.GetOwnerId() != player.GetIdentity().GetId()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE_ERROR, new Param1<string>("#you_can_only_remove_your_own_order"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE_ERROR to player: is not owner of market offer");
                    return;
                }

				inventory.AddCollection(player, playerMarketOffer.GetOfferItems());
				
				traderStock.RemovePlayerToMarketOffer(playerMarketOffer);
				
				GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE, new Param1<bool>(true), true, player.GetIdentity());
                DebugMessageP2PTrader("send P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE to player");
            }
        }
    }
};