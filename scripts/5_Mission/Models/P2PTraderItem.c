class P2PTraderItem extends P2PTraderBaseItem
{
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
		this.translatedName = item.GetDisplayName(translated);
		this.translatedNameLower = translated;
		this.translatedNameLower.ToLower();
	}
	
	override P2PTraderStockItem GetItem() {
		return item;
	}
	
	override string GetType() {
		return this.item.GetType();
	}

}