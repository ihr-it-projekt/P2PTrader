class P2PTraderCategoryCollection {
    private ref array<ref P2PTraderCategory> categories;

    void P2PTraderCategoryCollection(string suffix) {
        P2PTraderConfiguredCategory configuredConfig = new P2PTraderConfiguredCategory;
        array<string> categoryNames = configuredConfig.categoryNames;
        categories = new array<ref P2PTraderCategory>;
        foreach(int index, string name: categoryNames) {
            categories.Insert(new P2PTraderCategory(name, index, suffix));
        }
    }

    void AddItemToCategory(string itemName, int categoryId) {
        P2PTraderCategory category = categories.Get(categoryId);
        category.AddItem(itemName);
    }

    array<ref P2PTraderCategory> GetCategories() {
        return categories;
    }

    int GetCategoryIdByItemName(string itemName) {
        foreach(P2PTraderCategory category: categories) {
            if(category.ContainsItem(itemName)) {
                return category.GetId();
            }
        }

        return -1;
    }

}
