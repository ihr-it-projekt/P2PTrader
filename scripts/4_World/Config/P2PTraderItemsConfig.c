class P2PTraderItemsConfig
{
    private const static string	SETTINGSFILE = "P2PTraderItemsConfig.json";
	private const static string	CONFIGSFOLDERP2P = "$profile:P2PTrader\\";
	ref TStringArray items;
	

    void P2PTraderItemsConfig()
    {
  		if (!FileExist(CONFIGSFOLDERP2P + SETTINGSFILE))
		{
			TStringArray configs = new TStringArray;
			items = new TStringArray;
			configs.Insert( CFG_VEHICLESPATH );
			configs.Insert( CFG_WEAPONSPATH );
			configs.Insert( CFG_MAGAZINESPATH );
			configs.Insert( "CfgNonAIVehicles" );
			configs.Insert( "CfgAmmo" );
			
			foreach (string configName: configs){
				int countChildren = g_Game.ConfigGetChildrenCount(configName);
	
				for (int i = 0; i < countChildren; ++i){
					string strName;
					GetGame().ConfigGetChildName(configName, i, strName);
	
					if (!Contains(strName)){
						DebugMessageP2PTrader("Add tradeable item type " + strName);
						items.Insert(strName);
					}
				}
			}
			Save(SETTINGSFILE);
		} else {
			Load(SETTINGSFILE);
			
		}
    }
	
	private bool Contains(string name) {
		TStringArray exactExclude = new TStringArray;
		exactExclude.Insert("All");
		exactExclude.Insert("Transport");
		exactExclude.Insert("Car");
		exactExclude.Insert("Air");
		exactExclude.Insert("Man");
		exactExclude.Insert("Static");
		exactExclude.Insert("Fortress");
		exactExclude.Insert("Thing");
		exactExclude.Insert("ItemOptics");
		exactExclude.Insert("Refridgerator");
		exactExclude.Insert("SeedBase");
		exactExclude.Insert("DE");
		exactExclude.Insert("Plant");
		exactExclude.Insert("StreetLamp");
		exactExclude.Insert("EditCursor");
		exactExclude.Insert("ObjView");
		exactExclude.Insert("Temp");
		exactExclude.Insert("Bird");
		exactExclude.Insert("Insect");
		exactExclude.Insert("ObjVSeaGulliew");
		exactExclude.Insert("StaticCamera");
		exactExclude.Insert("FreeDebugCamera");
		exactExclude.Insert("DefaultAmmo");
		exactExclude.Insert("BulletCore");
		exactExclude.Insert("ShotgunCore");
		exactExclude.Insert("EnviroDmg");
		exactExclude.Insert("FenceKitPlacing");
		exactExclude.Insert("BaseRadio");
		exactExclude.Insert("Church");
		
		TStringArray configs = new TStringArray;
		configs.Insert("Crater");
		configs.Insert("ZmbF_");
		configs.Insert("ZmbM_");
		configs.Insert("Proxy");
		configs.Insert("Proxies");
		configs.Insert("Land_");
		configs.Insert("Book");
		configs.Insert("TestObject");
		configs.Insert("Fx");
		configs.Insert("FX");
		configs.Insert("House");
		configs.Insert("Ruins");
		configs.Insert("Building");
		configs.Insert("FlagCarrierCore");
		configs.Insert("ThingEffect");
		configs.Insert("ExplosionTest");
		configs.Insert("Ground");
		configs.Insert("Strategic");
		configs.Insert("Bear_");
		configs.Insert("CigarettePack_");
		configs.Insert("Wreck_");
		configs.Insert("_Ruined");
		configs.Insert("Animal");
		configs.Insert("SurvivorM_");
		configs.Insert("SurvivorF_");
		configs.Insert("Hands");
		configs.Insert("Head");
		configs.Insert("Legs");
		configs.Insert("Feet");
		configs.Insert("Torso");
		configs.Insert("LightAI");
		configs.Insert("AllVehicles");
		configs.Insert("Helicopter");
		configs.Insert("BushSoft");
		configs.Insert("BushHard");
		configs.Insert("TreeSoft");
		configs.Insert("TreeHard");
		configs.Insert("Static_");
		configs.Insert("access");
		configs.Insert("Dummy");
		configs.Insert("Melee");
		configs.Insert("FallDamage");
		configs.Insert("FireDamage");
		configs.Insert("Hit");
		configs.Insert("_Base");
		configs.Insert("Trash");
		configs.Insert("ClutterCutter");
		configs.Insert("Explosion");
		
		foreach(string itemExact: exactExclude) {
			if (name == itemExact) {
				return true;
			}
		}
		
		foreach(string itemPrefix: configs) {
			if (name.Contains(itemPrefix)) {
				return true;
			}
		}
		
		return false;
	}
	
    private void Load(string filename){
        if (IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGSFOLDERP2P + filename)) {
			DebugMessageP2PTrader("load file");
			JsonFileLoader<P2PTraderItemsConfig>.JsonLoadFile(CONFIGSFOLDERP2P + SETTINGSFILE, this);
        }
    }

    private void Save(string filename){
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