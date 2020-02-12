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
				offerId = parameterTakeOffer.param2;
				int playerOfferId = parameterTakeOffer.param3;

                playerMarketOffer = traderStock.GetPlayerToMarketOfferById(offerId);
                P2PTraderPlayerPlayerOffer playerPlayerOffer = traderStock.GetPlayerOfferById(playerOfferId);

                if (playerMarketOffer == null) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR, new Param1<string>("#offer_not_exists"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR to player: no offer found");
                    return;
                } else if (playerPlayerOffer == null) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR, new Param1<string>("#player_offer_not_exists"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR to player: no offer found");
                    return;
                } else if (playerMarketOffer.GetOwnerId() != player.GetIdentity().GetPlainId()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR, new Param1<string>("#you_can_only_use_your_own_order"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE_ERROR to player: is not owner of market offer");
                    return;
                } else if (!P2P_TRADER_DEBUG && playerPlayerOffer.GetOwnerId() != player.GetIdentity().GetPlainId()) {
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
                } else if (playerMarketOffer.GetOwnerId() != player.GetIdentity().GetPlainId()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE_ERROR, new Param1<string>("#you_can_only_remove_your_own_order"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE_ERROR to player: is not owner of market offer");
                    return;
                }

				inventory.AddCollection(player, playerMarketOffer.GetOfferItems());
				
				traderStock.RemovePlayerToMarketOffer(playerMarketOffer);
				
				GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE, new Param1<bool>(true), true, player.GetIdentity());
                DebugMessageP2PTrader("send P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE to player");
            }
        } else if (rpc_type == P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER) {
			DebugMessageP2PTrader("receive P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER");
            Param4<DayZPlayer, ref array<ref P2PTraderItem>, int, string> parameterOffer;
            if (ctx.Read(parameterOffer)) {
                player = parameterOffer.param1;
				ref array<ref P2PTraderItem> offerPlayerItems = parameterOffer.param2;
				offerId = parameterOffer.param3;
				string offerPlayerMessage = parameterOffer.param4;
                DebugMessageP2PTrader("Check Player has items");

				array<EntityAI> itemsPlayer = inventory.GetPlayerItems(player);

                playerMarketOffer = traderStock.GetPlayerToMarketOfferById(offerId);

				if (playerMarketOffer == null) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR, new Param1<string>("#offer_not_exists"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR to player: no offer found");
                    return;
				} else if (!P2P_TRADER_DEBUG && playerMarketOffer.GetOwnerId() == player.GetIdentity().GetPlainId()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR, new Param1<string>("#you_can_not_make_yourself_an_offer"), true, player.GetIdentity());
                    DebugMessageP2PTrader("send P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR to player: owner is same then ");
                    return;
				}

                P2PTraderPlayerPlayerOffer offerFromPlayer = new P2PTraderPlayerPlayerOffer(player.GetIdentity().GetPlainId(), player.GetIdentity().GetName(), offerId, offerPlayerMessage);

				DebugMessageP2PTrader("have offer items" + offerPlayerItems.Count().ToString());

				foreach(EntityAI item: itemsPlayer) {
					ItemBase itemPlayerCast = ItemBase.Cast(item);
					foreach(P2PTraderItem offerItem: offerPlayerItems) {
						if (itemPlayerCast && offerItem && offerItem.item && offerItem.item.GetHealth() == itemPlayerCast.GetHealth() && offerItem.item.GetType() == itemPlayerCast.GetType() && offerItem.item.GetQuantity() == itemPlayerCast.GetQuantity()) {
                            offerFromPlayer.AddOfferItem(offerItem.item);
							inventory.Remove(itemPlayerCast, player);
						}
					}
				}

				DebugMessageP2PTrader("Create offer for player in stock");
				traderStock.AddPlayerToPlayerOffer(offerFromPlayer);
                playerMarketOffer.AddPlayerOffer(offerFromPlayer);

                GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE, new Param1<bool>(true), true, player.GetIdentity());
                DebugMessageP2PTrader("send P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE to player");
            }
        }
    }
};