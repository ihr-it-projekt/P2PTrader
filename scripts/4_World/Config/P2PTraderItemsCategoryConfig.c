class P2PTraderItemsCategoryConfig
{
    private const static string	ITEM_CATEGORY_PREFIX = "offer";
    private ref P2PTraderCategoryCollection items;

    void P2PTraderItemsCategoryConfig() {
		loadItem(ITEM_CATEGORY_PREFIX);
    }
	
	P2PTraderCategoryCollection GetItems() {
		return items;
	}
	
	
	string GetCategoryItemName(int index) {
		P2PTraderCategory category = items.GetCategories().Get(index);
		if(category) {
		    return category.GetName();
		}

		return "";
	}
	
	private void loadItem(string fileNameSuffix) {
        string fileName = fileNameSuffix + "0" + P2PTraderCategory.SETTINGSFILE;
		bool configExists = !FileExist(CONFIGS_CATEGORY_FOLDER_P2P + fileName);
        items = new P2PTraderCategoryCollection(fileNameSuffix);
		if (IsServerAndMultiplayerP2PTrader() && configExists) {
			P2PTraderItemsConfig itemsConfig = new P2PTraderItemsConfig;
			array<string> itemsFromConfig = itemsConfig.items;
			DebugMessageP2PTrader("category array has item count: " + items.GetCategories().Count());
			P2PTraderConfiguredCategory configuredCategory = new P2PTraderConfiguredCategory;
            foreach(string item: itemsFromConfig) {
				string name = GetCategory(item);
				
                if (name == "") {
                    DebugMessageP2PTrader("Did not find category");
                    continue;
                }
                
				int index = configuredCategory.categoryNames.Find(name);

				if (index == -1) {
					index = 0;
				}
					
				items.AddItemToCategory(item, index);
            }
        }
	}
	
    private string GetCategory(string item) {
		string category = "#no_category";
        Object object = GetGame().CreateObject(item, "0 0 0", true);
		ItemBase itemObject = ItemBase.Cast(object);
		
        if (!itemObject) {
            category = "#no_category";
        } else if (itemObject.IsTransmitter()){
			category = "#transmitter";
		} else if (itemObject.IsClothing()){
			category = "#clothes";
		} else if (itemObject.IsPeltBase()){
			category = "#pelt";
		} else if (itemObject.IsAmmoPile() || itemObject.IsKindOf("Box_Base") || "AmmoBox" == item){
			category = "#ammo";
		} else if (itemObject.IsKindOf("Chemlight_ColorBase")){
			category = "#lights";
		} else if (itemObject.IsMagazine()){
			category = "#mag";
		} else if (itemObject.IsKindOf("BaseBuildingBase")){
			category = "";
		} else if (itemObject.IsKindOf("ItemCompass") || itemObject.IsKindOf("ItemGPS")){
			category = "#navigation";
		} else if (itemObject.IsKindOf("Grenade_Base") || itemObject.IsWeapon()){
			category = "#weapon";
		} else if (itemObject.IsKindOf("WoodenPlank") || itemObject.IsKindOf("Nail") || itemObject.IsKindOf("MetalWire") || itemObject.IsKindOf("Spotlight") || itemObject.IsKindOf("Bark_ColorBase")){
			category = "#build_items";
		} else if (itemObject.IsKindOf("PowerGenerator") || itemObject.IsKindOf("CarWheel") || itemObject.IsKindOf("Car") || itemObject.IsKindOf("CarDoor") || itemObject.IsKindOf("CarRadiator") || itemObject.IsKindOf("EngineBelt") || itemObject.IsKindOf("BrakeFluid") || itemObject.IsKindOf("EngineOil") || itemObject.IsKindOf("TireRepairKit")){
			category = "#car";
		} else if (itemObject.IsKindOf("StartKitIV") || itemObject.IsKindOf("Container_Base") || itemObject.IsKindOf("Barrel_ColorBase")){
			category = "#store_items";
		} else if (itemObject.IsBloodContainer() || itemObject.IsKindOf("Splint") || itemObject.IsKindOf("SalineBag") || itemObject.IsKindOf("SalineBagIV") || itemObject.IsKindOf("InjectionVial") || itemObject.IsKindOf("ClearSyringe") || itemObject.IsKindOf("CigarettePack_ColorBase") || itemObject.IsKindOf("Morphine") || itemObject.IsKindOf("Epinephrine") || itemObject.IsKindOf("DisinfectantAlcohol") || itemObject.IsKindOf("BloodTestKit")){
			category = "#medicine";
		} else if (itemObject.IsTransport()){
			category = "#transport";
		} else if (itemObject.IsFood() || itemObject.IsKindOf("AntiPestsSpray") || itemObject.IsKindOf("PlantBase") || itemObject.IsKindOf("SeedBase") || itemObject.IsKindOf("Edible_Base") || itemObject.IsKindOf("SodaCan_ColorBase") || itemObject.IsKindOf("SeedPackBase") || itemObject.IsKindOf("Edible_Base")){
			category = "#food";
		} else if (itemObject.IsFireplace()){
			category = "#fireplace";
		} else if (itemObject.IsKindOf("SuppressorBase") || itemObject.IsKindOf("ButtstockBase") || itemObject.IsKindOf("ItemOptics") || item.Contains("AK") || item.Contains("MP5") || item.Contains("M4")){
			category = "#weapon_part";
		} else if (itemObject.IsMeleeWeapon()){
			category = "#meleeWeapon";
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
}