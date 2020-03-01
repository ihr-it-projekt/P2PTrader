class P2PTraderConfigParams
{
    private const static string	SETTINGSFILE = "P2PTraderConfigParams.json";
	private const static string	CONFIGSFOLDERP2P = "$profile:P2PTrader\\";

    int maxOffersPerPlayer = 3;
    int maxBidsPerPlayer = 3;
	ref array<ref P2PTraderGamePosition> positions;

	string traderObjectType =  "StreetLamp";

    void P2PTraderConfigParams()
    {
  		if (!FileExist(CONFIGSFOLDERP2P + SETTINGSFILE))
		{
			positions = new array<ref P2PTraderGamePosition>;
			positions.Add(new P2PTraderGamePosition("8349.769531 293.181458 5976.001953", "49.000000 0.000000 0.000000"));
			Save();
		} else {
			Load();
		}
    }
	
    private void Load(){
        if (IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGSFOLDERP2P + SETTINGSFILE)) {
			DebugMessageP2PTrader("load file");
			JsonFileLoader<P2PTraderConfigParams>.JsonLoadFile(CONFIGSFOLDERP2P + SETTINGSFILE, this);
        }
    }

    private void Save(){
        if (IsServerAndMultiplayerP2PTrader()) {
			if (!FileExist(CONFIGSFOLDERP2P)) {
                MakeDirectory(CONFIGSFOLDERP2P);
                DebugMessageP2PTrader("create folder");
            }
			DebugMessageP2PTrader("save file");
			JsonFileLoader<P2PTraderConfigParams>.JsonSaveFile(CONFIGSFOLDERP2P + SETTINGSFILE, this);
		}
    }
	
}