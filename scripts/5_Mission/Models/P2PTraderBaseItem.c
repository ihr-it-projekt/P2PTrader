class P2PTraderBaseItem
{
	int category = 0;

	void SetCategory(int category) {
		this.category = category;
	}

	int GetCategory() {
		return category;
	}
	
	string GetType() {
		return "";
	}
	
	P2PTraderStockItem GetItem() {
		return null;
	}
	
	string GetTranslation() {
		return "";
	}
	
	bool HasTranslation() {
		return false;
	}
	
	string UpdateTranslation(bool addType) {
		return "";
	}

    bool Contains(string search) {
        return false;
    }
	
	void SetTranslation(string translated, bool addType) {
		
	}
	
	void ResetTranslation() {
		
	}
}