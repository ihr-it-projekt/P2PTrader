class P2PTraderUserListEventService
{
	private DayZPlayer player;
	private int refreshRuns = 0;
	
	void P2PTraderUserListEventService(DayZPlayer player) {
		this.player = player;
	}

	void RefreshPlayerLists() {
		Param1<DayZPlayer> paramGetPlayerItems = new Param1<DayZPlayer>(player);
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_PLAYER_ITEMS, paramGetPlayerItems, true);
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_ALL_BID_OFFERS, paramGetPlayerItems, true);
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_PLAYER_ACCEPTED_INACTIVE_OFFERS, paramGetPlayerItems, true);
		refreshRuns = 3;
	}

	void RefreshStockLists() {
		Param1<DayZPlayer> paramGetPlayerItems = new Param1<DayZPlayer>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_STOCK, paramGetPlayerItems, true);
	}
	
	void DownCountRefresh() {
		refreshRuns = refreshRuns - 1;
	}
	
	bool RefreshFinished() {
		return 0 >= refreshRuns;
	}

	void ResetRefresh() {
		refreshRuns = 0;
	}
}