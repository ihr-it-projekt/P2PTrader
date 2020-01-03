class P2PTraderPlayerInventory
{
    int PlayerHasItem(DayZPlayer player,int pos, string itemName) {
		array<EntityAI> itemsArray = GetPlayerItems(player);
        if(itemsArray.IsValidIndex(pos)) {
            ItemBase item = ItemBase.Cast(itemsArray.Get(pos));
			if (item.GetName() == itemName) {
				return true;
			}
        }

        return false;
    }

    ItemBase GetPlayerItem(DayZPlayer player, int pos)
    {
        if (!player) {
            DebugMessageP2PTrader("can not get items, no player set");
            return null;
        }

        array<EntityAI> itemsArray = GetPlayerItems(player);
        
        if(itemsArray.IsValidIndex(pos)) {
            return ItemBase.Cast(itemsArray.Get(pos));
        }
        

        return null;
    }
	
    array<EntityAI> GetPlayerItems(DayZPlayer player)
    {
        DebugMessageP2PTrader("GetPlayerItem");
        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

        return itemsArray;
    }
	

    void Add(DayZPlayer player, string itemName, int health) {
		EntityAI item;
		InventoryLocation inventoryLocation = new InventoryLocation;
		if (player.GetInventory().FindFirstFreeLocationForNewEntity(itemName, FindInventoryLocationType.ANY, inventoryLocation)) {
            item = player.GetHumanInventory().CreateInInventory(itemName);
        } else if (!player.GetHumanInventory().GetEntityInHands()) {
            item = player.GetHumanInventory().CreateInHands(itemName);
		} else {
            item = player.SpawnEntityOnGroundPos(itemName, player.GetPosition());
        }
		item.SetHealth(health);
    }

    void Remove(ItemBase item) {
		item.SetQuantity(0);
        DebugMessageP2PTrader("destroy item " + item.GetName());
    }
};