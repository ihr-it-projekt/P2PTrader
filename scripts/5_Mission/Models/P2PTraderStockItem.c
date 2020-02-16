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
	
	bool IsItem(ItemBase item) {
		if (item.GetHealth() == this.GetHealth() && item.GetType() == this.GetType() && item.GetQuantity() == this.GetQuantity()) {
			DebugMessageP2PTrader("Is item at base level check now attachmends");
			return CompareAttached(this, item);
		}
		
		return false;
	}
	
	private bool CompareAttached(P2PTraderStockItem stockItems, ItemBase item) {
		array<EntityAI> itemsArray = new array<EntityAI>;
		item.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);
		
		bool hasAllFound = true;
		
		foreach(P2PTraderStockItem stockItem: stockItems.attached) {
			bool hasFound = false;
			foreach(EntityAI itemAtteched: itemsArray) {
				ItemBase itemCast = ItemBase.Cast(itemAtteched);
				if (itemAtteched && stockItem && stockItem != itemAtteched && itemAtteched.GetHealth() == stockItem.GetHealth() && itemAtteched.GetType() == stockItem.GetType() && itemCast.GetQuantity() == stockItem.GetQuantity()) {
					DebugMessageP2PTrader("Is item at deeper level check now attachmends for attachmend: " + stockItem.GetType() + itemAtteched.GetType());
					hasFound = CompareAttached(stockItem, itemCast);
					DebugMessageP2PTrader("has found in deeper: " + hasFound.ToString());
					break;
				}
				
			}
			hasAllFound = hasAllFound && hasFound;
		}
		DebugMessageP2PTrader("has attached found " + hasAllFound.ToString());
		return hasAllFound;
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
		this.translatedName = translated + " (" + type + ")" + " #healt " + this.GetHealth().ToString();
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