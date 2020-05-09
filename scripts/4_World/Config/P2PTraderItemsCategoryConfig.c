class P2PTraderItemsCategoryConfig
{
    private const static string	SETTINGSFILE1 = "P2PTraderItemsCategoryConfig.json";
    private const static string	SETTINGSFILE2 = "P2PTraderItemsCategoryConfigInventory.json";
	private const static string	CONFIGSFOLDERP2P = "$profile:P2PTrader\\";
    private ref map<string, ref TStringArray> items;
    private ref map<string, ref TStringArray> itemsInventory;

    void P2PTraderItemsCategoryConfig() {
        items = loadItem(SETTINGSFILE1);
		itemsInventory = loadItem(SETTINGSFILE2);
    }
	
	map<string, ref TStringArray> GetItems() {
		return items;
	}
	
	map<string, ref TStringArray> GetItemsInventory() {
		return itemsInventory;
	}
	
	private ref map<string, ref TStringArray> loadItem(string filename) {
		ref map<string, ref TStringArray> target;
		if (IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGSFOLDERP2P + filename)) {
            DebugMessageP2PTrader("load file" + filename);
			
            JsonFileLoader<ref map<string, ref TStringArray>>.JsonLoadFile(CONFIGSFOLDERP2P + filename, target);
        } else if(IsServerAndMultiplayerP2PTrader()) {
            target = new map<string, ref TStringArray>;
            P2PTraderItemsConfig itemsConfig = new P2PTraderItemsConfig;
			TStringArray itemsFromConfig = itemsConfig.items;
            foreach(string item: itemsFromConfig) {
				string category = GetCategory(item);
				
				TStringArray subItemCollection = target.Get(category);
				if (!subItemCollection) {
					subItemCollection = new TStringArray;
				}
			
				subItemCollection.Insert(item);
				target.Set(category, subItemCollection);
            }
			
			SaveFile(target, filename);
        }
		
		return target;
	}

    private string GetCategory(string item) {
		string category = "no_category";
        Object object = GetGame().CreateObject(item, "0 0 0", true);
		ItemBase itemObject = ItemBase.Cast(object);
		
        if (!itemObject) {
            category = "no_category";
        } else if (itemObject.IsTransmitter()){
			category = "transmitter";
		} else if (itemObject.IsClothing()){
			category = "clothes";
		} else if (itemObject.IsPeltBase()){
			category = "pelt";
		} else if (itemObject.IsAmmoPile() || itemObject.IsKindOf("Box_Base") || "AmmoBox" == item){
			category = "ammo";
		} else if (itemObject.IsKindOf("Chemlight_ColorBase")){
			category = "lights";
		} else if (itemObject.IsMagazine()){
			category = "mag";
		} else if (itemObject.IsKindOf("BaseBuildingBase")){
			category = "";
		} else if (itemObject.IsKindOf("ItemCompass") || itemObject.IsKindOf("ItemGPS")){
			category = "navigation"; 
		} else if (itemObject.IsKindOf("Grenade_Base") || itemObject.IsWeapon()){
			category = "weapon";
		} else if (itemObject.IsKindOf("WoodenPlank") || itemObject.IsKindOf("Nail") || itemObject.IsKindOf("MetalWire") || itemObject.IsKindOf("Spotlight") || itemObject.IsKindOf("Bark_ColorBase")){
			category = "build_items";
		} else if (itemObject.IsKindOf("PowerGenerator") || itemObject.IsKindOf("CarWheel") || itemObject.IsKindOf("Car") || itemObject.IsKindOf("CarDoor") || itemObject.IsKindOf("CarRadiator") || itemObject.IsKindOf("EngineBelt") || itemObject.IsKindOf("BrakeFluid") || itemObject.IsKindOf("EngineOil") || itemObject.IsKindOf("TireRepairKit")){
			category = "car";
		} else if (itemObject.IsKindOf("StartKitIV") || itemObject.IsKindOf("Container_Base") || itemObject.IsKindOf("Barrel_ColorBase")){
			category = "store_items";
		} else if (itemObject.IsBloodContainer() || itemObject.IsKindOf("Splint") || itemObject.IsKindOf("SalineBag") || itemObject.IsKindOf("SalineBagIV") || itemObject.IsKindOf("InjectionVial") || itemObject.IsKindOf("ClearSyringe") || itemObject.IsKindOf("CigarettePack_ColorBase") || itemObject.IsKindOf("Morphine") || itemObject.IsKindOf("Epinephrine") || itemObject.IsKindOf("DisinfectantAlcohol") || itemObject.IsKindOf("BloodTestKit")){
			category = "medicine";
		} else if (itemObject.IsTransport()){
			category = "transport";
		} else if (itemObject.IsFood() || itemObject.IsKindOf("AntiPestsSpray") || itemObject.IsKindOf("PlantBase") || itemObject.IsKindOf("SeedBase") || itemObject.IsKindOf("Edible_Base") || itemObject.IsKindOf("SodaCan_ColorBase") || itemObject.IsKindOf("SeedPackBase") || itemObject.IsKindOf("Edible_Base")){
			category = "food";
		} else if (itemObject.IsItemTent()){
			category = "tent";
		} else if (itemObject.IsFireplace()){
			category = "fireplace";
		} else if (itemObject.IsKindOf("SuppressorBase") || itemObject.IsKindOf("ButtstockBase") || itemObject.IsKindOf("ItemOptics") || item.Contains("AK") || item.Contains("MP5") || item.Contains("M4")){
			category = "weapon_part";
		} else if (itemObject.IsMeleeWeapon()){
			category = "meleeWeapon";
		} 
		
		GetGame().ObjectDelete(object);
		
		return category;
    }
	
	private bool ObjectIsKindOf(Object object, string cfg_parent_name){
		TStringArray full_path = new TStringArray;
		GetGame().ConfigGetObjectFullPath(object, full_path);
	
		cfg_parent_name.ToLower();
	
		for (int i = 0; i < full_path.Count(); i++) {
			string tmp = full_path.Get(i);
			DebugMessageP2PTrader(tmp + " " + cfg_parent_name);
			tmp.ToLower();
			if (tmp == cfg_parent_name) {
				return true;
			}
		}
	
		return false;
	}

    private void SaveFile(map<string, ref TStringArray> mapping, string fileName ){
        if (IsServerAndMultiplayerP2PTrader()) {
            if (!FileExist(CONFIGSFOLDERP2P)) {
                MakeDirectory(CONFIGSFOLDERP2P);
                DebugMessageP2PTrader("create folder");
            }
            DebugMessageP2PTrader("save file");
            JsonFileLoader<map<string, ref TStringArray>>.JsonSaveFile(CONFIGSFOLDERP2P + fileName, mapping);
        }
    }
}