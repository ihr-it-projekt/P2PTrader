class P2PTraderItemListenerManger
{
	private ref array<ref P2PTraderItemMoveListener> moveListener;
	private ref array<ref P2PTraderPreviewWindow> previewListener;
	private P2PItemService itemService;
	
	void P2PTraderItemListenerManger(P2PItemService itemService) {
		moveListener = new array<ref P2PTraderItemMoveListener>;
		previewListener = new array<ref P2PTraderPreviewWindow>;
		this.itemService = itemService;
	}
	
	void AddItemMoveListener(ButtonWidget buttonSourceToTarget, ButtonWidget buttonTargetToSource, TextListboxWidget source, TextListboxWidget target, bool move, ItemPreviewWidget peviewWidget, MultilineTextWidget description) {
		moveListener.Insert(new P2PTraderItemMoveListener(buttonSourceToTarget, buttonTargetToSource, source, target, move, peviewWidget, description, itemService));
	}
	
	void AddPreviewListener(MultilineTextWidget description, ItemPreviewWidget peviewWidget, TextListboxWidget source) {
		P2PTraderPreviewWindow previewWindow = new P2PTraderPreviewWindow(peviewWidget, description, itemService);
		previewWindow.ListenOnClick(source);
		previewListener.Insert(previewWindow);
	}
}