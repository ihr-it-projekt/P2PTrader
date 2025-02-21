modded class MissionServer {

    private ref P2PTraderConfig p2pTraderConfig;
    private ref P2PTraderStock traderStock;
    private ref P2PTraderAdminEventHandler adminEventHandler;
    private ref P2PTraderOfferCreateEventHandler offerCreateEventHandler;
    private ref P2PTraderMarketOfferEventHandler marketOfferEventHandler;
    private ref P2PTraderPlayerOfferEventHandler playerOfferEventHandler;
    private ref P2PTraderPlayerItemEventHandler playerItemEventHandler;
    private ref Timer exceededTimer;
    private ref P2PStockChecker stockChecker;

    void MissionServer() {
        for(int i = 0; i < 20; i++) {
            Print("[P2PTrader] This mod is deprecated and will not maintained anymore. If you search for an alternative see here: https://youtu.be/YXXO2QezOUU");
            GetGame().AdminLog("[P2PTrader] This mod is deprecated and will not maintained anymore. If you search for an alternative see here: https://youtu.be/YXXO2QezOUU");
        }

        p2pTraderConfig = new P2PTraderConfig();

        P2PTraderKeyCodeMatch keyMap = new P2PTraderKeyCodeMatch;

        traderStock = new P2PTraderStock();

        string fileName = P2PTraderItemsCategoryConfig.ITEM_CATEGORY_PREFIX + "0" + P2PTraderCategory.SETTINGSFILE;
        bool configExists = FileExist(CONFIGS_CATEGORY_FOLDER_P2P + fileName);

        if(!configExists) {
            GetGame().AdminLog("[P2PTrader] NOT SUCCESSFUL LOADED. Please visit https:\/\/dayz-p2ptrader.com/category-editor/add-items and create your category config. Alternative you can copy all files and folders from '##paste_content_to_server_profiles_folder' into your server profiles folder. There are all items in the will came from basic game.");
            Print("[P2PTrader] NOT SUCCESSFUL LOADED. Please visit https:\/\/dayz-p2ptrader.com/category-editor/add-items and create your category config. Alternative you can copy all files and folders from '##paste_content_to_server_profiles_folder' into your server profiles folder. There are all items in the will came from basic game.");
            return;
        }

        adminEventHandler = new P2PTraderAdminEventHandler(traderStock, p2pTraderConfig.traderConfigParams);
        offerCreateEventHandler = new P2PTraderOfferCreateEventHandler(traderStock, p2pTraderConfig.traderConfigParams);
        marketOfferEventHandler = new P2PTraderMarketOfferEventHandler(traderStock);
        playerOfferEventHandler = new P2PTraderPlayerOfferEventHandler(traderStock);
        playerItemEventHandler = new P2PTraderPlayerItemEventHandler(p2pTraderConfig.traderConfigParams, p2pTraderConfig.traderItemsConfig);
        GetDayZGame().Event_OnRPC.Insert(HandleEventsTrader);

        foreach(P2PTraderPosition position: p2pTraderConfig.traderConfigParams.traderPositions) {
            SpawnHouse(position.position, position.orientation, position.gameObjectType);
        }

        if(p2pTraderConfig.traderConfigParams.isEnabledExceededCheck) {
            stockChecker = new P2PStockChecker(traderStock, p2pTraderConfig.traderConfigParams);
            stockChecker.CheckForExpiredItems();
            exceededTimer = new Timer;
            exceededTimer.Run((p2pTraderConfig.traderConfigParams.exceededTimeCheckInterval) * 60, stockChecker, "CheckForExpiredItems", null, true);
            traderStock.Save();
        }


        DebugMessageP2PTrader("loaded");
    }

    void ~MissionServer() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsTrader);
        if(exceededTimer) {
            exceededTimer.Stop();
        }
    }

    void HandleEventsTrader(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(!IsServerP2PTrader()) {
            return;
        }

        if(rpc_type == P2P_TRADER_EVENT_GET_CONFIG) {
            autoptr Param1<PlayerBase> paramGetConfig;
            if(ctx.Read(paramGetConfig)) {
                GetGame().RPCSingleParam(paramGetConfig.param1, P2P_TRADER_EVENT_GET_CONFIG_RESPONSE, new Param1<ref P2PTraderConfig>(p2pTraderConfig), true, sender);
            }
        } else if(rpc_type == P2P_TRADER_EVENT_GET_STOCK) {
            autoptr Param1<PlayerBase> paramGetStock;
            if(ctx.Read(paramGetStock)) {
                GetGame().RPCSingleParam(paramGetStock.param1, P2P_TRADER_EVENT_GET_STOCK_RESPONSE, new Param1<ref array<ref P2PTraderPlayerMarketOffer>>(traderStock.GetStock()), true, sender);
            }
        } else if(rpc_type == P2P_TRADER_EVENT_GET_ALL_BID_OFFERS) {
            autoptr Param1<PlayerBase> paramGetMyBidOffer;
            if(ctx.Read(paramGetMyBidOffer)) {
                GetGame().RPCSingleParam(paramGetMyBidOffer.param1, P2P_TRADER_EVENT_GET_ALL_BID_OFFERS_RESPONSE, new Param1<ref array<ref P2PTraderPlayerPlayerOffer>>(traderStock.GetOffersFromAllPlayer()), true, sender);
            }
        }
    }

    private House SpawnHouse(vector position, vector orientation, string gameObjectName) {
        if("not_spawn" == gameObjectName) {
            return null;
        }
        House house = House.Cast(GetGame().CreateObject(gameObjectName, position));
        if(!house) {
            return house;
        }
        house.SetPosition(position);
        house.SetOrientation(orientation);
        house.SetOrientation(house.GetOrientation()); //Collision fix
        house.Update();
        house.SetAffectPathgraph(true, false);
        if(house.CanAffectPathgraph()) {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, house);
        }

        return house;
    }


};
