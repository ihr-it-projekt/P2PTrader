class P2PTraderOfferWidget extends P2PTraderBaseSubWidget
{
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

    override Widget Init() {
        super.Init();
        P2PTraderUIItemCreator uIItemCreator = new P2PTraderUIItemCreator("P2PTrader/layout/offer.layout");
        layoutRoot = uIItemCreator.GetLayoutRoot();

        playerInventoryItemsOffer = uIItemCreator.GetTextListboxWidget("playerInventoryItemsOffer");
        playerWantToHaveOffer = uIItemCreator.GetTextListboxWidget("playerWantToHaveOffer");
        tradableItemsOffer = uIItemCreator.GetTextListboxWidget("tradableItemsOffer");
        playerItemsOfferOffer = uIItemCreator.GetTextListboxWidget("playerItemsOfferOffer");
        offerTypeCreateOffer = uIItemCreator.GetXComboBoxWidget("offerTypeCreateOffer");
        playerTextOffer = uIItemCreator.GetEditBoxWidget("playerTextOffer");
        inputSearchOffer = uIItemCreator.GetEditBoxWidget("inputSearchOffer");
        minQuantityCreateMarketOffer = uIItemCreator.GetEditBoxWidget("minQuantityCreateMarketOffer");
        minHealthCreateMarketOffer = uIItemCreator.GetEditBoxWidget("minHealthCreateMarketOffer");
        offerMenuMenuItemPreview = uIItemCreator.GetItemPreviewWidget("offerMenuMenuItemPreview");
        offerMenuItemPreviewText = uIItemCreator.GetMultilineTextWidget("offerMenuItemPreviewText");
        buttonCreateCreateOffer = uIItemCreator.GetButtonWidget("buttonCreateCreateOffer", this, "OnClick");
        buttonSearchOffer = uIItemCreator.GetButtonWidget("buttonSearchOffer", this, "OnClick");
        buttonCloseCreateOffer = uIItemCreator.GetButtonWidget("buttonCloseCreateOffer", this, "OnClick");
        buttonMoveToGiveCreateMarketOffer = uIItemCreator.GetButtonWidget("buttonMoveToGiveCreateMarketOffer");
        buttonMoveToInventoryCreateMarketOffer = uIItemCreator.GetButtonWidget("buttonMoveToInventoryCreateMarketOffer");
        buttonMoveToWillCreateMarketOffer = uIItemCreator.GetButtonWidget("buttonMoveToWillCreateMarketOffer");
        buttonMoveFromWillCreateMarketOffer = uIItemCreator.GetButtonWidget("buttonMoveFromWillCreateMarketOffer");

        offerTypeCreateOffer.AddItem("#instant_buy");
        offerTypeCreateOffer.AddItem("#auction");
        offerTypeCreateOffer.SetCurrentItem(1);

        itemListenerManager.AddItemMoveListener(buttonMoveToGiveCreateMarketOffer, buttonMoveToInventoryCreateMarketOffer, playerInventoryItemsOffer, playerItemsOfferOffer, true, offerMenuMenuItemPreview, offerMenuItemPreviewText);
        itemListenerManager.AddItemMoveListener(buttonMoveToWillCreateMarketOffer, buttonMoveFromWillCreateMarketOffer, tradableItemsOffer, playerWantToHaveOffer, false, offerMenuMenuItemPreview, offerMenuItemPreviewText, minQuantityCreateMarketOffer, minHealthCreateMarketOffer);

        return layoutRoot;
    }

    override void OnShow() {
        itemService.GetPlayerItemList(playerInventoryItemsOffer, playerItems);
        itemService.AddTradableItemsToWidget(tradableItemsOffer, inputSearchOffer.GetText());
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