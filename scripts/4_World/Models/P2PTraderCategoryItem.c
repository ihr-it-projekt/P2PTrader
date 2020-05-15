class P2PTraderCategoryItem
{
	private string name;
	private int categoryId;
	
	void P2PTraderCategoryItem(string name, int categoryId) {
		this.name = name;
		this.categoryId = categoryId;
	}
	
	string GetName() {
		return name;
	}
	
	int GetCategoryId() {
		return categoryId;
	}
}