class P2PTraderStockItem {

	float health
	string type;
	float quantity;
	ref array<ref P2PTraderStockItem> attached;
	private string translatedName;
	private string translatedNameLower;
	private string lowerCaseName;;
	
	void P2PTraderStockItem() {
		attached = new array<ref P2PTraderStockItem>;
	}
	
	void SetItem(EntityAI item) {
		health = item.GetHealth();
		SetType(item.GetType());
		
		ItemBase itemCast = ItemBase.Cast(item);
		
		if (itemCast) {
			quantity = itemCast.GetQuantity();
		} else {
			DebugMessageP2PTrader("P2PTraderStockItem: Can not cast " + item.GetType());
		}
		
		array<EntityAI> itemsArray = new array<EntityAI>;
        item.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);
		
		foreach(EntityAI itemAtteched: itemsArray) {
			if (itemAtteched !=item) {
				P2PTraderStockItem stockItem = new P2PTraderStockItem();
				stockItem.SetItem(itemAtteched);
				attached.Insert(stockItem);
			}
		}
	}
	
	float GetHealth() {
		return health;
	}
	
	float GetQuantity() {
		return quantity;
	}
	
	void SetType(string type) {
		this.lowerCaseName = type;
		this.lowerCaseName.ToLower();
		this.type = type;
	}
	
	string GetType() {
		return type;
	}
	
	void SetTranslation(string translated) {
		this.translatedName = translated + " (" + type + ")";
		this.translatedNameLower = translated;
		this.translatedNameLower.ToLower();
	}
	
	bool HasTranslation() {
		return !!this.translatedName;
	}
	
	string GetTranslation() {
		return this.translatedName;
	}
	
	array<ref P2PTraderStockItem> GetAttached() {
		return attached;
	}
	
}