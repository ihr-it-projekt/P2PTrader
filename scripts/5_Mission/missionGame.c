modded class MissionGameplay 
{
	private ref P2PTraderConfig config;
	private ref P2PTraderMenu traderMenu;
	private DayZPlayer player;
	private UAInput localInput;
	
	void MissionGameplay() {
		DebugMessageP2PTrader("init Mission MissionGameplay");
		
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
        Param1<DayZPlayer> paramGetConfig = new Param1<DayZPlayer>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetConfig.param1, P2P_TRADER_EVENT_GET_CONFIG, paramGetConfig, true);
		
		localInput = GetUApi().GetInputByName("UAInputOpenP2PTrader");
	}
	
	void ~MissionGameplay() {
		GetDayZGame().Event_OnRPC.Remove(HandleEvents);
	}
	
	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (rpc_type == P2P_TRADER_EVENT_GET_CONFIG_RESPONSE) {
			DebugMessageP2PTrader("player receive config");
			Param2 <ref P2PTraderConfig, string> configParam;
			if (ctx.Read(configParam)){
				config = configParam.param1;
				string playerId = configParam.param2;
				DebugMessageP2PTrader("player has load config");

			}
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		player = GetGame().GetPlayer();
		
		if(localInput.LocalClick() && player && player.IsAlive()) {
			DebugMessageP2PTrader("try open menu");
			if (GetGame().GetUIManager().GetMenu() == null && !traderMenu && config) {
				DebugMessageP2PTrader("Create and show trader menue");
				traderMenu = new P2PTraderMenu;
				traderMenu.SetConfig(config);
				traderMenu.Init();
				traderMenu.OnShow();
			} else if (traderMenu && !traderMenu.isMenuOpen && config) {
				DebugMessageP2PTrader("show trader menue");
				traderMenu.OnShow();
			}
		}	
	}

	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
		
		if (traderMenu){
			switch (key){
				case KeyCode.KC_ESCAPE:
					DebugMessageP2PTrader("press esc ");
					traderMenu.CloseMenu();
					
					break;
				default:
					break;
			}
		} 

	}
}