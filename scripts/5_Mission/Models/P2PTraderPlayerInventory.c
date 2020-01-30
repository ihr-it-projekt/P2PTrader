class P2PTraderPlayerInventory
{
    array<EntityAI> GetPlayerItems(DayZPlayer player)
    {
        DebugMessageP2PTrader("GetPlayerItem");
        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);
		

        return itemsArray;
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

        addAttechmends(item, itemInStock.attached);

		item.SetHealth(itemInStock.health);
		item.SetQuantity(itemInStock.quantity);
    }

    private void addAttechmend(EntityAi item, array<ref P2PTraderStockItem>attached) {
        if(attached.Count() > 0) {
            foreach(P2PTraderStockItem itemInStock: attached) {
                EntityAI newItem = item.GetInventory().CreateInInventory(itemInStock.type);
                newItem.SetHealth(itemInStock.health);
                newItem.SetQuantity(itemInStock.quantity);
                addAttechmend(newItem, itemInStock.attached);
            }
        }
    }

    void Remove(ItemBase item, DayZPlayer player) {
		GetGame().ObjectDelete(item);
		
        DebugMessageP2PTrader("destroy item " + item.GetName());
    }
};