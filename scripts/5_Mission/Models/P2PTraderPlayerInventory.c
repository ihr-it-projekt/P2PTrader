class P2PTraderPlayerInventory {
    array<EntityAI> GetPlayerItems(DayZPlayer player) {
        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);

        return itemsArray;
    }

    void AddCollection(DayZPlayer player, array <ref P2PTraderStockItem> stockPlayerOfferItems) {
        foreach(P2PTraderStockItem stockPlayerOfferItem: stockPlayerOfferItems) {
            this.Add(player, stockPlayerOfferItem);
        }
    }
    void AddCollectionNoRef(DayZPlayer player, array <P2PTraderStockItem> stockPlayerOfferItems) {
        foreach(P2PTraderStockItem stockPlayerOfferItem: stockPlayerOfferItems) {
            this.Add(player, stockPlayerOfferItem);
        }
    }

    void Add(DayZPlayer player, P2PTraderStockItem itemInStock, ref InventoryLocation inventoryLocation = null) {
        EntityAI item;

        if(!inventoryLocation) {
            inventoryLocation = new InventoryLocation;
        }

        if(player.GetInventory().FindFirstFreeLocationForNewEntity(itemInStock.type, FindInventoryLocationType.ANY, inventoryLocation)) {
            item = player.GetHumanInventory().CreateInInventory(itemInStock.type);
        } else if(!player.GetHumanInventory().GetEntityInHands()) {
            item = player.GetHumanInventory().CreateInHands(itemInStock.type);
        }

        SpawnOnGround(itemInStock, player, item);

        if(itemInStock.attached.Count() > 0) {
            foreach(P2PTraderStockItem itemAttached: itemInStock.attached) {
                this.Add(player, itemAttached, inventoryLocation);
            }
        }
    }

    void Remove(ItemBase item) {
        GetGame().ObjectDelete(item);
    }

    EntityAI SpawnOnGround(P2PTraderStockItem itemInStock, DayZPlayer player = null, EntityAI item = null) {
        if(!item && player) {
            item = player.SpawnEntityOnGroundPos(itemInStock.type, player.GetPosition());
        }

        if(item) {
            item.SetHealth(itemInStock.health);

            ItemBase castItem;
            if(item.IsMagazine()) {
                Magazine mag = Magazine.Cast(item);

                if(!mag) {
                    return item;
                }

                mag.ServerSetAmmoCount(itemInStock.GetQuantity());
            } else if(item.IsAmmoPile()) {
                Ammunition_Base ammo = Ammunition_Base.Cast(item);

                if(!ammo) {
                    return item;
                }
                ammo.ServerSetAmmoCount(itemInStock.GetQuantity());
            } else if(ItemBase.CastTo(castItem, item)) {
                castItem.SetQuantity(itemInStock.GetQuantity(), true, true);
            }
        }

        return item;
    }
};
