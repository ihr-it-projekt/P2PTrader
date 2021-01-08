class P2PTraderBaseOffer
{
	ref P2PTraderDate creationDate;
	protected string ownerId;
    protected string ownerName;
    protected ref array <ref P2PTraderStockItem> offerItems;
    protected int id;
	
	protected void SetCreationDate() {
       	creationDate = new P2PTraderDate();
		creationDate.SetDate();
		creationDate.SetInSeconds();
	}
	
	int GetId() {
		return id;
	}
	
	void SetId(int id){
		this.id = id;
	}

    array <ref P2PTraderStockItem> GetOfferItems() {
	   return offerItems;
	}

    void AddOfferItem(ref P2PTraderStockItem item) {
        offerItems.Insert(item);
    }

    string GetOwnerId() {
        return ownerId;
    }

	string GetOwnerName() {
		return ownerName;
	}
	
	bool IsExceeded(P2PTraderDate date, int maxDays) {
		if (!creationDate || creationDate.year == 0) {
			creationDate = new P2PTraderDate();
			creationDate.SetDate();
			creationDate.SetInSeconds();
			false;
		}
        P2PTraderExpiredDate expiredDate = new P2PTraderExpiredDate(creationDate, maxDays);

		if (date.IsAfter(expiredDate)) {
			return true;
		}

        return false;
	}
	
	
	array<int> getAllCategoryIds() {
		array<int> ids = new array<int>;
		
	    foreach(P2PTraderStockItem item: offerItems) {
			ids.Insert(item.GetCategory());
			
			array<ref P2PTraderStockItem> attacheds = item.GetAttached();
			foreach(P2PTraderStockItem attached: attacheds) {
				ids.Insert(attached.GetCategory());
			}
		}
		
		return ids;
	}
	
	array<string> getAllItemTypes() {
		array<string> types = new array<string>;
		
	    foreach(P2PTraderStockItem item: offerItems) {
			types.Insert(item.type);
			
			array<ref P2PTraderStockItem> attacheds = item.GetAttached();
			foreach(P2PTraderStockItem attached: attacheds) {
				types.Insert(attached.type);
			}
		}
		
		return types;
	}
	
	void UpdateCategories(array<string> types, array<int> categoryIds) {
		foreach(P2PTraderStockItem item: offerItems) {
			int pos = types.Find(item.type);
			item.SetCategory(categoryIds.Get(pos));
			
			array<ref P2PTraderStockItem> attacheds = item.GetAttached();
			foreach(P2PTraderStockItem attached: attacheds) {
				pos = types.Find(attached.type);
				attached.SetCategory(categoryIds.Get(pos));
			}
		}
	}
}
