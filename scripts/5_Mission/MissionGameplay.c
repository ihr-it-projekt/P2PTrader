modded class MissionGameplay 
{
	private ref P2PTraderConfig p2pTraderConfig;
	private ref P2PTraderMenu traderMenu;
	private ref P2PTraderHint traderHintMenu;
	private DayZPlayer p2pPlayer;
	private UAInput localInput;
	private string keyName = "";
	private ref P2PTraderKeyCodeMatch keyMap;
	
	void MissionGameplay() {
		DebugMessageP2PTrader("init Mission MissionGameplay");
		
		GetDayZGame().Event_OnRPC.Insert(HandleEventsTrader);
        Param1<DayZPlayer> paramGetConfig = new Param1<DayZPlayer>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetConfig.param1, P2P_TRADER_EVENT_GET_CONFIG, paramGetConfig, true);
		
		localInput = GetUApi().GetInputByName("UAInputOpenP2PTrader");
		keyMap = new P2PTraderKeyCodeMatch;
	}
	
	void ~MissionGameplay() {
		GetDayZGame().Event_OnRPC.Remove(HandleEventsTrader);
	}
	
	void HandleEventsTrader(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (rpc_type == P2P_TRADER_EVENT_GET_CONFIG_RESPONSE) {
			Param1 <ref P2PTraderConfig> configParam;
			if (ctx.Read(configParam)){
				p2pTraderConfig = configParam.param1;
				if (p2pTraderConfig.traderConfigParams && p2pTraderConfig.traderConfigParams.useServerKeyBind && keyMap && p2pTraderConfig.traderConfigParams.defaultKey) {
					keyName = keyMap.keyCodes.Get(p2pTraderConfig.traderConfigParams.defaultKey);
					GetGame().AdminLog("[P2PTrader] Use serverside keybind: " + keyName);
					
					if (keyName) {
						localInput.ClearDeviceBind(EUAINPUT_DEVICE_KEYBOARDMOUSE);
						localInput.BindCombo("k" + keyName);
					}
				}
			}
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		p2pPlayer = PlayerBase.Cast(GetGame().GetPlayer());
		bool isInNear = isInNearOfTrader();
		if(localInput.LocalClick() && p2pPlayer && p2pPlayer.IsAlive()) {
			OpenTrader(isInNear);
		}
		if (p2pTraderConfig && p2pTraderConfig.traderConfigParams && isInNear && !traderHintMenu){
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
		if (p2pPlayer && p2pPlayer.IsAlive() && p2pTraderConfig.traderConfigParams && p2pTraderConfig.traderConfigParams.traderCanOpenFromEveryware || isInNear) {
			DebugMessageP2PTrader("try open menu");
			bool canTrade = p2pTraderConfig.traderConfigParams.playerCanTradeFromEveryware || isInNear;
			
			if (!traderMenu || !traderMenu.IsInitialized()) {
				traderMenu = new P2PTraderMenu();
				traderMenu.SetConfig(p2pTraderConfig);
				traderMenu.Init();
			} 
			
			if (traderMenu && !traderMenu.layoutRoot.IsVisible()) {
				traderMenu.SetCanTrade(canTrade);
				traderMenu.OnShow();
			}
		}
	}

	override void OnKeyRelease(int key)
	{
		if(!traderMenu || !traderMenu.layoutRoot.IsVisible()) {
			super.OnKeyRelease(key);
		}
		
		if (traderMenu && traderMenu.layoutRoot.IsVisible() && key == KeyCode.KC_ESCAPE){
			traderMenu.CloseMenu();
		}
	}
	
	private bool isInNearOfTrader() {
		if (!p2pPlayer) {
			return false;
		}
		vector playerPosition = p2pPlayer.GetPosition();
		if (!playerPosition) {
			return false;
		}
		foreach(P2PTraderPosition position: p2pTraderConfig.traderConfigParams.traderPositions) {
			if (vector.Distance(position.position, playerPosition) <= p2pTraderConfig.traderConfigParams.maxDistanceToTrader){
				return true;
			}
		}	
		return false;
	}
}
