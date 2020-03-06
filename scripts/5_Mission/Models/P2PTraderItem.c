class P2PTraderItem {
	string name;
	string translatedName;
	string translatedNameLower;
	string lowerCaseName;
	ref P2PTraderStockItem item;
	
	void P2PTraderItem(string name, EntityAI item = null) {
		this.name = name;
		this.lowerCaseName = name;
		this.lowerCaseName.ToLower();
		this.item = new P2PTraderStockItem();
		
		if (item) {
			this.item.SetItem(item);
		} else {
			this.item.SetType(name);
		}
	}
	
	void SetTranslation(string translated) {
		item.SetTranslation(translated);
		this.translatedName = item.GetTranslation() ;
		this.translatedNameLower = item.GetTranslatedNameLower();
	}
	
}