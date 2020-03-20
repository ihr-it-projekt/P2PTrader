class P2PTraderPreviewWindow extends Managed
{
    private ItemPreviewWidget widget;
    private MultilineTextWidget description;
    private EntityAI previewItem;
	private P2PItemService itemService;
	private TextListboxWidget listBoxWidget;

    void P2PTraderPreviewWindow(ItemPreviewWidget widget, MultilineTextWidget description, P2PItemService itemService) {
        this.widget = widget;
        this.description = description;
		this.itemService = itemService;
    }
	
	void ListenOnClick(TextListboxWidget listBoxWidget) {
		this.listBoxWidget = listBoxWidget;
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(listBoxWidget,  this, "OnClick");
	}
	
	bool OnClick() {
		DebugMessageP2PTrader("click on: " + listBoxWidget.GetName());
		if (previewItem) {
			GetGame().ObjectDelete(previewItem);
		}
		
		P2PTraderBaseItem item = itemService.GetSelectedItemPlayerOffer(listBoxWidget);
		return UpdatePreview(item);
	}
	
	bool UpdatePreview(P2PTraderBaseItem item) {
		if (!item) {
			DebugMessageP2PTrader("hide preview, no stock item");
			widget.Show(false);
			description.Show(false);
			return false;
		}
		
		Object itemObject = GetGame().CreateObject(item.GetType(), "0 0 0", true);
		
		if (!itemObject) {
			DebugMessageP2PTrader("hide preview, can not create item");
			return false;
		}
		
		previewItem = EntityAI.Cast(itemObject);
		
		if (!previewItem) {
			DebugMessageP2PTrader("hide preview, can not cast item");
			widget.Show(false);
			description.Show(false);
			return false;
		}
		
		Update(previewItem, item);
		
		return false;
	}
	
	private void Update(EntityAI previewItem, P2PTraderBaseItem item){
		DebugMessageP2PTrader("show preview, item is there");
		
		widget.SetItem(previewItem);
		widget.SetModelPosition(Vector(0,0,0.5));

		InventoryItem itemCast = InventoryItem.Cast(previewItem);

		if (itemCast) {
			this.description.SetText(item.GetTranslation() + " "+ itemCast.GetTooltip());
		} else {
			this.description.SetText("");
		}
		
		widget.Show(true);
		description.Show(true);
    }
}