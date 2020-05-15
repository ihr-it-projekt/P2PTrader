class P2PTraderItemsInventoryConfig
{
    private const static string	SETTINGSFILE = "P2PTraderItemsInventoryConfig.json";
	ref TStringArray items;

    void P2PTraderItemsInventoryConfig()
    {
  		if (!FileExist(CONFIGS_FOLDER_P2P + SETTINGSFILE))
		{
			Save();
		} else {
			Load();
			
		}
    }
	
	private void Load(){
        if (IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGS_FOLDER_P2P + SETTINGSFILE)) {
			DebugMessageP2PTrader("load file");
			JsonFileLoader<P2PTraderItemsInventoryConfig>.JsonLoadFile(CONFIGS_FOLDER_P2P + SETTINGSFILE, this);
        } else {
            P2PTraderItemsConfig config = new P2PTraderItemsConfig();
            items = config.items;
            Save();
        }
    }

    private void Save(){
        if (IsServerAndMultiplayerP2PTrader()) {
			if (!FileExist(CONFIGS_FOLDER_P2P)) {
                MakeDirectory(CONFIGS_FOLDER_P2P);
                DebugMessageP2PTrader("create folder");
            }
			DebugMessageP2PTrader("save file");
			JsonFileLoader<P2PTraderItemsInventoryConfig>.JsonSaveFile(CONFIGS_FOLDER_P2P + SETTINGSFILE, this);
		}
    }
	
}