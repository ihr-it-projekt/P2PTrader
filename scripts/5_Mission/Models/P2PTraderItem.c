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
	    if (item) {
	        this.translatedName = item.GetDisplayName(translated);
	    } else {
	        this.translatedName = translated;
	    }

		this.translatedNameLower = this.translatedName;
		this.translatedNameLower.ToLower();
	}

	override bool Contains(string search) {
		search.ToLower();
	    if(search != "" && !item.GetTranslatedNameLower().Contains(search)) {
			return false;
		}
		return true;
    }
	
	override string GetTranslation() {
		return this.translatedName;
	}
	
	override string UpdateTranslation() {
		if (item) {
			this.translatedName = item.UpdateTranslation();
		}
		return this.translatedName;
	}
	
	override P2PTraderStockItem GetItem() {
		return item;
	}
	
	override string GetType() {
		return this.item.GetType();
	}

}