class P2PTraderAdminEventHandler {
    private ref P2PTraderPlayerInventory inventory;
    private P2PTraderStock traderStock;
    private P2PTraderConfigParams config;

    void P2PTraderAdminEventHandler(P2PTraderStock _traderStock, P2PTraderConfigParams _config) {
        traderStock = _traderStock;
        inventory = new P2PTraderPlayerInventory;
        config = _config;
        GetDayZGame().Event_OnRPC.Insert(HandleEvents);
    }

    void ~P2PTraderAdminEventHandler() {
        GetDayZGame().Event_OnRPC.Remove(HandleEvents);
    }

    void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(!IsServerP2PTrader()) {
            return;
        }

        if(rpc_type == P2P_TRADER_EVENT_ADMIN_DELETE_OFFER) {
            Param2<DayZPlayer, int> parameterOffer;
            if(ctx.Read(parameterOffer)) {
                DayZPlayer player = parameterOffer.param1;
                int offerId = parameterOffer.param2;

                if(config.IsAdmin(player)) {
                    P2PTraderPlayerMarketOffer offer = traderStock.GetPlayerToMarketOfferById(offerId);

                    traderStock.RemovePlayerToMarketOffer(offer);
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_ADMIN_DELETE_OFFER_RESPONSE, new Param1<string>("#deleted"), true, player.GetIdentity());
                }
            }
        }
    }
}
