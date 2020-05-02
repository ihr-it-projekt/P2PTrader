modded class MissionServer {
	
	private ref P2PTraderConfig p2pTraderConfig;
	private ref P2PTraderStockWrapper traderStock;
	private ref P2PTraderOfferCreateEventHandler offerCreateEventHandler;
	private ref P2PTraderMarketOfferEventHandler marketOfferEventHandler;
	private ref P2PTraderPlayerOfferEventHandler playerOfferEventHandler;
	private ref P2PTraderPlayerItemEventHandler playerItemEventHandler;
    private ref Timer exceededTimer;
    private ref P2PStockChecker stockChecker;
	
	void MissionServer()
	{
		p2pTraderConfig = new P2PTraderConfig();

		if (p2pTraderConfig.traderItemsConfig.items) {
		    DebugMessageP2PTrader("Has load Items from p2pTraderConfig: " + p2pTraderConfig.traderItemsConfig.items.Count().ToString());
		} else {
		     GetGame().AdminLog("[P2PTrader] ERROR: You have to configure P2PTraderItemsConfig.json. Mod not successful loaded. See: https://steamcommunity.com/sharedfiles/filedetails/discussions/2012299152");
		     return;
		}

		traderStock = new P2PTraderStockWrapper(p2pTraderConfig);
		DebugMessageP2PTrader("Has loaded stock:" + traderStock.GetStock().Count().ToString());
		
		offerCreateEventHandler = new P2PTraderOfferCreateEventHandler(traderStock, p2pTraderConfig.traderConfigParams);
		marketOfferEventHandler = new P2PTraderMarketOfferEventHandler(traderStock);
		playerOfferEventHandler = new P2PTraderPlayerOfferEventHandler(traderStock);
		playerItemEventHandler = new P2PTraderPlayerItemEventHandler(p2pTraderConfig.traderConfigParams, p2pTraderConfig.traderItemsConfig);
		GetDayZGame().Event_OnRPC.Insert(HandleEventsTrader);
		
		foreach(P2PTraderPosition position: p2pTraderConfig.traderConfigParams.traderPositions) {
			SpawnHouse(position.position, position.orientation, position.gameObjectType);
		}

		if (p2pTraderConfig.traderConfigParams.isEnabledExceededCheck) {
			DebugMessageP2PTrader("create timer for exeeded check");
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
		if (exceededTimer) {
            exceededTimer.Stop();
        }
	}
	
	void HandleEventsTrader(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (!IsServerP2PTrader()) {
			return;
		} 
		
		if (rpc_type == P2P_TRADER_EVENT_GET_CONFIG) {
			
			DebugMessageP2PTrader("receive get p2pTraderConfig");
			autoptr Param1<PlayerBase> paramGetConfig;
			if (ctx.Read(paramGetConfig)){
                GetGame().RPCSingleParam(paramGetConfig.param1, P2P_TRADER_EVENT_GET_CONFIG_RESPONSE, new Param1<ref P2PTraderConfig>(p2pTraderConfig), true, sender);
			}
		} else if (rpc_type == P2P_TRADER_EVENT_GET_STOCK) {
			DebugMessageP2PTrader("receive get stock");
			autoptr Param1<PlayerBase> paramGetStock;
			if (ctx.Read(paramGetStock)){
                GetGame().RPCSingleParam(paramGetStock.param1, P2P_TRADER_EVENT_GET_STOCK_RESPONSE, new Param1<ref array<ref P2PTraderPlayerMarketOffer>>(traderStock.GetStock()), true, sender);
			}
		} else if (rpc_type == P2P_TRADER_EVENT_GET_ALL_BID_OFFERS) {
			DebugMessageP2PTrader("receive get stock");
			autoptr Param1<PlayerBase> paramGetMyBidOffer;
			if (ctx.Read(paramGetMyBidOffer)){
                GetGame().RPCSingleParam(paramGetMyBidOffer.param1, P2P_TRADER_EVENT_GET_ALL_BID_OFFERS_RESPONSE, new Param1<ref array<ref P2PTraderPlayerPlayerOffer>>(traderStock.GetOffersFromAllPlayer()), true, sender);
			}
		}
	}
	
	private House SpawnHouse(vector position, vector orientation, string gameObjectName) {
	    if ("not_spawn" == gameObjectName) {
	        return null;
	    }
		position[1] = GetGame().SurfaceY(position[0], position[2]);
        House house = House.Cast(GetGame().CreateObject(gameObjectName, position));
        if (!house) {
            return house;
        }
        house.SetPosition(position);
        house.SetOrientation(orientation);
        house.SetOrientation(house.GetOrientation()); //Collision fix
        house.Update();
        house.SetAffectPathgraph(true, false);
        if(house.CanAffectPathgraph()) {
            GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().UpdatePathgraphRegionByObject, 100, false, house );
        }

        return house;
    }


};