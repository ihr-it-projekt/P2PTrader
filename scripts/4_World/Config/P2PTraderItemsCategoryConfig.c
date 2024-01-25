class P2PTraderItemsCategoryConfig {
    const static string	ITEM_CATEGORY_PREFIX = "offer";
    private ref P2PTraderCategoryCollection items;

    void P2PTraderItemsCategoryConfig() {
        items = new P2PTraderCategoryCollection(ITEM_CATEGORY_PREFIX);
    }

    P2PTraderCategoryCollection GetItems() {
        return items;
    }

    string GetCategoryItemName(int index) {
        P2PTraderCategory category = items.GetCategories().Get(index);
        if(category) {
            return category.GetName();
        }

        return "";
    }
}