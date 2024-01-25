class P2PTraderOfferCreateEventHandler {
    private ref P2PTraderPlayerInventory inventory;
    private P2PTraderStock traderStock;
    private P2PTraderConfigParams config;

    void P2PTraderOfferCreateEventHandler(P2PTraderStock traderStock, P2PTraderConfigParams config) {
        this.traderStock = traderStock;
        inventory = new P2PTraderPlayerInventory;
        this.config = config;
        GetDayZGame().Event_OnRPC.Insert(HandleEvents);
    }

    void ~P2PTraderOfferCreateEventHandler() {
        GetDayZGame().Event_OnRPC.Remove(HandleEvents);
    }

    void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(!IsServerP2PTrader()) {
            return;
        }

        if(rpc_type == P2P_TRADER_EVENT_NEW_OFFER) {
            Param5<DayZPlayer, ref array<ref P2PTraderItem>, ref array<ref P2PTraderItem>, string, string> parameterOffer;
            if(ctx.Read(parameterOffer)) {
                DayZPlayer player = parameterOffer.param1;
                if(config.maxMarketOffersPerPlayer == traderStock.GetMarketOffersFromPlayer(player).Count()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_RESPONSE_ERROR, new Param1<string>("#you_reach_max_market_offers_per_player"), true, player.GetIdentity());
                    return;
                }

                ref array<ref P2PTraderItem> offerItems = parameterOffer.param2;
                ref array<ref P2PTraderItem> wantedItems = parameterOffer.param3;
                string offerMessage = parameterOffer.param4;
                string offerType = parameterOffer.param5;

                if(offerType != P2PTraderPlayerMarketOffer.TYPE_AUCTION && offerType != P2PTraderPlayerMarketOffer.TYPE_INSTANT_BUY) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_RESPONSE_ERROR, new Param1<string>("#you_have_to_selecte_one_offer_type"), true, player.GetIdentity());
                    return;
                }

                if(offerType == P2PTraderPlayerMarketOffer.TYPE_INSTANT_BUY && 0 == wantedItems.Count()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_RESPONSE_ERROR, new Param1<string>("#you_have_to_add_one_wanted_item"), true, player.GetIdentity());
                    return;
                }

                array<EntityAI> items = inventory.GetPlayerItems(player);
                P2PTraderPlayerMarketOffer offer = new P2PTraderPlayerMarketOffer(player, offerType, offerMessage);

                while(offerItems != null && 0 < offerItems.Count()) {
                    offerItems = removeItem(offer, items, offerItems);
                    items = inventory.GetPlayerItems(player);
                }

                foreach(P2PTraderItem itemWantToHave: wantedItems) {
                    offer.AddWantedItem(itemWantToHave.GetItem());
                }

                if(offer.IsEmpty()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_RESPONSE_ERROR, new Param1<string>("#you_can_not_make_an_empty_offer"), true, player.GetIdentity());
                    return;
                }

                traderStock.AddPlayerToMarketOffer(offer);

                GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_RESPONSE, new Param1<string>(""), true, player.GetIdentity());
            }
        } else if(rpc_type == P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER) {
            Param4<DayZPlayer, ref array<ref P2PTraderItem>, int, string> parameterPlayerOffer;
            if(ctx.Read(parameterPlayerOffer)) {
                DayZPlayer offerPlayer = parameterPlayerOffer.param1;
                if(config.maxBidsPerPlayer == traderStock.GetCountPlayerOffers(offerPlayer)) {
                    GetGame().RPCSingleParam(offerPlayer, P2P_TRADER_EVENT_NEW_OFFER_RESPONSE_ERROR, new Param1<string>("#you_reach_max_bid_offers_per_player"), true, offerPlayer.GetIdentity());
                    return;
                }

                ref array<ref P2PTraderItem> offerPlayerItems = parameterPlayerOffer.param2;
                int offerId = parameterPlayerOffer.param3;
                string offerPlayerMessage = parameterPlayerOffer.param4;

                array<EntityAI> itemsPlayer = inventory.GetPlayerItems(offerPlayer);

                P2PTraderPlayerMarketOffer playerMarketOffer = traderStock.GetPlayerToMarketOfferById(offerId);

                if(playerMarketOffer == null) {
                    GetGame().RPCSingleParam(offerPlayer, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR, new Param1<string>("#offer_not_exists"), true, offerPlayer.GetIdentity());
                    return;
                } else if(!P2P_TRADER_DEBUG && playerMarketOffer.GetOwnerId() == offerPlayer.GetIdentity().GetId()) {
                    GetGame().RPCSingleParam(offerPlayer, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR, new Param1<string>("#you_can_not_make_yourself_an_offer"), true, offerPlayer.GetIdentity());
                    return;
                }

                P2PTraderPlayerPlayerOffer offerFromPlayer = new P2PTraderPlayerPlayerOffer(offerPlayer.GetIdentity().GetId(), offerPlayer.GetIdentity().GetName(), offerId, offerPlayerMessage);

                bool isAuction = playerMarketOffer.IsOfferType(P2PTraderPlayerMarketOffer.TYPE_AUCTION);

                while(offerPlayerItems != null && 0 < offerPlayerItems.Count()) {
                    offerPlayerItems = removeItemPlayer(offerFromPlayer, itemsPlayer, offerPlayerItems);
                    itemsPlayer = inventory.GetPlayerItems(offerPlayer);
                }


                if(offerFromPlayer.IsEmpty()) {
                    GetGame().RPCSingleParam(player, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR, new Param1<string>("#you_can_not_make_an_empty_offer"), true, player.GetIdentity());
                    return;
                }

                if(isAuction) {
                    traderStock.AddPlayerToPlayerOffer(offerFromPlayer);
                    playerMarketOffer.AddPlayerOffer(offerFromPlayer);

                    GetGame().RPCSingleParam(offerPlayer, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE, new Param1<string>(""), true, offerPlayer.GetIdentity());
                } else {
                    P2PIsAuctionCompleteValidator isAuctionCompleteValidator = new P2PIsAuctionCompleteValidator(playerMarketOffer, offerFromPlayer);
                    if(isAuctionCompleteValidator.IsValid()) {
                        array <P2PTraderStockItem> unUsedItems = isAuctionCompleteValidator.GetUnUsedItems();

                        P2PTraderPlayerPlayerOffer validOfferFromPlayer = new P2PTraderPlayerPlayerOffer(offerPlayer.GetIdentity().GetId(), offerPlayer.GetIdentity().GetName(), offerId, offerPlayerMessage);

                        array <P2PTraderStockItem> usedItems = isAuctionCompleteValidator.GetUsedItems();
                        foreach(P2PTraderStockItem usedItem: usedItems) {
                            validOfferFromPlayer.AddOfferItem(usedItem);
                        }

                        traderStock.AddPlayerToPlayerOffer(validOfferFromPlayer);
                        playerMarketOffer.AddPlayerOffer(validOfferFromPlayer);

                        inventory.AddCollectionNoRef(offerPlayer, unUsedItems);
                        inventory.AddCollection(offerPlayer, playerMarketOffer.GetOfferItems());

                        traderStock.AcceptPlayerToMarketOffer(playerMarketOffer, validOfferFromPlayer);

                        GetGame().RPCSingleParam(offerPlayer, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE, new Param1<string>("#your_trade_was_successfull"), true, offerPlayer.GetIdentity());
                    } else {
                        inventory.AddCollection(offerPlayer, offerFromPlayer.GetOfferItems());
                        GetGame().RPCSingleParam(offerPlayer, P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE_ERROR, new Param1<string>(isAuctionCompleteValidator.GetErrorMessage()), true, offerPlayer.GetIdentity());
                    }
                }
            }
        }
    }

    private array<ref P2PTraderItem> removeItem(P2PTraderPlayerMarketOffer offer, array<EntityAI> items, array<ref P2PTraderItem> offerItems) {
        foreach(EntityAI item: items) {
            ItemBase itemCast = ItemBase.Cast(item);
            foreach(int pos, P2PTraderItem offerItem: offerItems) {
                if(itemCast && offerItem && offerItem.GetItem().IsItem(itemCast)) {
                    offer.AddOfferItem(offerItem.GetItem());
                    inventory.Remove(itemCast);
                    offerItems.Remove(pos);
                    return offerItems;
                }
            }
        }
        return null;
    }
    private array<ref P2PTraderItem> removeItemPlayer(P2PTraderPlayerPlayerOffer offer, array<EntityAI> items, array<ref P2PTraderItem> offerItems) {
        foreach(EntityAI item: items) {
            ItemBase itemCast = ItemBase.Cast(item);
            foreach(int pos, P2PTraderItem offerItem: offerItems) {
                if(itemCast && offerItem && offerItem.GetItem().IsItem(itemCast)) {
                    offer.AddOfferItem(offerItem.GetItem());
                    inventory.Remove(itemCast);
                    offerItems.Remove(pos);
                    return offerItems;
                }
            }
        }

        return null;
    }
};
