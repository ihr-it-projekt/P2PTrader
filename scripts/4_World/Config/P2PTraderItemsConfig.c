class P2PTraderItemsConfig
{
    private const static string	SETTINGSFILE = "P2PTraderItemsConfig.json";
	ref TStringArray items;
	
	void P2PTraderItemsConfig()
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
			JsonFileLoader<P2PTraderItemsConfig>.JsonLoadFile(CONFIGS_FOLDER_P2P + SETTINGSFILE, this);
        }
    }

    private void Save(){
        if (IsServerAndMultiplayerP2PTrader()) {
			if (!FileExist(CONFIGS_FOLDER_P2P)) {
                MakeDirectory(CONFIGS_FOLDER_P2P);
                DebugMessageP2PTrader("create folder");
            }
			DebugMessageP2PTrader("save file");
			JsonFileLoader<P2PTraderItemsConfig>.JsonSaveFile(CONFIGS_FOLDER_P2P + SETTINGSFILE, this);
		}
    }
	
}