modded class MissionServer {
	
	private ref P2PTraderConfig config;
	private ref P2PTraderItemsConfig itemConfig;
	private ref P2PTraderStock traderStock;
	private ref P2PTraderOfferEventHandler offerEventHandler;
	private ref P2PTraderPlayerItemEventHandler playerItemEventHandler;
	
	void MissionServer()
	{
		config = new P2PTraderConfig();
		DebugMessageP2PTrader("Has load Items from config: " + config.traderItemsConfig.items.Count().ToString());
		traderStock = new P2PTraderStock();
		offerEventHandler = new P2PTraderOfferEventHandler(traderStock);
		playerItemEventHandler = new P2PTraderPlayerItemEventHandler();
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
		DebugMessageP2PTrader("loaded");
	}
	
	void ~MissionServer() {
		GetDayZGame().Event_OnRPC.Remove(HandleEvents);
	}
	
	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (rpc_type == P2P_TRADER_EVENT_GET_CONFIG) {
			DebugMessageP2PTrader("receive get config");
			autoptr Param1<PlayerBase> paramGetConfig;
			if (ctx.Read(paramGetConfig)){
                GetGame().RPCSingleParam(paramGetConfig.param1, P2P_TRADER_EVENT_GET_CONFIG_RESPONSE, new Param1<ref P2PTraderConfig>(config), true, sender);
			}
		}
	}


};