class P2PTraderPlayerInventory
{
    array<EntityAI> GetPlayerItems(DayZPlayer player)
    {
        DebugMessageP2PTrader("GetPlayerItem");
        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);
		

        return itemsArray;
    }
	
	void AddCollection(DayZPlayer player, array <ref P2PTraderStockItem> stockPlayerOfferItems) {
		foreach(P2PTraderStockItem stockPlayerOfferItem: stockPlayerOfferItems) {
			this.Add(player, stockPlayerOfferItem);
		}
	}

    void Add(DayZPlayer player, P2PTraderStockItem itemInStock, ref InventoryLocation inventoryLocation = null) {
		EntityAI item;
		
		if (!inventoryLocation) {
			inventoryLocation = new InventoryLocation;
		}
		
		if (player.GetInventory().FindFirstFreeLocationForNewEntity(itemInStock.type, FindInventoryLocationType.ANY, inventoryLocation)) {
			DebugMessageP2PTrader("spawn in inventory" + itemInStock.type);
            item = player.GetHumanInventory().CreateInInventory(itemInStock.type);
        } else if (!player.GetHumanInventory().GetEntityInHands()) {
			DebugMessageP2PTrader("spawn in hands" + itemInStock.type);
            item = player.GetHumanInventory().CreateInHands(itemInStock.type);
		}
			
       	SpawnOnGround(itemInStock, player, item);

		if(itemInStock.attached.Count() > 0) {
            foreach(P2PTraderStockItem itemAttached: itemInStock.attached) {
				DebugMessageP2PTrader("has Attachments" + itemInStock.type);
                this.Add(player, itemAttached, inventoryLocation);
            }
        }
    }

    void Remove(ItemBase item) {
		GetGame().ObjectDelete(item);
		
        DebugMessageP2PTrader("destroy item " + item.GetName());
    }

	private EntityAI SpawnOnGround(P2PTraderStockItem itemInStock, DayZPlayer player, EntityAI item = null) {
		if (item) {
			item.SetHealth(itemInStock.health);
			ItemBase.Cast(item).SetQuantity(itemInStock.quantity);
			DebugMessageP2PTrader("has spawned" + itemInStock.type);
		} else {
			DebugMessageP2PTrader("spawn on ground" + itemInStock.type);
            item = player.SpawnEntityOnGroundPos(itemInStock.type, player.GetPosition());
			if (!item) {
				DebugMessageP2PTrader("item was not spawned" + itemInStock.type);
			} else {
				item.SetHealth(itemInStock.health);
				ItemBase.Cast(item).SetQuantity(itemInStock.quantity);
			}
			
		}
	
		return item;
	}
};