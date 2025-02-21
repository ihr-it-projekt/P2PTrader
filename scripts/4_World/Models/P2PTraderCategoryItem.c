class P2PTraderCategoryItem {
    private string name;
    private int categoryId;

    void P2PTraderCategoryItem(string _name, int _categoryId) {
        this.name = _name;
        this.categoryId = _categoryId;
    }

    string GetName() {
        return name;
    }

    int GetCategoryId() {
        return categoryId;
    }
}