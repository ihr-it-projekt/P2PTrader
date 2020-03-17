class P2PTraderConfigParams
{
    private const static string	SETTINGSFILE = "P2PTraderConfigParams.json";
	private const static string	CONFIGSFOLDERP2P = "$profile:P2PTrader\\";
	

    int maxMarketOffersPerPlayer = 3;
    int maxBidsPerPlayer = 3;
	float maxDistanceToTrader = -1;
	bool traderCanOpenFromEveryware = false;
	bool playerCanTradeFromEveryware = false;
	int exceededTimeCheckInterval = 1;
	bool isEnabledExceededCheck = false;
	bool spawnExceededToGround = false;
	int offerWillExpireAfterDays = 30;
	ref array<vector> spawnPositionExceededOffers;
	ref array<ref P2PTraderPosition> traderPositions;
	

    void P2PTraderConfigParams()
    {
  		if (!FileExist(CONFIGSFOLDERP2P + SETTINGSFILE))
		{
			traderPositions = new array<ref P2PTraderPosition>;
			traderPositions.Insert(new P2PTraderPosition("6571.0 6.0 2450", "49.000000 0.000000 0.000000", "not_spawn"));
			spawnPositionExceededOffers = new array<vector>;
			spawnPositionExceededOffers.Insert("6573.0 6.0 2450");
			Save();
		} else {
			Load();
			if (0.9 > maxDistanceToTrader) {
				maxDistanceToTrader = 3;
				Save();
			}

			if (exceededTimeCheckInterval == 0) {
			    exceededTimeCheckInterval = 1;
                isEnabledExceededCheck = false;
                spawnExceededToGround = false;
                offerWillExpireAfterDays = 30;
                Save();
			}

			if (!spawnPositionExceededOffers || spawnPositionExceededOffers.Count() == 0) {
				DebugMessageP2PTrader("spawnPositionExceededOffers not exists, will created");
				spawnPositionExceededOffers = new array<vector>;
				foreach(P2PTraderPosition position: traderPositions) {
					position.position[0] = position.position[0] + 2;
					spawnPositionExceededOffers.Insert(position.position);
				}
				Save();
			}
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