class P2PTraderItem extends P2PTraderBaseItem
{
	private ref P2PTraderStockItem item;
	
	void P2PTraderItem(string name, EntityAI item = null) {
		this.item = new P2PTraderStockItem();
		
		if (item) {
			this.item.SetItem(item);
		} else {
			this.item.SetType(name);
		}
	}
	
	override void SetTranslation(string translated) {
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
	
	override bool HasTranslation() {
		return item.HasTranslation();
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