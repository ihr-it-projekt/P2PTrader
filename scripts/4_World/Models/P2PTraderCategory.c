class P2PTraderCategory
{
	const static string	SETTINGSFILE = "P2PTraderItemsCategory.json";
	private string name;
	private int id;
	private ref array<ref P2PTraderCategoryItem> items;
	private string fileName;
	
	void P2PTraderCategory(string name, int id, string fileNameSuffix = "") {
		fileName = fileNameSuffix + id.ToString() + SETTINGSFILE;
		
		if (IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGS_CATEGORY_FOLDER_P2P + fileName)) {
            DebugMessageP2PTrader("load file" + id.ToString() + SETTINGSFILE);
			JsonFileLoader<P2PTraderCategory>.JsonLoadFile(CONFIGS_CATEGORY_FOLDER_P2P + fileName, this);
			DebugMessageP2PTrader("Has category items loaded count: " + items.Count());
        } else {
			this.name = name;
			this.id = id;
			items = new array<ref P2PTraderCategoryItem>;
			SaveFile();
		}
	}
	
	void AddItem(string nameOfItem) {
		if (nameOfItem) {
			items.Insert(new P2PTraderCategoryItem(nameOfItem, this.id));
			SaveFile();
		}
	}
	
	array<ref P2PTraderCategoryItem> GetItems() {
		return items;
	}

	string GetName() {
	    return name;
	}

	int GetId() {
	    return id;
	}

	bool ContainsItem(string itemName) {
		foreach(P2PTraderCategoryItem item: items) {
			if (item.GetName() == itemName) {
				return true;
			}
		}
		
		return false;
	}

	string GetFileName() {
	    return fileName;
	}
	
	private void SaveFile(){
        if (IsServerAndMultiplayerP2PTrader()) {
            if (!FileExist(CONFIGS_CATEGORY_FOLDER_P2P)) {
                MakeDirectory(CONFIGS_CATEGORY_FOLDER_P2P);
                DebugMessageP2PTrader("create folder");
            }
            DebugMessageP2PTrader("save file: " + fileName);
            JsonFileLoader<P2PTraderCategory>.JsonSaveFile(CONFIGS_CATEGORY_FOLDER_P2P + fileName, this);
        }
    }
}