class P2PTraderOfferWidget extends UIScriptedMenu
{
    Widget parentWidget;
    P2PItemService itemService;
    MultilineTextWidget message;
	DayZPlayer player;
	private ButtonWidget buttonSearchOffer;
	private EditBoxWidget inputSearchOffer;

	private TextListboxWidget playerInventoryItemsOffer;
	private XComboBoxWidget offerTypeCreateOffer
	private EditBoxWidget playerTextOffer;
	private TextListboxWidget playerWantToHaveOffer;
	private TextListboxWidget playerItemsOfferOffer;
	private ItemPreviewWidget offerMenuMenuItemPreview;
	private MultilineTextWidget offerMenuItemPreviewText;
	private ButtonWidget buttonCreateCreateOffer;
	private TextListboxWidget tradableItemsOffer;
	private EditBoxWidget minQuantityCreateMarketOffer;
	private EditBoxWidget minHealthCreateMarketOffer;
	private ButtonWidget buttonMoveToGiveCreateMarketOffer;
	private ButtonWidget buttonMoveToInventoryCreateMarketOffer;
	private ButtonWidget buttonMoveToWillCreateMarketOffer;
	private ButtonWidget buttonMoveFromWillCreateMarketOffer;
	private ButtonWidget buttonCloseCreateOffer;
	private Widget createOfferWidget;

    void P2PTraderOfferWidget(DayZPlayer player, Widget parentWidget, P2PTraderItemListenerManger itemListenManager, P2PItemService itemService, MultilineTextWidget message) {
        this.player = player;
		this.parentWidget = parentWidget;
        this.itemService = itemService;
        this.message = message;

        createOfferWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/offer.layout");

        playerInventoryItemsOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("playerInventoryItemsOffer"));
        offerTypeCreateOffer = XComboBoxWidget.Cast(createOfferWidget.FindAnyWidget("offerTypeCreateOffer"));
        tradableItemsOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("tradableItemsOffer"));
        playerWantToHaveOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("playerWantToHaveOffer"));
        playerItemsOfferOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("playerItemsOfferOffer"));
        playerTextOffer = EditBoxWidget.Cast(createOfferWidget.FindAnyWidget("playerTextOffer"));
        minQuantityCreateMarketOffer = EditBoxWidget.Cast(createOfferWidget.FindAnyWidget("minQuantityCreateMarketOffer"));
        minHealthCreateMarketOffer = EditBoxWidget.Cast(createOfferWidget.FindAnyWidget("minHealthCreateMarketOffer"));
        offerMenuMenuItemPreview = ItemPreviewWidget.Cast(createOfferWidget.FindAnyWidget("offerMenuMenuItemPreview"));
        offerMenuItemPreviewText = MultilineTextWidget.Cast(createOfferWidget.FindAnyWidget("offerMenuItemPreviewText"));
        buttonCreateCreateOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonCreateCreateOffer"));
        buttonSearchOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonSearchOffer"));
		inputSearchOffer = EditBoxWidget.Cast(createOfferWidget.FindAnyWidget("inputSearchOffer"));
        buttonMoveToGiveCreateMarketOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonMoveToGiveCreateMarketOffer"));
        buttonMoveToInventoryCreateMarketOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonMoveToInventoryCreateMarketOffer"));
        buttonMoveToWillCreateMarketOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonMoveToWillCreateMarketOffer"));
        buttonMoveFromWillCreateMarketOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonMoveFromWillCreateMarketOffer"));
        buttonCloseCreateOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonCloseCreateOffer"));

        offerTypeCreateOffer.AddItem("#direct_offer");
        offerTypeCreateOffer.AddItem("#auction");
        offerTypeCreateOffer.SetCurrentItem(1);

        itemListenManager.AddItemMoveListener(buttonMoveToGiveCreateMarketOffer, buttonMoveToInventoryCreateMarketOffer, playerInventoryItemsOffer, playerItemsOfferOffer, true, offerMenuMenuItemPreview, offerMenuItemPreviewText);
        itemListenManager.AddItemMoveListener(buttonMoveToWillCreateMarketOffer, buttonMoveFromWillCreateMarketOffer, tradableItemsOffer, playerWantToHaveOffer, false, offerMenuMenuItemPreview, offerMenuItemPreviewText, minQuantityCreateMarketOffer, minHealthCreateMarketOffer);

        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCreateCreateOffer, this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCloseCreateOffer, this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonSearchOffer, this, "OnClick");

        layoutRoot.AddChild(createOfferWidget);

		itemService.AddTradableItemsToWidget(tradableItemsOffer, "");

    }

    override void OnShow() {
        createOfferWidget.Show(true);
    }

    bool IsWidgetVisible() {
        return createOfferWidget.IsVisible();
    }

    override void OnHide() {
		playerInventoryItemsOffer.ClearItems();
		playerItemsOfferOffer.ClearItems();
		playerWantToHaveOffer.ClearItems();
		tradableItemsOffer.ClearItems();
        createOfferWidget.Show(false);
    }

    void OnGetPlayerItems(array<ref P2PTraderItem> playerItems) {
        itemService.GetPlayerItemList(playerInventoryItemsOffer, playerItems);
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
            createOfferWidget.Show(false);
            return true;
        } else if(w == buttonCloseCreateOffer) {
	        DebugMessageP2PTrader("click buttonCloseCreateOffer");
	        createOfferWidget.Show(false);
	        return true;
	    } else if(w == buttonSearchOffer) {
	        DebugMessageP2PTrader("click buttonSearchOffer");
	        itemService.AddTradableItemsToWidget(tradableItemsOffer, inputSearchOffer.GetText());
	        return true;
	    }
		return false;
	}
}