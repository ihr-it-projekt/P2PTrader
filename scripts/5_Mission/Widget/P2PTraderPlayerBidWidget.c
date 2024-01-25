class P2PTraderPlayerBidWidget extends P2PTraderBaseSubWidget {
    private P2PTraderPlayerMarketOffer selectedMarketOffer;
    private ref array<ref P2PTraderItem> playerItems;

    private TextListboxWidget playerInventoryItemsPlayerOffer;
    private TextListboxWidget playerItemsOfferPlayerOffer;
    private TextListboxWidget playerOfferWantToHave;
    private EditBoxWidget playerTextPlayerOffer;
    private ButtonWidget buttonCreateCreatePlayerOffer;
    private ItemPreviewWidget bidMenuItemPreview;
    private MultilineTextWidget bidMenuItemPreviewText;
    private TextWidget playerNameBidDetail;
    private MultilineTextWidget playerOfferMessageDetailBid;
    private TextListboxWidget offerDetailItemsBid;
    private TextListboxWidget detailAttachmentBid;
    private ButtonWidget buttonMoveToGiveCreateCreatePlayerOffer;
    private ButtonWidget buttonMoveToInventoryCreatePlayerOffer;
    private ButtonWidget buttonCreateClosePlayerOffer;

    override Widget Init() {
        super.Init();
        P2PTraderUIItemCreator uIItemCreator = new P2PTraderUIItemCreator("P2PTrader/layout/bid.layout");
        layoutRoot = uIItemCreator.GetLayoutRoot();

        playerInventoryItemsPlayerOffer = uIItemCreator.GetTextListboxWidget("playerInventoryItemsPlayerOffer");
        playerItemsOfferPlayerOffer = uIItemCreator.GetTextListboxWidget("playerItemsOfferPlayerOffer");
        playerOfferWantToHave = uIItemCreator.GetTextListboxWidget("playerOfferWantToHave");
        playerTextPlayerOffer = uIItemCreator.GetEditBoxWidget("playerTextPlayerOffer");
        bidMenuItemPreview = uIItemCreator.GetItemPreviewWidget("bidMenuItemPreview");
        bidMenuItemPreviewText = uIItemCreator.GetMultilineTextWidget("bidMenuItemPreviewText");
        playerNameBidDetail = uIItemCreator.GetTextWidget("playerNameBidDetail");
        playerOfferMessageDetailBid = uIItemCreator.GetMultilineTextWidget("playerOfferMessageDetailBid");
        offerDetailItemsBid = uIItemCreator.GetTextListboxWidget("offerDetailItemsBid", this, "OnClick");
        detailAttachmentBid = uIItemCreator.GetTextListboxWidget("detailAttachmentBid");
        buttonCreateCreatePlayerOffer = uIItemCreator.GetButtonWidget("buttonCreateCreatePlayerOffer", this, "OnClick");
        buttonMoveToGiveCreateCreatePlayerOffer = uIItemCreator.GetButtonWidget("buttonMoveToGiveCreateCreatePlayerOffer");
        buttonMoveToInventoryCreatePlayerOffer = uIItemCreator.GetButtonWidget("buttonMoveToInventoryCreatePlayerOffer");
        buttonCreateClosePlayerOffer = uIItemCreator.GetButtonWidget("buttonCreateClosePlayerOffer", this, "OnClick");

        itemListenerManager.AddItemMoveListener(buttonMoveToGiveCreateCreatePlayerOffer, buttonMoveToInventoryCreatePlayerOffer, playerInventoryItemsPlayerOffer, playerItemsOfferPlayerOffer, true, bidMenuItemPreview, bidMenuItemPreviewText);

        CreatePreview(bidMenuItemPreview, bidMenuItemPreviewText);

        itemListenerManager.AddPreviewListener(previewWindow, detailAttachmentBid);
        itemListenerManager.AddPreviewListener(previewWindow, playerOfferWantToHave);

        return layoutRoot;
    }

    void SetMarketOfferDetails(P2PTraderPlayerMarketOffer selectedMarketOffer) {
        this.selectedMarketOffer = selectedMarketOffer;
        playerNameBidDetail.SetText(selectedMarketOffer.GetOwnerName());
        playerOfferMessageDetailBid.SetText(selectedMarketOffer.GetOfferMessage());

        playerOfferWantToHave.ClearItems();

        if(this.selectedMarketOffer.GetWantedItems().Count() > 0) {
            itemService.GetTraderStockItemList(playerOfferWantToHave, this.selectedMarketOffer.GetWantedItems());
        }

        itemService.GetMarketOfferItemList(offerDetailItemsBid, selectedMarketOffer);
    }

    override void OnShow() {
        itemService.GetPlayerItemList(playerInventoryItemsPlayerOffer, playerItems);
        playerItemsOfferPlayerOffer.ClearItems();
        playerTextPlayerOffer.SetText("");
        detailAttachmentBid.ClearItems();
        layoutRoot.Show(true);
    }

    void OnGetPlayerItems(array<ref P2PTraderItem> playerItems) {
        this.playerItems = playerItems;
    }

    bool IsWidgetVisible() {
        return layoutRoot.IsVisible();
    }

    override bool OnClick(Widget w, int x, int y, int button)	{
        if(w == buttonCreateCreatePlayerOffer) {
            string messageText = itemService.CreateOfferToPlayer(player, playerItemsOfferPlayerOffer, selectedMarketOffer, playerTextPlayerOffer.GetText());
            message.SetText(messageText);

            layoutRoot.Show(false);
            return true;
        } else if(w == offerDetailItemsBid) {
            P2PTraderStockItem currentOfferDetailItem = itemService.GetSelectedItemPlayerOffer(offerDetailItemsBid);
            if(!currentOfferDetailItem) {
                return true;
            }

            UpdatePreview(currentOfferDetailItem);

            itemService.GetMarketOfferItemAttachmentList(detailAttachmentBid, currentOfferDetailItem);
            return true;
        } else if(w == buttonCreateClosePlayerOffer) {
            OnHide();
            return true;
        }
        return false;
    }

    override void OnHide() {
        playerInventoryItemsPlayerOffer.ClearItems();
        playerItemsOfferPlayerOffer.ClearItems();
        layoutRoot.Show(false);
    }
}
