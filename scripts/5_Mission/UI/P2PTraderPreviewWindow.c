class P2PTraderPreviewWindow extends Managed {
    private ItemPreviewWidget widget;
    private MultilineTextWidget description;
    private EntityAI previewItem;
    private P2PItemService itemService;

    void P2PTraderPreviewWindow(ItemPreviewWidget _widget, MultilineTextWidget _description, P2PItemService _itemService) {
        widget = _widget;
        description = _description;
        itemService = _itemService;
    }

    void ListenOnClick(TextListboxWidget listBoxWidget) {
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(listBoxWidget, this, "OnClick");
    }

    bool OnClick(Widget _widget, int x, int y, int button) {
        if(previewItem) {
            GetGame().ObjectDelete(previewItem);
        }

        P2PTraderBaseItem item = itemService.GetSelectedItemPlayerOffer(TextListboxWidget.Cast(_widget));
        return UpdatePreview(item);
    }

    bool UpdatePreview(P2PTraderBaseItem item) {
        if(!item) {
            widget.Show(false);
            description.Show(false);
            return false;
        }

        Object itemObject = GetGame().CreateObject(item.GetType(), "0 0 0", true);

        if(!itemObject) {
            return false;
        }

        previewItem = EntityAI.Cast(itemObject);

        if(!previewItem) {
            widget.Show(false);
            description.Show(false);
            return false;
        }

        Update(previewItem, item);

        return false;
    }

    private void Update(EntityAI _previewItem, P2PTraderBaseItem item) {

        widget.SetItem(_previewItem);
        widget.SetModelPosition(Vector(0, 0, 0.5));

        InventoryItem itemCast = InventoryItem.Cast(_previewItem);

        if(itemCast) {
            description.SetText(item.GetTranslation() + " " + itemCast.GetTooltip());
        } else {
            this.description.SetText("");
        }

        widget.Show(true);
        description.Show(true);
    }
}
