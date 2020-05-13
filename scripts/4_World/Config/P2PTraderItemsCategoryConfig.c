class P2PTraderItemsCategoryConfig
{
    private ref array<string> categoryArray;
    private const static string	SETTINGSFILE1 = "P2PTraderItemsCategoryConfig.json";
    private const static string	SETTINGSFILE2 = "P2PTraderItemsCategoryConfigInventory.json";
	private const static string	CONFIGSFOLDERP2P = "$profile:P2PTrader\\";
    private ref array<ref array<string>> items;
    private ref array<ref array<string>> itemsInventory;

    void P2PTraderItemsCategoryConfig() {
		categoryArray = new array<string>;
        categoryArray.Insert("no_category");
        categoryArray.Insert("transmitter");
        categoryArray.Insert("clothes");
        categoryArray.Insert("pelt");
        categoryArray.Insert("ammo");
        categoryArray.Insert("lights");
        categoryArray.Insert("mag");
        categoryArray.Insert("navigation");
        categoryArray.Insert("weapon");
        categoryArray.Insert("build_items");
        categoryArray.Insert("car");
        categoryArray.Insert("store_items");
        categoryArray.Insert("medicine");
        categoryArray.Insert("transport");
        categoryArray.Insert("food");
        categoryArray.Insert("tent");
        categoryArray.Insert("fireplace");
        categoryArray.Insert("weapon_part");
        categoryArray.Insert("meleeWeapon");
		

		loadItem(SETTINGSFILE1);
		loadItemInventory(SETTINGSFILE2);
    }
	
	array<ref TStringArray> GetItems() {
		return items;
	}
	
	array<ref TStringArray> GetItemsInventory() {
		return itemsInventory;
	}
	
	string GetCategoryName(int index) {
		return categoryArray[index];
	}
	
	private void loadItem(string filename) {
		if (false && IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGSFOLDERP2P + filename)) {
            DebugMessageP2PTrader("load file" + filename);
			
            JsonFileLoader<ref array<ref array<string>>>.JsonLoadFile(CONFIGSFOLDERP2P + filename, items);
        } else if(IsServerAndMultiplayerP2PTrader()) {
			items = new array<ref array<string>>;
            P2PTraderItemsConfig itemsConfig = new P2PTraderItemsConfig;
			array<string> itemsFromConfig = itemsConfig.items;
			
			DebugMessageP2PTrader("category array has item count: " + categoryArray.Count());
			
			foreach(string category: categoryArray) {
				DebugMessageP2PTrader("create category " + category);
				items.Insert(new array<string>);
			}
			
			DebugMessageP2PTrader("category items array has item count: " + items.Count());
            foreach(string item: itemsFromConfig) {
				int index = GetCategory(item);
				
				if (index == -1) {
					DebugMessageP2PTrader("Did not find category");
					continue;
				}
					
				array<string> subItemCollection = items.Get(index);
			
				
				subItemCollection.Insert(item);
				items.Set(index, subItemCollection);
            }
			DebugMessageP2PTrader("Has added category items: " + items.Count().ToString());
			SaveFile(items, filename);
        }
	}
	
	private void loadItemInventory(string filename) {
		if (IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGSFOLDERP2P + filename)) {
            DebugMessageP2PTrader("load file" + filename);
			
            JsonFileLoader<ref array<ref array<string>>>.JsonLoadFile(CONFIGSFOLDERP2P + filename, itemsInventory);
        } else if(IsServerAndMultiplayerP2PTrader()) {
			itemsInventory = new array<ref array<string>>;
            P2PTraderItemsConfig itemsConfig = new P2PTraderItemsConfig;
			array<string> itemsFromConfig = itemsConfig.items;
			
			foreach(string category: categoryArray) {
				DebugMessageP2PTrader("create category " + category);
				itemsInventory.Insert(new array<string>);
			}
			
            foreach(string item: itemsFromConfig) {
				int index = GetCategory(item);
				
				if (index == -1) {
					DebugMessageP2PTrader("Did not find category");
					continue;
				}
					
				array<string> subItemCollection = itemsInventory.Get(index);
			
				subItemCollection.Insert(item);
				itemsInventory.Set(index, subItemCollection);
            }
			DebugMessageP2PTrader("Has added category items: " + itemsInventory.Count().ToString());
			SaveFile(itemsInventory, filename);
        }
	}

    private int GetCategory(string item) {
		int category = 0;
        Object object = GetGame().CreateObject(item, "0 0 0", true);
		ItemBase itemObject = ItemBase.Cast(object);
		
        if (!itemObject) {
            category = 0;
        } else if (itemObject.IsTransmitter()){
			category = 1;
		} else if (itemObject.IsClothing()){
			category = 2;
		} else if (itemObject.IsPeltBase()){
			category = 3;
		} else if (itemObject.IsAmmoPile() || itemObject.IsKindOf("Box_Base") || "AmmoBox" == item){
			category = 4;
		} else if (itemObject.IsKindOf("Chemlight_ColorBase")){
			category = 5;
		} else if (itemObject.IsMagazine()){
			category = 6;
		} else if (itemObject.IsKindOf("BaseBuildingBase")){
			category = -1;
		} else if (itemObject.IsKindOf("ItemCompass") || itemObject.IsKindOf("ItemGPS")){
			category = 7;
		} else if (itemObject.IsKindOf("Grenade_Base") || itemObject.IsWeapon()){
			category = 8;
		} else if (itemObject.IsKindOf("WoodenPlank") || itemObject.IsKindOf("Nail") || itemObject.IsKindOf("MetalWire") || itemObject.IsKindOf("Spotlight") || itemObject.IsKindOf("Bark_ColorBase")){
			category = 9;
		} else if (itemObject.IsKindOf("PowerGenerator") || itemObject.IsKindOf("CarWheel") || itemObject.IsKindOf("Car") || itemObject.IsKindOf("CarDoor") || itemObject.IsKindOf("CarRadiator") || itemObject.IsKindOf("EngineBelt") || itemObject.IsKindOf("BrakeFluid") || itemObject.IsKindOf("EngineOil") || itemObject.IsKindOf("TireRepairKit")){
			category = 10;
		} else if (itemObject.IsKindOf("StartKitIV") || itemObject.IsKindOf("Container_Base") || itemObject.IsKindOf("Barrel_ColorBase")){
			category = 11;
		} else if (itemObject.IsBloodContainer() || itemObject.IsKindOf("Splint") || itemObject.IsKindOf("SalineBag") || itemObject.IsKindOf("SalineBagIV") || itemObject.IsKindOf("InjectionVial") || itemObject.IsKindOf("ClearSyringe") || itemObject.IsKindOf("CigarettePack_ColorBase") || itemObject.IsKindOf("Morphine") || itemObject.IsKindOf("Epinephrine") || itemObject.IsKindOf("DisinfectantAlcohol") || itemObject.IsKindOf("BloodTestKit")){
			category = 12;
		} else if (itemObject.IsTransport()){
			category = 13;
		} else if (itemObject.IsFood() || itemObject.IsKindOf("AntiPestsSpray") || itemObject.IsKindOf("PlantBase") || itemObject.IsKindOf("SeedBase") || itemObject.IsKindOf("Edible_Base") || itemObject.IsKindOf("SodaCan_ColorBase") || itemObject.IsKindOf("SeedPackBase") || itemObject.IsKindOf("Edible_Base")){
			category = 14;
		} else if (itemObject.IsItemTent()){
			category = 15;
		} else if (itemObject.IsFireplace()){
			category = 16;
		} else if (itemObject.IsKindOf("SuppressorBase") || itemObject.IsKindOf("ButtstockBase") || itemObject.IsKindOf("ItemOptics") || item.Contains("AK") || item.Contains("MP5") || item.Contains("M4")){
			category = 17;
		} else if (itemObject.IsMeleeWeapon()){
			category = 18;
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

    private void SaveFile(array<ref TStringArray> mapping, string fileName ){
        if (IsServerAndMultiplayerP2PTrader()) {
            if (!FileExist(CONFIGSFOLDERP2P)) {
                MakeDirectory(CONFIGSFOLDERP2P);
                DebugMessageP2PTrader("create folder");
            }
            DebugMessageP2PTrader("save file: " + fileName);
            JsonFileLoader<array<ref TStringArray>>.JsonSaveFile(CONFIGSFOLDERP2P + fileName, mapping);
        }
    }
}