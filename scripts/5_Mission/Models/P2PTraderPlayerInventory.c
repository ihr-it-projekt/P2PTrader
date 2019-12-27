class P2PTraderPlayerInventory
{
    bool PlayerHasEnoughItems(DayZPlayer player, string itemName, int count) {
        int amount = GetPlayerItemAmount(player, itemName);
        DebugMessageP2PTrader("Has amount of " + amount.ToString() + " from type: " + itemName);

        return count <= amount;
    }

    int GetPlayerItemAmount(DayZPlayer player, string itemName)
    {
        if (!player) {
            DebugMessageP2PTrader("can not get items, no player set");
            return 0;
        }

        DebugMessageP2PTrader("GetPlayerItemAmount");
        int amount = 0;

        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

        ItemBase item;
        for (int i = 0; i < itemsArray.Count(); i++)
        {
            Class.CastTo(item, itemsArray.Get(i));
            if(item && item.GetType() == itemName) {
                amount += item.GetQuantity();
            }
        }

        return amount;
    }


    int AddItemToPlayer(DayZPlayer player, string itemName, int count) {
        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

        ItemBase item;
        for (int i = 0; i < itemsArray.Count(); i++)
        {
            Class.CastTo(item, itemsArray.Get(i));
            if (item && item.GetType() == itemName) {
                if (count > 0) {
                    count = Add(count, item);
                } else if(count < 0) {
                    DebugMessageP2PTrader("try remove item");
                    count = Remove(count, item);
                }
                if (count == 0) {
                    DebugMessageP2PTrader("no item to add");
                    break;
                }
            }
        }

        if (count > 0) {
            count = AddNewItemToInventory(player, itemName, count);
        }

        return count;
    }

    private int AddNewItemToInventory(DayZPlayer player, string itemName, int count) {
        InventoryLocation inventoryLocation = new InventoryLocation;
        if (player.GetInventory().FindFirstFreeLocationForNewEntity(itemName, FindInventoryLocationType.ANY, inventoryLocation)) {
            EntityAI entityInInventory = player.GetHumanInventory().CreateInInventory(itemName);
            count = Add(count - 1, entityInInventory);
        } else if (!player.GetHumanInventory().GetEntityInHands()) {
            EntityAI entityInHands = player.GetHumanInventory().CreateInHands(itemName);
            count = Add(count - 1, entityInHands);
        } else {
            EntityAI entityToGround = player.SpawnEntityOnGroundPos(itemName, player.GetPosition());
            count = Add(count - 1, entityToGround);
        }

        if(count) {
            count = AddNewItemToInventory(player, itemName, count);
        }

        return count;
    }

    private int Add(int toAdd, EntityAI entity) {
        ItemBase item;
        ItemBase.CastTo(item, entity);

        int currencyAmount = item.GetQuantity();
        int maxAmount = item.GetQuantityMax();

        int canAddedChipsCount = maxAmount - currencyAmount;

        if (canAddedChipsCount > 0) {
            if (toAdd > canAddedChipsCount) {
                item.SetQuantity(maxAmount);
                toAdd -= canAddedChipsCount;
            } else {
                item.SetQuantity(currencyAmount + toAdd);
                toAdd = 0;
            }
        }

        return toAdd;
    }

    private int Remove(int toRemove, EntityAI entity) {
        ItemBase item;
        ItemBase.CastTo(item, entity);

        int canRemoveCount = item.GetQuantity();

        DebugMessageP2PTrader("has quantity " + canRemoveCount);
        DebugMessageP2PTrader("chips should remove " + toRemove);

        if (canRemoveCount > toRemove) {
            DebugMessageP2PTrader("down count Quantity ");
            item.AddQuantity(toRemove);
            toRemove = 0;
        } else {
            item.SetQuantity(0);
            DebugMessageP2PTrader("destroy item " + toRemove);
            toRemove += canRemoveCount;
        }

        return toRemove;
    }
};