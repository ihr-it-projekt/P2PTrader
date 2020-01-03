class P2PTraderItems
{
	private DayZPlayer owner;
	private ref array <ItemBase> items;
	
	void P2PTraderItem(DayZPlayer owner, ItemBase item) {
		this.owner = owner;
		this.items = new array<ItemBase>;
		this.items.Insert(item);
	}
	
	void AddItem(ItemBase item) {
		items.Insert(item);
	}
	
	void RemoveItem(int index) {
		if (items.IsValidIndex(index)) {
			items.Remove(index);
		}
	}
	
}