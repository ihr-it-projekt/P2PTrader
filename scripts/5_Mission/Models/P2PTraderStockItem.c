class P2PTraderStockItem extends P2PTraderBaseItem
{
	float health
	string type;
	float quantity;
	ref array<ref P2PTraderStockItem> attached;
	private string translated;
	private string translatedName;
	private string translatedNameLower;
	private string lowerCaseName;
	
	void P2PTraderStockItem() {
		attached = new array<ref P2PTraderStockItem>;
	}

	override P2PTraderStockItem GetItem() {
        return this;
    }
	
	void SetItem(EntityAI item, bool isAttached = false) {
		health = item.GetHealth();
		SetType(item.GetType());
		
		ItemBase itemCast;
        ItemBase.CastTo(itemCast, item);
		
		if (itemCast) {
			quantity = itemCast.GetQuantity();
		} else {
			DebugMessageP2PTrader("P2PTraderStockItem: Can not cast " + item.GetType());
		}
		
		if(item.IsMagazine()) {
			Magazine mag = Magazine.Cast(item);
			
			if (!mag)
				return;
			quantity = mag.GetAmmoCount();
		} else if(item.IsAmmoPile()) {
			Ammunition_Base ammo = Ammunition_Base.Cast(item);
			
			if (!ammo) {
				return;
			}
			
			quantity = ammo.GetAmmoCount();
		}
		

		if (!isAttached) {
			array<EntityAI> itemsArray = new array<EntityAI>;
	        item.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);

			foreach(EntityAI itemAtteched: itemsArray) {
				if (itemAtteched !=item) {
					P2PTraderStockItem stockItem = new P2PTraderStockItem();
					stockItem.SetItem(itemAtteched, true);
					attached.Insert(stockItem);
				}
			}
		}
	}
	
	bool IsItem(ItemBase item) {
		float compareQuantity = item.GetQuantity();
		if(item.IsMagazine()) {
			Magazine mag = Magazine.Cast(item);
			
			if (!mag) {
				return false;
			}
			
			compareQuantity = mag.GetAmmoCount();
		} else if(item.IsAmmoPile()) {
			Ammunition_Base ammo = Ammunition_Base.Cast(item);
			
			if (!ammo) {
				return false;
			}
			
			compareQuantity = ammo.GetAmmoCount();
		}
		
		if (item.GetHealth() == this.GetHealth() && item.GetType() == this.GetType() && compareQuantity == this.GetQuantity()) {
			DebugMessageP2PTrader("Is item at base level check now attachmends");
			return CompareAttached(this, item);
		}
		
		return false;
	}
	
	private bool CompareAttached(P2PTraderStockItem marketOffer, ItemBase item) {
		array<EntityAI> itemsArray = new array<EntityAI>;
		item.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);
		
		bool hasAllFound = true;
		
		foreach(P2PTraderStockItem stockItem: marketOffer.attached) {
			bool hasFound = false;
			foreach(EntityAI itemAtteched: itemsArray) {
				ItemBase itemCast = ItemBase.Cast(itemAtteched);
				float compareQuantity = itemCast.GetQuantity();
				if(itemCast.IsMagazine()) {
					Magazine mag = Magazine.Cast(itemCast);
					
					if (!mag) {
						return false;
					}
					
					compareQuantity = mag.GetAmmoCount();
				}

				if (itemAtteched && stockItem && stockItem != itemAtteched && itemAtteched.GetHealth() == stockItem.GetHealth() && itemAtteched.GetType() == stockItem.GetType() && compareQuantity == stockItem.GetQuantity()) {
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
	
	override string GetType() {
		return type;
	}
	
	override void ResetTranslation() {
		this.translated = "";
		this.translatedNameLower = "";
	}
	
	override void SetTranslation(string translated, bool addType) {
	    this.translated = translated;
		this.translatedName = GetDisplayName(translated, addType);
		this.translatedNameLower = translated;
		this.translatedNameLower.ToLower();
	}
	
	override string UpdateTranslation(bool addType) {
		this.translatedName = GetDisplayName(this.translated, addType);
		this.translatedNameLower = this.translatedName;
        this.translatedNameLower.ToLower();
		return this.translatedName;
	}

	override bool Contains(string search) {
		search.ToLower();
        if(search != "" && !translatedNameLower.Contains(search)){
            return false;
        }

        return true;
    }
	
	string GetDisplayName(string translated, bool addType) {
		this.translated = translated;
		if (addType) {
			return translated + " (" + type + ")" + " #health " + this.GetHealth().ToString() + " #quantity: " + this.GetQuantity().ToString();
		} 
		return translated + " #health " + this.GetHealth().ToString() + " #quantity: " + this.GetQuantity().ToString();
	}
	
	string GetTranslatedNameLower() {
		return this.translatedNameLower;
	}
	
	override bool HasTranslation() {
		return !!this.translatedName;
	}
	
	override string GetTranslation() {
		return this.translatedName;
	}
	
	array<ref P2PTraderStockItem> GetAttached() {
		return attached;
	}
}