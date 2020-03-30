class P2PTraderItem extends P2PTraderBaseItem
{
	private string name;
	private ref P2PTraderStockItem item;
	
	void P2PTraderItem(string name, EntityAI item = null) {
		this.name = name;
		this.item = new P2PTraderStockItem();
		
		if (item) {
			this.item.SetItem(item);
		} else {
			this.item.SetType(name);
		}
	}

	string GetName() {
	    return name;
	}
	
	void SetTranslation(string translated) {
	    item.SetTranslation(translated);
	}

	override bool Contains(string search) {
	    search.ToLower();
        string searchName = item.GetTranslatedNameLower();
		DebugMessageP2PTrader("Search for: " + search + " Item is: " + searchName);

	    if(search != "" && !searchName.Contains(search)) {
			return false;
		}

		return true;
    }
	
	override string GetTranslation() {
		return item.GetTranslation();
	}
	
	override string UpdateTranslation() {
        return item.UpdateTranslation();
	}
	
	override P2PTraderStockItem GetItem() {
		return item;
	}
	
	override string GetType() {
		return this.item.GetType();
	}
}