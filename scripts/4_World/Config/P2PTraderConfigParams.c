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
	ref array<string> adminIds;
	bool enableOrigenItemsNameInView = false;
	string configVersion = "7";
	

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
			adminIds = new array<string>;
			adminIds.Insert("Enter your GUID");
			Save();
		} else {
			Load();
			if (configVersion.ToInt() < 7) {
				configVersion = "7";
				enableOrigenItemsNameInView = false;
				Save();
			}
		}
		
		if (enabledOfferTypes.Count() == 0) {
			P2PLog("enabledOfferTypes not configured. Use default values. See Readme file in mod folder for more information.");
			enabledOfferTypes.Insert("instant_buy");
			enabledOfferTypes.Insert("auction");
		}
		
    }
	
	bool IsAdmin(DayZPlayer player) {
		string playerId = player.GetIdentity().GetId();
		
		 return -1 != adminIds.Find(playerId);
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