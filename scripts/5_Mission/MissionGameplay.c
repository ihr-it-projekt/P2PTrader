modded class MissionGameplay 
{
	private ref P2PTraderConfig p2pTraderConfig;
	private ref P2PTraderMenu traderMenu;
	private ref P2PTraderHint traderHintMenu;
	private DayZPlayer player;
	private UAInput localInput;
	private P2PTraderConfigParams traderConfigParams;	
	private string keyName = "";
	
	void MissionGameplay() {
		DebugMessageP2PTrader("init Mission MissionGameplay");
		
		GetDayZGame().Event_OnRPC.Insert(HandleEventsTrader);
        Param1<DayZPlayer> paramGetConfig = new Param1<DayZPlayer>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetConfig.param1, P2P_TRADER_EVENT_GET_CONFIG, paramGetConfig, true);
		
		localInput = GetUApi().GetInputByName("UAInputOpenP2PTrader");
	}
	
	void ~MissionGameplay() {
		GetDayZGame().Event_OnRPC.Remove(HandleEventsTrader);
		DebugMessageP2PTrader("destroy MissionGameplay");
	}
	
	void HandleEventsTrader(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (rpc_type == P2P_TRADER_EVENT_GET_CONFIG_RESPONSE) {
			DebugMessageP2PTrader("player receive p2pTraderConfig");
			Param1 <ref P2PTraderConfig> configParam;
			if (ctx.Read(configParam)){
				p2pTraderConfig = configParam.param1;
				traderConfigParams = p2pTraderConfig.traderConfigParams;
				if (traderConfigParams && traderConfigParams.useServerKeyBind && traderConfigParams.defaultKey) {
					keyName = traderConfigParams.possibleKeyBindingsMap.Get(traderConfigParams.defaultKey);
					GetGame().AdminLog("[P2PTrader] Use serverside keybind: " + keyName);
					
					if (keyName) {
						localInput.ClearDeviceBind(EUAINPUT_DEVICE_KEYBOARDMOUSE);
						localInput.BindCombo("k" + keyName);
					}
				}
				
				DebugMessageP2PTrader("player has load p2pTraderConfig");
			}
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		player = GetGame().GetPlayer();
		bool isInNear = isInNearOfTrader();
		if(localInput.LocalClick() && player && player.IsAlive()) {
			OpenTrader(isInNear);
		}
		if (traderConfigParams && isInNear && !traderHintMenu){
			traderHintMenu = new P2PTraderHint;
            traderHintMenu.Init();
            traderHintMenu.SetMessage(keyName);
			traderHintMenu.OnShow();
			
		} else if (isInNear && traderHintMenu) {
            traderHintMenu.OnShow();
		} else if(!isInNear && traderHintMenu) {
            traderHintMenu.OnHide();
		}
	}
	
	private void OpenTrader(bool isInNear) {
		if (player && player.IsAlive() && traderConfigParams && traderConfigParams.traderCanOpenFromEveryware || isInNear) {
			DebugMessageP2PTrader("try open menu");
			bool canTrade = p2pTraderConfig.traderConfigParams.playerCanTradeFromEveryware || isInNear;
			
			if (!traderMenu || !traderMenu.IsInitialized()) {
				DebugMessageP2PTrader("Init trader menu");
				traderMenu = new P2PTraderMenu();
				traderMenu.SetConfig(p2pTraderConfig);
				traderMenu.Init();
			} 
			
			if (traderMenu && !traderMenu.layoutRoot.IsVisible()) {
				DebugMessageP2PTrader("show trader menue");
				traderMenu.SetCanTrade(canTrade);
				traderMenu.OnShow();
			}
		}
	}

	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
		
		if (traderMenu && traderMenu.layoutRoot.IsVisible() && key == KeyCode.KC_ESCAPE){
		    DebugMessageP2PTrader("press esc");
			traderMenu.CloseMenu();
		}
	}
	
	private bool isInNearOfTrader() {
		if (!player) {
			return false;
		}
		vector playerPosition = player.GetPosition();
		if (!playerPosition) {
			return false;
		}
		foreach(P2PTraderPosition position: traderConfigParams.traderPositions) {
			if (vector.Distance(position.position, playerPosition) <= traderConfigParams.maxDistanceToTrader){
				return true;
			}
		}	
		return false;
	}
}