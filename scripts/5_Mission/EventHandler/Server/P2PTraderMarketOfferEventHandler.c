class P2PTraderMarketOfferEventHandler {
    private ref P2PTraderPlayerInventory inventory;
    private P2PTraderStock traderStock;

    void P2PTraderMarketOfferEventHandler(P2PTraderStock _traderStock) {
        this.traderStock = _traderStock;
        inventory = new P2PTraderPlayerInventory;
        GetDayZGame().Event_OnRPC.Insert(HandleEvents);
    }

    void ~P2PTraderMarketOfferEventHandler() {
        GetDayZGame().Event_OnRPC.Remove(HandleEvents);
    }

    void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(!IsServerP2PTrader()) {
            return;
        }

        int offerId;
        P2PTraderPlayerMarketOffer playerMarketOffer;
        DayZPlayer player;

        if(rpc_type == P2P_TRADER_EVENT_TAKE_OFFER) {
            Param3<DayZPlayer, int, int> parameterTakeOffer;
            if(ctx.Read(parameterTakeOffer)) {
                player = parameterTakeOffer.param1;
                int playerOfferId = parameterTakeOffer.param2;
                offerId = parameterTakeOffer.param3;

                playerMarketOffer = traderStock.GetPlayerToMarketOfferById(offerId);
                P2PTraderPlayerPlayerOffer playerPlayerOffer = traderStock.GetPlayerOfferById(playerOfferId);

                P2PTakeOfferValidator takeOfferValidator = new P2PTakeOfferValidator(playerMarketOffer, playerPlayerOffer, player.GetIdentity().GetId());

                if(!takeOfferValidator.IsValid()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR, new Param1<string>(takeOfferValidator.GetErrorMessage()), true, player.GetIdentity());
                    return;
                }

                inventory.AddCollection(player, playerPlayerOffer.GetOfferItems());
                traderStock.AcceptPlayerToPlayerOffer(playerMarketOffer, playerPlayerOffer);

                GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE, new Param1<string>(""), true, player.GetIdentity());
            }
        } else if(rpc_type == P2P_TRADER_EVENT_REMOVE_OFFER) {
            Param2<DayZPlayer, int> parameterRemoveOffer;
            if(ctx.Read(parameterRemoveOffer)) {
                player = parameterRemoveOffer.param1;
                offerId = parameterRemoveOffer.param2;
                playerMarketOffer = traderStock.GetPlayerToMarketOfferById(offerId);

                if(playerMarketOffer == null) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE_ERROR, new Param1<string>("#offer_not_exists"), true, player.GetIdentity());
                    return;
                } else if(playerMarketOffer.GetOwnerId() != player.GetIdentity().GetId()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE_ERROR, new Param1<string>("#you_can_only_remove_your_own_order"), true, player.GetIdentity());
                    return;
                }

                inventory.AddCollection(player, playerMarketOffer.GetOfferItems());

                traderStock.RemovePlayerToMarketOffer(playerMarketOffer);

                GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE, new Param1<string>(""), true, player.GetIdentity());
            }
        }
    }
};
