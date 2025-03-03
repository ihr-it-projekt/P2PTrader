class P2PTraderOfferWidget extends P2PTraderBaseSubWidget {
    private ref array<ref P2PTraderItem> playerItems;

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
    private XComboBoxWidget categoryCreateMarketOffer
    private MultilineTextWidget offerMenuItemPreviewText;
    private ref Timer searchTimer;
    private string rememberedSearch = "";
    private int rememberedCategory = 0;

    override Widget Init() {
        super.Init();

        searchTimer = new Timer;

        P2PTraderUIItemCreator uIItemCreator = new P2PTraderUIItemCreator("P2PTrader/layout/offer.layout");
        layoutRoot = uIItemCreator.GetLayoutRoot();

        playerInventoryItemsOffer = uIItemCreator.GetTextListboxWidget("playerInventoryItemsOffer");
        playerWantToHaveOffer = uIItemCreator.GetTextListboxWidget("playerWantToHaveOffer");
        tradableItemsOffer = uIItemCreator.GetTextListboxWidget("tradableItemsOffer");
        playerItemsOfferOffer = uIItemCreator.GetTextListboxWidget("playerItemsOfferOffer");
        offerTypeCreateOffer = uIItemCreator.GetXComboBoxWidget("offerTypeCreateOffer");
        categoryCreateMarketOffer = uIItemCreator.GetXComboBoxWidget("categoryCreateMarketOffer");
        playerTextOffer = uIItemCreator.GetEditBoxWidget("playerTextOffer");
        inputSearchOffer = uIItemCreator.GetEditBoxWidget("inputSearchOffer");
        minQuantityCreateMarketOffer = uIItemCreator.GetEditBoxWidget("minQuantityCreateMarketOffer");
        minHealthCreateMarketOffer = uIItemCreator.GetEditBoxWidget("minHealthCreateMarketOffer");
        offerMenuMenuItemPreview = uIItemCreator.GetItemPreviewWidget("offerMenuMenuItemPreview");
        offerMenuItemPreviewText = uIItemCreator.GetMultilineTextWidget("offerMenuItemPreviewText");
        buttonCreateCreateOffer = uIItemCreator.GetButtonWidget("buttonCreateCreateOffer", this, "OnClick");
        buttonCloseCreateOffer = uIItemCreator.GetButtonWidget("buttonCloseCreateOffer", this, "OnClick");
        buttonMoveToGiveCreateMarketOffer = uIItemCreator.GetButtonWidget("buttonMoveToGiveCreateMarketOffer");
        buttonMoveToInventoryCreateMarketOffer = uIItemCreator.GetButtonWidget("buttonMoveToInventoryCreateMarketOffer");
        buttonMoveToWillCreateMarketOffer = uIItemCreator.GetButtonWidget("buttonMoveToWillCreateMarketOffer");
        buttonMoveFromWillCreateMarketOffer = uIItemCreator.GetButtonWidget("buttonMoveFromWillCreateMarketOffer");

        TStringArray enabledOfferTypes = config.traderConfigParams.enabledOfferTypes;

        if(enabledOfferTypes && enabledOfferTypes.Count() > 0) {
            foreach(string offerType: enabledOfferTypes) {
                offerTypeCreateOffer.AddItem("#" + offerType);
            }
        }

        array<ref P2PTraderCategory> categories = config.traderItemsConfig.GetItems().GetCategories();

        categoryCreateMarketOffer.AddItem("#all");

        foreach(P2PTraderCategory category: categories) {
            categoryCreateMarketOffer.AddItem(category.GetName());
        }

        offerTypeCreateOffer.SetCurrentItem(0);
        categoryCreateMarketOffer.SetCurrentItem(0);

        itemListenerManager.AddItemMoveListener(buttonMoveToGiveCreateMarketOffer, buttonMoveToInventoryCreateMarketOffer, playerInventoryItemsOffer, playerItemsOfferOffer, true, offerMenuMenuItemPreview, offerMenuItemPreviewText);
        itemListenerManager.AddItemMoveListener(buttonMoveToWillCreateMarketOffer, buttonMoveFromWillCreateMarketOffer, tradableItemsOffer, playerWantToHaveOffer, false, offerMenuMenuItemPreview, offerMenuItemPreviewText, minQuantityCreateMarketOffer, minHealthCreateMarketOffer);

        return layoutRoot;
    }

    override void OnShow() {
        itemService.GetPlayerItemList(playerInventoryItemsOffer, playerItems);
        itemService.AddTradableItemsToWidget(tradableItemsOffer, inputSearchOffer.GetText());
        layoutRoot.Show(true);
        searchTimer.Run(1, this, "RefreshSearch", null, true);
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
        searchTimer.Stop();
    }

    void OnGetPlayerItems(array<ref P2PTraderItem> _playerItems) {
        playerItems = _playerItems;
    }

    override bool OnClick(Widget w, int x, int y, int button)	{
        if(w == buttonCreateCreateOffer) {
            string offerType = config.traderConfigParams.enabledOfferTypes.Get(offerTypeCreateOffer.GetCurrentItem());

            string messageText = itemService.CreateOffer(player, playerItemsOfferOffer, playerWantToHaveOffer, playerTextOffer.GetText(), offerType);
            message.SetText(messageText);

            playerItemsOfferOffer.ClearItems();
            playerWantToHaveOffer.ClearItems();
            layoutRoot.Show(false);
            return true;
        } else if(w == buttonCloseCreateOffer) {
            layoutRoot.Show(false);
            return true;
        }
        return false;
    }

    void RefreshSearch() {
        if(rememberedSearch != inputSearchOffer.GetText() || rememberedCategory != categoryCreateMarketOffer.GetCurrentItem() - 1) {
            rememberedSearch = inputSearchOffer.GetText();
            rememberedCategory = categoryCreateMarketOffer.GetCurrentItem() - 1;
            itemService.AddTradableItemsToWidgetByCategory(tradableItemsOffer, rememberedSearch, rememberedCategory);
        }
    }
}
