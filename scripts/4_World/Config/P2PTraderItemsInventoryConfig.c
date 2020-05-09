class P2PTraderItemsInventoryConfig
{
    private const static string	SETTINGSFILE = "P2PTraderItemsInventoryConfig.json";
	private const static string	CONFIGSFOLDERP2P = "$profile:P2PTrader\\";
	ref TStringArray items;
	

    void P2PTraderItemsInventoryConfig()
    {
  		if (!FileExist(CONFIGSFOLDERP2P + SETTINGSFILE))
		{
			Save();
		} else {
			Load();
			
		}
    }
	
	private void Load(){
        if (IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGSFOLDERP2P + SETTINGSFILE)) {
			DebugMessageP2PTrader("load file");
			JsonFileLoader<P2PTraderItemsInventoryConfig>.JsonLoadFile(CONFIGSFOLDERP2P + SETTINGSFILE, this);
        } else {
            P2PTraderItemsConfig config = new P2PTraderItemsConfig();
            items = config.items;
            Save();
        }
    }

    private void Save(){
        if (IsServerAndMultiplayerP2PTrader()) {
			if (!FileExist(CONFIGSFOLDERP2P)) {
                MakeDirectory(CONFIGSFOLDERP2P);
                DebugMessageP2PTrader("create folder");
            }
			DebugMessageP2PTrader("save file");
			JsonFileLoader<P2PTraderItemsInventoryConfig>.JsonSaveFile(CONFIGSFOLDERP2P + SETTINGSFILE, this);
		}
    }
	
}