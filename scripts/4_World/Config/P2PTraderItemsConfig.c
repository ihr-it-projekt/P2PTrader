class P2PTraderItemsConfig
{
    private const static string	SETTINGSFILE = "P2PTraderItemsConfig.json";
	private const static string	CONFIGSFOLDERP2P = "$profile:P2PTrader\\";
	ref TStringArray items;
	

    void P2PTraderItemsConfig()
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
			JsonFileLoader<P2PTraderItemsConfig>.JsonLoadFile(CONFIGSFOLDERP2P + SETTINGSFILE, this);
        }
    }

    private void Save(){
        if (IsServerAndMultiplayerP2PTrader()) {
			if (!FileExist(CONFIGSFOLDERP2P)) {
                MakeDirectory(CONFIGSFOLDERP2P);
                DebugMessageP2PTrader("create folder");
            }
			DebugMessageP2PTrader("save file");
			JsonFileLoader<P2PTraderItemsConfig>.JsonSaveFile(CONFIGSFOLDERP2P + SETTINGSFILE, this);
		}
    }
	
}