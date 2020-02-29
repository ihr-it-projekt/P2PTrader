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

    void Add(DayZPlayer player, P2PTraderStockItem itemInStock) {
		EntityAI item;
		InventoryLocation inventoryLocation = new InventoryLocation;

		if (player.GetInventory().FindFirstFreeLocationForNewEntity(itemInStock.type, FindInventoryLocationType.ANY, inventoryLocation)) {
            item = player.GetHumanInventory().CreateInInventory(itemInStock.type);
        } else if (!player.GetHumanInventory().GetEntityInHands()) {
            item = player.GetHumanInventory().CreateInHands(itemInStock.type);
		} else {
            item = player.SpawnEntityOnGroundPos(itemInStock.type, player.GetPosition());
        }

		if(itemInStock.attached.Count() > 0) {
            foreach(P2PTraderStockItem itemAttached: itemInStock.attached) {
                Add(player, itemAttached);
            }
        }
       

		item.SetHealth(itemInStock.health);
		ItemBase.Cast(item).SetQuantity(itemInStock.quantity);
    }

    void Remove(ItemBase item, DayZPlayer player) {
		GetGame().ObjectDelete(item);
		
        DebugMessageP2PTrader("destroy item " + item.GetName());
    }
};