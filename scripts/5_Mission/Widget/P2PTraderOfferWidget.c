class P2PTraderOfferWidget extends UIScriptedMenu
{
    private Widget parentWidget;
    private P2PItemService itemService;
    private MultilineTextWidget message;
	private DayZPlayer player;
	private ref array<ref P2PTraderItem> playerItems;

	private ButtonWidget buttonSearchOffer;
	private ButtonWidget buttonCreateCreateOffer;
	private ButtonWidget buttonMoveToGiveCreateMarketOffer;
	private ButtonWidget buttonMoveToInventoryCreateMarketOffer;
	private ButtonWidget buttonMoveToWillCreateMarketOffer;
	private ButtonWidget buttonMoveFromWillCreateMarketOffer;
	private ButtonWidget buttonCloseCreateOffer;
	private EditBoxWidget inputSearchOffer;
	private EditBoxWidget playerTextOffer;
	private EditBoxWidget minQuantityCreateMarketOffer;
	private EditBoxWidget minHealthCreateMarketOffer;
	private ItemPreviewWidget offerMenuMenuItemPreview;
	private TextListboxWidget playerInventoryItemsOffer;
	private TextListboxWidget playerWantToHaveOffer;
	private TextListboxWidget playerItemsOfferOffer;
	private TextListboxWidget tradableItemsOffer;
	private XComboBoxWidget offerTypeCreateOffer
	private MultilineTextWidget offerMenuItemPreviewText;

    void P2PTraderOfferWidget(DayZPlayer player, Widget parentWidget, P2PTraderItemListenerManger itemListenManager, P2PItemService itemService, MultilineTextWidget message) {
        this.player = player;
		this.parentWidget = parentWidget;
        this.itemService = itemService;
        this.message = message;

        layoutRoot = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/offer.layout");

        playerInventoryItemsOffer = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("playerInventoryItemsOffer"));
        offerTypeCreateOffer = XComboBoxWidget.Cast(layoutRoot.FindAnyWidget("offerTypeCreateOffer"));
        tradableItemsOffer = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("tradableItemsOffer"));
        playerWantToHaveOffer = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("playerWantToHaveOffer"));
        playerItemsOfferOffer = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("playerItemsOfferOffer"));
        playerTextOffer = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("playerTextOffer"));
        minQuantityCreateMarketOffer = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("minQuantityCreateMarketOffer"));
        minHealthCreateMarketOffer = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("minHealthCreateMarketOffer"));
        offerMenuMenuItemPreview = ItemPreviewWidget.Cast(layoutRoot.FindAnyWidget("offerMenuMenuItemPreview"));
        offerMenuItemPreviewText = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("offerMenuItemPreviewText"));
        buttonCreateCreateOffer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("buttonCreateCreateOffer"));
        buttonSearchOffer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("buttonSearchOffer"));
		inputSearchOffer = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("inputSearchOffer"));
        buttonMoveToGiveCreateMarketOffer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("buttonMoveToGiveCreateMarketOffer"));
        buttonMoveToInventoryCreateMarketOffer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("buttonMoveToInventoryCreateMarketOffer"));
        buttonMoveToWillCreateMarketOffer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("buttonMoveToWillCreateMarketOffer"));
        buttonMoveFromWillCreateMarketOffer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("buttonMoveFromWillCreateMarketOffer"));
        buttonCloseCreateOffer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("buttonCloseCreateOffer"));

        offerTypeCreateOffer.AddItem("#direct_offer");
        offerTypeCreateOffer.AddItem("#auction");
        offerTypeCreateOffer.SetCurrentItem(1);

        itemListenManager.AddItemMoveListener(buttonMoveToGiveCreateMarketOffer, buttonMoveToInventoryCreateMarketOffer, playerInventoryItemsOffer, playerItemsOfferOffer, true, offerMenuMenuItemPreview, offerMenuItemPreviewText);
        itemListenManager.AddItemMoveListener(buttonMoveToWillCreateMarketOffer, buttonMoveFromWillCreateMarketOffer, tradableItemsOffer, playerWantToHaveOffer, false, offerMenuMenuItemPreview, offerMenuItemPreviewText, minQuantityCreateMarketOffer, minHealthCreateMarketOffer);

        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCreateCreateOffer, this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCloseCreateOffer, this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonSearchOffer, this, "OnClick");

        parentWidget.AddChild(layoutRoot);
    }

    override void OnShow() {
        itemService.GetPlayerItemList(playerInventoryItemsOffer, playerItems);
        itemService.AddTradableItemsToWidget(tradableItemsOffer, "");
        inputSearchOffer.SetText("");
        layoutRoot.Show(true);
    }

    bool IsWidgetVisible() {
        return layoutRoot.IsVisible();
    }

    override void OnHide() {
		playerInventoryItemsOffer.ClearItems();
		playerItemsOfferOffer.ClearItems();
		playerWantToHaveOffer.ClearItems();
		tradableItemsOffer.ClearItems();
        layoutRoot.Show(false);
    }

    void OnGetPlayerItems(array<ref P2PTraderItem> playerItems) {
        this.playerItems = playerItems;
    }

    override bool OnClick(Widget w, int x, int y, int button)	{
        if(w == buttonCreateCreateOffer) {
            DebugMessageP2PTrader("Click on create offer");

            string offerType = P2PTraderPlayerMarketOffer.TYPE_AUCTION;

            if (0 == offerTypeCreateOffer.GetCurrentItem()) {
                offerType = P2PTraderPlayerMarketOffer.TYPE_INSTANT_BUY;
            }

            string messageText = itemService.CreateOffer(player, playerItemsOfferOffer, playerWantToHaveOffer, playerTextOffer.GetText(), offerType);
            message.SetText(messageText);

            playerItemsOfferOffer.ClearItems();
            playerWantToHaveOffer.ClearItems();
            layoutRoot.Show(false);
            return true;
        } else if(w == buttonCloseCreateOffer) {
	        DebugMessageP2PTrader("click buttonCloseCreateOffer");
	        layoutRoot.Show(false);
	        return true;
	    } else if(w == buttonSearchOffer) {
	        DebugMessageP2PTrader("click buttonSearchOffer");
	        itemService.AddTradableItemsToWidget(tradableItemsOffer, inputSearchOffer.GetText());
	        return true;
	    }
		return false;
	}
}