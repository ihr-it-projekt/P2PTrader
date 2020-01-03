class ItemService
{
	private ref P2PTraderPlayerInventory inventory;
	private ref TStringArray configs;
	private ref array<string> itemsFromConfig;
	
	void ItemService() {
		inventory = new P2PTraderPlayerInventory;
		
		configs = new TStringArray;
		configs.Insert( CFG_VEHICLESPATH );
		configs.Insert( CFG_WEAPONSPATH );
		configs.Insert( CFG_MAGAZINESPATH );
		configs.Insert( "CfgNonAIVehicles" );
		
		itemsFromConfig = new array<string>;
		
		foreach (string configName: configs){
			int countChildren = g_Game.ConfigGetChildrenCount(configName);

			for (int i = 0; i < countChildren; ++i){
				string strName;
				GetGame().ConfigGetChildName(configName, i, strName);

				int scope = GetGame().ConfigGetInt( configName + " " + strName + " scope" );

				if (scope == 0 ){
					continue;
				}

				string strNameLower = strName;

				strNameLower.ToLower();

				if (strName != "ItemOptics"){
					itemsFromConfig.Insert(strName);
				}
			}
		}
	}
	
	array<EntityAI> GetPlayerItemList(DayZPlayer player) {
		return inventory.GetPlayerItems(player);
	}
	
	void AddTradeableItemsToWidget(TextListboxWidget widget, string currentType, string search) {		
		widget.ClearItems();
		
		search.ToLower();

		foreach (string itemName: itemsFromConfig){
				string strNameLower = itemName;

				strNameLower.ToLower();

				if ((currentType == "All" || GetGame().IsKindOf(strNameLower, currentType))){
					if (search != "" && !strNameLower.Contains(search)){
						continue;
					}
					widget.AddItem(itemName, NULL, 0);
				}
			}
		}
	}
	
	void MoveItemToPlayer(DayZPlayer player, string itemName) {
		
	}
	
	void MoveItemToTrader(DayZPlayer player, int pos) {
		ItemBase item = inventory.GetPlayerItem(player, pos);
		if (item) {
			
		}
	}
	
	
	
	
}