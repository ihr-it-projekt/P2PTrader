class P2PTraderItem extends P2PTraderBaseItem {
    private ref P2PTraderStockItem item;

    void P2PTraderItem(string name, int categoryId, EntityAI _item = null) {
        item = new P2PTraderStockItem();

        if(_item) {
            item.SetItem(_item);
        } else {
            item.SetType(name);
        }

        item.SetCategory(categoryId);
        SetCategory(categoryId);
    }

    override void SetTranslation(string _translated, bool _addType) {
        item.SetTranslation(_translated, _addType);
    }

    override bool Contains(string search) {
        search.ToLower();
        string searchName = item.GetTranslatedNameLower();

        if(search != "" && !searchName.Contains(search)) {
            return false;
        }

        return true;
    }

    override bool HasTranslation() {
        return item.HasTranslation();
    }

    override string GetTranslation() {
        return item.GetTranslation();
    }

    override string UpdateTranslation(bool addType) {
        return item.UpdateTranslation(addType);
    }

    override P2PTraderStockItem GetItem() {
        return item;
    }

    override string GetType() {
        return item.GetType();
    }
}