class P2PTraderBaseItem
{
	string category = "";

	void SetCategory(string category) {
		this.category = category;
	}

	string GetCategory() {
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
	
	string UpdateTranslation() {
		return "";
	}

    bool Contains(string search) {
        return false;
    }
	
	void SetTranslation(string translated) {
		
	}
	
	void ResetTranslation() {
		
	}
}