class P2PTraderPlayerBidWidget extends UIScriptedMenu
{
    Widget parentWidget;
    P2PItemService itemService;
    MultilineTextWidget message;
	DayZPlayer player;
	private P2PTraderPlayerMarketOffer selectedMarketOffer;
	private ref array<ref P2PTraderItem> playerItems;
	private ref P2PTraderPreviewWindow offerDetailItemsBidPreview;

	private TextListboxWidget playerInventoryItemsPlayerOffer;
	private TextListboxWidget playerItemsOfferPlayerOffer;
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

    void P2PTraderPlayerBidWidget(DayZPlayer player, Widget parentWidget, P2PTraderItemListenerManger itemListenerManager, P2PItemService itemService, MultilineTextWidget message) {
        this.player = player;
        this.parentWidget = parentWidget;
        this.itemService = itemService;
        this.message = message;

        layoutRoot = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/bid.layout");

        playerInventoryItemsPlayerOffer = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("playerInventoryItemsPlayerOffer"));
        playerItemsOfferPlayerOffer = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("playerItemsOfferPlayerOffer"));
        playerTextPlayerOffer = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("playerTextPlayerOffer"));
        buttonCreateCreatePlayerOffer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("buttonCreateCreatePlayerOffer"));
        bidMenuItemPreview = ItemPreviewWidget.Cast(layoutRoot.FindAnyWidget("bidMenuItemPreview"));
		bidMenuItemPreviewText = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("bidMenuItemPreviewText"));
        playerNameBidDetail = TextWidget.Cast( layoutRoot.FindAnyWidget( "playerNameBidDetail" ));
        playerOfferMessageDetailBid = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "playerOfferMessageDetailBid" ));
        offerDetailItemsBid = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("offerDetailItemsBid"));
        detailAttachmentBid = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("detailAttachmentBid"));
        buttonMoveToGiveCreateCreatePlayerOffer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("buttonMoveToGiveCreateCreatePlayerOffer"));
        buttonMoveToInventoryCreatePlayerOffer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("buttonMoveToInventoryCreatePlayerOffer"));
        buttonCreateClosePlayerOffer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("buttonCreateClosePlayerOffer"));

        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCreateClosePlayerOffer,this,"OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCreateCreatePlayerOffer,this,"OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(offerDetailItemsBid,this,"OnClick");

        itemListenerManager.AddItemMoveListener(buttonMoveToGiveCreateCreatePlayerOffer, buttonMoveToInventoryCreatePlayerOffer, playerInventoryItemsPlayerOffer, playerItemsOfferPlayerOffer, true, bidMenuItemPreview, bidMenuItemPreviewText);
        itemListenerManager.AddPreviewListener(bidMenuItemPreviewText, bidMenuItemPreview, detailAttachmentBid);

        offerDetailItemsBidPreview = new P2PTraderPreviewWindow(bidMenuItemPreview, bidMenuItemPreviewText, itemService);

        parentWidget.AddChild(layoutRoot);
    }

    void SetMarketOfferDetails(P2PTraderPlayerMarketOffer selectedMarketOffer) {
		this.selectedMarketOffer = selectedMarketOffer;
        playerNameBidDetail.SetText(selectedMarketOffer.GetOwnerName());
        playerOfferMessageDetailBid.SetText(selectedMarketOffer.GetOfferMessage());
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
        DebugMessageP2PTrader("player items was set, count: " + playerItems.Count().ToString());
        this.playerItems = playerItems;
    }

    bool IsWidgetVisible() {
        return layoutRoot.IsVisible();
    }

    override bool OnClick(Widget w, int x, int y, int button)	{
        if(w == buttonCreateCreatePlayerOffer) {
            DebugMessageP2PTrader("Click on create player offer");
            string messageText = itemService.CreateOfferToPlayer(player, playerItemsOfferPlayerOffer, selectedMarketOffer, playerTextPlayerOffer.GetText());
            message.SetText(messageText);

            layoutRoot.Show(false);
            return true;
        } else if(w == offerDetailItemsBid) {
            DebugMessageP2PTrader("click offerDetailItemsBid");
            P2PTraderStockItem currentOfferDetailItem = itemService.GetSelectedItemPlayerOffer(offerDetailItemsBid);
            if (!currentOfferDetailItem) {
                return true;
            }

            offerDetailItemsBidPreview.UpdatePreview(currentOfferDetailItem);

            itemService.GetMarketOfferItemAttachmentList(detailAttachmentBid, currentOfferDetailItem);
            return true;
        } else if(w == buttonCreateClosePlayerOffer) {
            DebugMessageP2PTrader("click buttonCreateClosePlayerOffer");
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