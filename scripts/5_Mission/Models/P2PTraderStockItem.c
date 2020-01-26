class P2PTraderStockItem {

	float health
	string type;
	float quantity;
	ref array<ref P2PTraderStockItem> attached;
	
	void P2PTraderStockItem() {
		attached = new array<ref P2PTraderStockItem>;
	}
	
	void SetItem(EntityAI item) {
		health = item.GetHealth();
		type = item.GetType();
		
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
		this.type = type;
	}
	
	string GetType() {
		return type;
	}
	
	
}