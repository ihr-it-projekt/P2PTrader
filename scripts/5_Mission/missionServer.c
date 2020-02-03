modded class MissionServer {
	
	private ref P2PTraderConfig config;
	private ref P2PTraderItemsConfig itemConfig;
	private ref P2PTraderStock traderStock;
	private ref P2PTraderOfferCreateEventHandler offerCreateEventHandler;
	private ref P2PTraderOfferRemoveEventHandler offerRemoveEventHandler;
	private ref P2PTraderPlayerItemEventHandler playerItemEventHandler;
	
	void MissionServer()
	{
		config = new P2PTraderConfig();
		DebugMessageP2PTrader("Has load Items from config: " + config.traderItemsConfig.items.Count().ToString());
		traderStock = new P2PTraderStock();
		offerCreateEventHandler = new P2PTraderOfferCreateEventHandler(traderStock);
		offerRemoveEventHandler = new P2PTraderOfferRemoveEventHandler(traderStock);
		playerItemEventHandler = new P2PTraderPlayerItemEventHandler();
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
		DebugMessageP2PTrader("loaded");
	}
	
	void ~MissionServer() {
		GetDayZGame().Event_OnRPC.Remove(HandleEvents);
	}
	
	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (!IsServerP2PTrader()) {
			return;
		} 
		
		if (rpc_type == P2P_TRADER_EVENT_GET_CONFIG) {
			
			DebugMessageP2PTrader("receive get config");
			autoptr Param1<PlayerBase> paramGetConfig;
			if (ctx.Read(paramGetConfig)){
                GetGame().RPCSingleParam(paramGetConfig.param1, P2P_TRADER_EVENT_GET_CONFIG_RESPONSE, new Param1<ref P2PTraderConfig>(config), true, sender);
			}
		} else if (rpc_type == P2P_TRADER_EVENT_GET_STOCK) {
			DebugMessageP2PTrader("receive get config");
			autoptr Param1<PlayerBase> paramGetStock;
			if (ctx.Read(paramGetStock)){
                GetGame().RPCSingleParam(paramGetStock.param1, P2P_TRADER_EVENT_GET_STOCK_RESPONSE, new Param1<ref array<ref P2PTraderPlayerMarketOffer>>(traderStock.GetStock()), true, sender);
			}
		}
	}


};