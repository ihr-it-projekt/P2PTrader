class P2PTraderScriptedMenu extends UIScriptedMenu
{
    protected ref P2PItemService itemService;
	protected ref P2PTraderPreviewWindow previewWindow;

    protected void CreatePreview(ItemPreviewWidget widget, MultilineTextWidget description) {
        previewWindow = new P2PTraderPreviewWindow(widget, description, itemService);
    }

    protected void UpdatePreview(P2PTraderBaseItem item) {
        previewWindow.UpdatePreview(item);
    }

}