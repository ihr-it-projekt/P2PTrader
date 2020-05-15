class P2PTraderConfigParams
{
    private const static string	SETTINGSFILE = "P2PTraderConfigParams.json";

    int maxMarketOffersPerPlayer = 3;
    int maxBidsPerPlayer = 3;
	float maxDistanceToTrader = 3;
	bool traderCanOpenFromEveryware = false;
	bool playerCanTradeFromEveryware = false;
	int exceededTimeCheckInterval = 1;
	bool isEnabledExceededCheck = false;
	bool spawnExceededToGround = false;
	int offerWillExpireAfterDays = 30;
	ref array<vector> spawnPositionExceededOffers;
	ref array<ref P2PTraderPosition> traderPositions;
	bool useItemsConfigForPlayerInventory = false;
	int defaultKey = KeyCode.KC_B;
	bool useServerKeyBind = false;
	ref TStringArray enabledOfferTypes;
	string configVersion = "5";
	

    void P2PTraderConfigParams()
    {
  		if (!FileExist(CONFIGS_FOLDER_P2P + SETTINGSFILE))
		{
			traderPositions = new array<ref P2PTraderPosition>;
			traderPositions.Insert(new P2PTraderPosition("6571.0 6.0 2450", "49.000000 0.000000 0.000000", "not_spawn"));
			spawnPositionExceededOffers = new array<vector>;
			spawnPositionExceededOffers.Insert("6573.0 6.0 2450");
			enabledOfferTypes = new TStringArray;
			enabledOfferTypes.Insert("instant_buy");
			enabledOfferTypes.Insert("auction");
			Save();
		} else {
			Load();
			if (configVersion.ToInt() < 5) {
				
				configVersion = "5";
				Save();
			}
		}
		
    }
	
    private void Load(){
        if (IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGS_FOLDER_P2P + SETTINGSFILE)) {
			DebugMessageP2PTrader("load file" + SETTINGSFILE);
			JsonFileLoader<P2PTraderConfigParams>.JsonLoadFile(CONFIGS_FOLDER_P2P + SETTINGSFILE, this);
        }
    }

    private void Save(){
        if (IsServerAndMultiplayerP2PTrader()) {
			if (!FileExist(CONFIGS_FOLDER_P2P)) {
                MakeDirectory(CONFIGS_FOLDER_P2P);
                DebugMessageP2PTrader("create folder");
            }
			DebugMessageP2PTrader("save file");
			JsonFileLoader<P2PTraderConfigParams>.JsonSaveFile(CONFIGS_FOLDER_P2P + SETTINGSFILE, this);
		}
    }
	
}