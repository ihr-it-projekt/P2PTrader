class P2PTraderConfig
{
    private const static string	SETTINGSFILE = "P2PTraderConfig.json";
	private const static string	CONFIGSFOLDERP2P = "$profile:P2PTrader\\";
	

    void P2PTraderConfig()
    {
  		if (!FileExist(CONFIGSFOLDERP2P + SETTINGSFILE))
		{
			

			Save(SETTINGSFILE);
		} else {
			Load(SETTINGSFILE);
			
			
		}
    }
	
	  

    private void Load(string filename)
    {
        if (IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGSFOLDERP2P + filename)) {
			DebugMessageP2PTrader("load file");
			JsonFileLoader<P2PTraderConfig>.JsonLoadFile(CONFIGSFOLDERP2P + SETTINGSFILE, this);
        }
    }

    private void Save(string filename)
    {
        if (IsServerAndMultiplayerP2PTrader()) {
			if (!FileExist(CONFIGSFOLDERP2P)) {
                MakeDirectory(CONFIGSFOLDERP2P);
                DebugMessageP2PTrader("create folder");
            }
			DebugMessageP2PTrader("save file");
			JsonFileLoader<P2PTraderConfig>.JsonSaveFile(CONFIGSFOLDERP2P + SETTINGSFILE, this);
		}
    }
	
}