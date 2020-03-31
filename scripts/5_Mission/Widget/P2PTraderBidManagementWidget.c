class P2PTraderBidManagementWidget extends P2PTraderBaseSubWidget
{
    private bool canTrade = false;
    private ref array<ref P2PTraderPlayerPlayerOffer> playerActiveOffers;
	private string bidFilterBidManagement = P2PTraderStock.OPEN_OFFER;
	private P2PTraderPlayerPlayerOffer selectedPlayerOfferBidManagement;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerAcceptedOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerInactiveOffers;
	private ref array<ref P2PTraderPlayerMarketOffer> marketItems;
	private P2PTraderUserListEventService userListEventService;

    private ButtonWidget buttonAcceptedBids;
    private ButtonWidget buttonCanceledBids;
    private ButtonWidget buttonOpenBids;
    private ButtonWidget buttonDeleteMyBid;
    private ButtonWidget buttonTakeBid;
    private ButtonWidget bidManagementCloseButton;
	private TextWidget bidManagementBidHint;
    private TextWidget bidManagementBidItemsLabel;
    private TextWidget bidManagementBidItemAttachmentLabel;
    private TextWidget bidManagementMarketOfferPlayerLabel;
    private TextWidget bidManagementMarketOfferPlayer;
    private TextWidget bidManagementMessageFromPlayerLabel;
    private TextWidget bidManagementMarketOfferWantToHaveLabel;
    private TextWidget bidManagementMarketOfferItemsLabel;
    private TextWidget bidManagementMarketItemAttachmentLabel;
    private ItemPreviewWidget bidManagementMenuMenuItemPreview;

    private MultilineTextWidget bidManagementMenuItemPreviewText;
    private MultilineTextWidget bidManagementMarketOfferMessage;
	private MultilineTextWidget bidManagementNotInNearHint;

	private TextListboxWidget bidManagementBids;
    private TextListboxWidget bidManagementMarketOfferWantToHave;
    private TextListboxWidget bidManagementMarketOfferDetailItemsBid;
    private TextListboxWidget bidManagementMarketOfferDetailAttachmentBid;
    private TextListboxWidget bidManagementBidItems;
    private TextListboxWidget bidManagementBidItemAttachment;

	void SetExtraInitDependencies(P2PTraderUserListEventService userListEventService, array<ref P2PTraderPlayerMarketOffer> marketItems) {
	    this.userListEventService = userListEventService;
        this.marketItems = marketItems;
	}

     override Widget Init() {
        super.Init();
        P2PTraderUIItemCreator uIItemCreator = new P2PTraderUIItemCreator("P2PTrader/layout/bidManagement.layout");
        layoutRoot = uIItemCreator.GetLayoutRoot();

        buttonAcceptedBids = uIItemCreator.GetButtonWidget("buttonAcceptedBids", this, "OnClick");
        buttonCanceledBids = uIItemCreator.GetButtonWidget("buttonCanceledBids", this, "OnClick");
        buttonOpenBids = uIItemCreator.GetButtonWidget("buttonOpenBids", this, "OnClick");
        buttonDeleteMyBid = uIItemCreator.GetButtonWidget("buttonDeleteMyBid", this, "OnClick");
        buttonTakeBid = uIItemCreator.GetButtonWidget("buttonTakeBid", this, "OnClick");
        bidManagementCloseButton = uIItemCreator.GetButtonWidget("bidManagementCloseButton", this, "OnClick");
        bidManagementBids = uIItemCreator.GetTextListboxWidget("bidManagementBids", this, "OnClick");
        bidManagementBidHint = uIItemCreator.GetTextWidget("bidManagementBidHint");
        bidManagementBidItemsLabel = uIItemCreator.GetTextWidget("bidManagementBidItemsLabel");
        bidManagementBidItemAttachmentLabel = uIItemCreator.GetTextWidget("bidManagementBidItemAttachmentLabel");
        bidManagementMarketOfferPlayerLabel = uIItemCreator.GetTextWidget("bidManagementMarketOfferPlayerLabel");
        bidManagementMarketOfferPlayer = uIItemCreator.GetTextWidget("bidManagementMarketOfferPlayer");
        bidManagementMessageFromPlayerLabel = uIItemCreator.GetTextWidget("bidManagementMessageFromPlayerLabel");
        bidManagementMarketOfferWantToHaveLabel = uIItemCreator.GetTextWidget("bidManagementMarketOfferWantToHaveLabel");
        bidManagementMarketOfferItemsLabel = uIItemCreator.GetTextWidget("bidManagementMarketOfferItemsLabel");
        bidManagementMarketItemAttachmentLabel = uIItemCreator.GetTextWidget("bidManagementMarketItemAttachmentLabel");
        bidManagementNotInNearHint = uIItemCreator.GetMultilineTextWidget("bidManagementNotInNearHint");

        bidManagementMarketOfferMessage = uIItemCreator.GetMultilineTextWidget("bidManagementMarketOfferMessage");

        bidManagementMarketOfferWantToHave = uIItemCreator.GetTextListboxWidget("bidManagementMarketOfferWantToHave");
        bidManagementMarketOfferDetailItemsBid = uIItemCreator.GetTextListboxWidget("bidManagementMarketOfferDetailItemsBid", this, "OnClick");
        bidManagementMarketOfferDetailAttachmentBid = uIItemCreator.GetTextListboxWidget("bidManagementMarketOfferDetailAttachmentBid");
        bidManagementBidItems = uIItemCreator.GetTextListboxWidget("bidManagementBidItems", this, "OnClick");
        bidManagementBidItemAttachment = uIItemCreator.GetTextListboxWidget("bidManagementBidItemAttachment");

        bidManagementMenuItemPreviewText = uIItemCreator.GetMultilineTextWidget("bidManagementMenuItemPreviewText");
        bidManagementMenuMenuItemPreview = uIItemCreator.GetItemPreviewWidget("bidManagementMenuMenuItemPreview");

        itemListenerManager.AddPreviewListener(bidManagementMenuItemPreviewText, bidManagementMenuMenuItemPreview, bidManagementBidItems);
        itemListenerManager.AddPreviewListener(bidManagementMenuItemPreviewText, bidManagementMenuMenuItemPreview, bidManagementBidItemAttachment);
        itemListenerManager.AddPreviewListener(bidManagementMenuItemPreviewText, bidManagementMenuMenuItemPreview, bidManagementMarketOfferWantToHave);
        itemListenerManager.AddPreviewListener(bidManagementMenuItemPreviewText, bidManagementMenuMenuItemPreview, bidManagementMarketOfferDetailItemsBid);
        itemListenerManager.AddPreviewListener(bidManagementMenuItemPreviewText, bidManagementMenuMenuItemPreview, bidManagementMarketOfferDetailAttachmentBid);

        layoutRoot.Show(false);

        return layoutRoot;
    }



    void SetCanTrade(bool canTrade) {
        this.canTrade = canTrade;
		bidManagementNotInNearHint.Show(!canTrade);
    }

    void OnGetAllBidOffers(array<ref P2PTraderPlayerPlayerOffer> playerActiveOffers) {
        this.playerActiveOffers = playerActiveOffers;

    }

    override void OnShow() {
        bidFilterBidManagement = P2PTraderStock.OPEN_OFFER;
        ShowHideBidManagementButtons();
        selectedPlayerOfferBidManagement = null;

        if(playerActiveOffers.Count() == 0) {
            bidManagementBidHint.Show(true);
            bidManagementBids.Show(false);
        } else {
            itemService.GetActiveOffersForStockItem(bidManagementBids, playerActiveOffers);
            bidManagementBidHint.Show(false);
            bidManagementBids.Show(true);
        }

        if(layoutRoot.IsVisible() && playerActiveOffers.Count() == 0 && P2PTraderStock.INACTIVE_OFFER == bidFilterBidManagement) {
            bidManagementBidHint.Show(true);
            bidManagementBids.Show(false);
        } else if(layoutRoot.IsVisible() && playerActiveOffers.Count() > 0 && P2PTraderStock.INACTIVE_OFFER == bidFilterBidManagement){
            itemService.GetActiveOffersForStockItem(bidManagementBids, playerActiveOffers);
            bidManagementBidHint.Show(false);
            bidManagementBids.Show(true);
        }
		buttonDeleteMyBid.Show(false);

        layoutRoot.Show(true);
    }

    bool IsWidgetVisible() {
        return layoutRoot.IsVisible();
    }

    override bool OnClick(Widget w, int x, int y, int button)	{
        if(w == buttonAcceptedBids) {
            selectedPlayerOfferBidManagement = null;
            bidManagementBidItemAttachment.ClearItems();
            bidManagementBidItems.ClearItems();

            if(!playerAcceptedOffers || playerAcceptedOffers.Count() == 0) {
                bidManagementBidHint.Show(true);
                bidManagementBids.Show(false);
            } else {
                itemService.GetActiveOffersForStockItem(bidManagementBids, playerAcceptedOffers);
                bidManagementBidHint.Show(false);
                bidManagementBids.Show(true);
            }

            bidFilterBidManagement = P2PTraderStock.ACCEPTED_OFFER;

            ShowHideBidManagementButtons();
            return true;
        } else if(w == buttonCanceledBids) {
            selectedPlayerOfferBidManagement = null;
            bidManagementBidItemAttachment.ClearItems();
            bidManagementBidItems.ClearItems();

            if(!playerInactiveOffers || playerInactiveOffers.Count() == 0) {
                bidManagementBidHint.Show(true);
                bidManagementBids.Show(false);
            } else {
                itemService.GetActiveOffersForStockItem(bidManagementBids, playerInactiveOffers);
                bidManagementBidHint.Show(false);
                bidManagementBids.Show(true);
            }
            bidFilterBidManagement = P2PTraderStock.INACTIVE_OFFER;

            ShowHideBidManagementButtons();
            return true;
        } else if(w == buttonOpenBids) {
            bidManagementBidItemAttachment.ClearItems();
            bidManagementBidItems.ClearItems();
            selectedPlayerOfferBidManagement = null;
            if(!playerActiveOffers || playerActiveOffers.Count() == 0) {
                bidManagementBidHint.Show(true);
                bidManagementBids.Show(false);
            } else {
                itemService.GetActiveOffersForStockItem(bidManagementBids, playerActiveOffers);
                bidManagementBidHint.Show(false);
                bidManagementBids.Show(true);
            }

            bidFilterBidManagement = P2PTraderStock.OPEN_OFFER;

            ShowHideBidManagementButtons();
            return true;
        } else if(w == bidManagementCloseButton) {
            layoutRoot.Show(false);
            bidManagementBids.ClearItems();
            bidManagementMarketOfferWantToHave.ClearItems();
            bidManagementMarketOfferDetailItemsBid.ClearItems();
            bidManagementMarketOfferDetailAttachmentBid.ClearItems();
            bidManagementBidItems.ClearItems();
            bidManagementBidItemAttachment.ClearItems();
            return true;
        } else if(w == buttonDeleteMyBid || w == buttonTakeBid) {
             DebugMessageP2PTrader("click buttonDeleteMyBid 1");
             if (!selectedPlayerOfferBidManagement) {
                 DebugMessageP2PTrader("no selected offer");
                 return true;
             }
             DebugMessageP2PTrader("click buttonDeleteMyBid 2");
             Param2<DayZPlayer, int> paramRemovePlayerToPlayerOffer = new Param2<DayZPlayer, int>(GetGame().GetPlayer(), selectedPlayerOfferBidManagement.GetId());
             GetGame().RPCSingleParam(paramRemovePlayerToPlayerOffer.param1, P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS, paramRemovePlayerToPlayerOffer, true);
             buttonDeleteMyBid.Show(false);
             buttonTakeBid.Show(false);
             selectedPlayerOfferBidManagement = null;
             bidManagementBidItems.ClearItems();
             bidManagementBidItemAttachment.ClearItems();
             bidManagementBids.ClearItems();
             userListEventService.RefreshPlayerLists();
             return true;
        } else if(w == bidManagementBids) {
            selectedPlayerOfferBidManagement = itemService.GetSelectedStockItem(bidManagementBids);
            P2PTraderPlayerMarketOffer selectedMarketOfferBidManagement;
            if (selectedPlayerOfferBidManagement) {
                foreach(P2PTraderPlayerMarketOffer marketOfferItems: marketItems) {
                    if (selectedPlayerOfferBidManagement.GetPlayerToMarketOfferId() == marketOfferItems.GetId()) {
                        selectedMarketOfferBidManagement = marketOfferItems;
                        break;
                    }
                }

                itemService.GetTraderStockItemList(bidManagementBidItems, selectedPlayerOfferBidManagement.GetOfferItems());
            }

            if (selectedMarketOfferBidManagement) {
                bidManagementMarketOfferPlayer.SetText(selectedMarketOfferBidManagement.GetOwnerName());
                bidManagementMarketOfferMessage.SetText(selectedMarketOfferBidManagement.GetOfferMessage());

                bidManagementMarketOfferWantToHave.ClearItems();

                if(selectedMarketOfferBidManagement.GetWantedItems().Count() > 0) {
                    itemService.GetTraderStockItemList(bidManagementMarketOfferWantToHave, selectedMarketOfferBidManagement.GetWantedItems());
                }

                itemService.GetMarketOfferItemList(bidManagementMarketOfferDetailItemsBid, selectedMarketOfferBidManagement);

            }
            ShowHideBidManagementButtons();
            return true;
        } else if(w == bidManagementBidItems) {
            P2PTraderStockItem selectedBidItemBidManagement = itemService.GetSelectedItemPlayerOffer(bidManagementBidItems);
            if (selectedBidItemBidManagement) {
                itemService.GetMarketOfferItemAttachmentList(bidManagementBidItemAttachment, selectedBidItemBidManagement);
            }
            ShowHideBidManagementButtons();
            return true;
        }
		
		return false;
    }

    int GetCountPlayerOffers() {
        return playerInactiveOffers.Count() + playerAcceptedOffers.Count();
    }

    void SetPlayerOffers(array<ref P2PTraderPlayerPlayerOffer> playerInactiveOffers, ref array<ref P2PTraderPlayerPlayerOffer> playerAcceptedOffers) {
        this.playerInactiveOffers = playerInactiveOffers;
        this.playerAcceptedOffers = playerAcceptedOffers;

        if (layoutRoot.IsVisible()) {
          if((!playerInactiveOffers || playerInactiveOffers.Count() == 0) && P2PTraderStock.INACTIVE_OFFER == bidFilterBidManagement) {
              bidManagementBidHint.Show(true);
              bidManagementBids.Show(false);
          } else if(playerInactiveOffers && playerInactiveOffers.Count() > 0 && P2PTraderStock.INACTIVE_OFFER == bidFilterBidManagement){
              itemService.GetActiveOffersForStockItem(bidManagementBids, playerInactiveOffers);
              bidManagementBidHint.Show(false);
              bidManagementBids.Show(true);
          }else if((!playerAcceptedOffers || playerAcceptedOffers.Count() == 0) && P2PTraderStock.ACCEPTED_OFFER == bidFilterBidManagement) {
              bidManagementBidHint.Show(true);
              bidManagementBids.Show(false);
          } else if(playerAcceptedOffers && playerAcceptedOffers.Count() > 0 && P2PTraderStock.ACCEPTED_OFFER == bidFilterBidManagement){
              itemService.GetActiveOffersForStockItem(bidManagementBids, playerAcceptedOffers);
              bidManagementBidHint.Show(false);
              bidManagementBids.Show(true);
          }
          ShowHideBidManagementButtons();
      }

    }

    override void OnHide() {
        buttonDeleteMyBid.Show(false);
        layoutRoot.Show(false);
    }

    private void ShowHideBidManagementButtons() {
        if (P2PTraderStock.OPEN_OFFER == bidFilterBidManagement) {
            buttonAcceptedBids.Show(true);
            buttonCanceledBids.Show(true);
            buttonOpenBids.Show(false);
        } else if (P2PTraderStock.ACCEPTED_OFFER == bidFilterBidManagement) {
            buttonAcceptedBids.Show(false);
            buttonCanceledBids.Show(true);
            buttonOpenBids.Show(true);
        } else if (P2PTraderStock.INACTIVE_OFFER == bidFilterBidManagement) {
            buttonAcceptedBids.Show(true);
            buttonCanceledBids.Show(false);
            buttonOpenBids.Show(true);
        }

        if (selectedPlayerOfferBidManagement) {
            if (P2PTraderStock.OPEN_OFFER == bidFilterBidManagement) {
                bidManagementMarketOfferPlayerLabel.Show(true);
                bidManagementMarketOfferPlayer.Show(true);
                bidManagementMessageFromPlayerLabel.Show(true);
                bidManagementMarketOfferMessage.Show(true);
                bidManagementMarketOfferWantToHaveLabel.Show(true);
                bidManagementMarketOfferWantToHave.Show(true);
                bidManagementMarketOfferItemsLabel.Show(true);
                bidManagementMarketOfferDetailItemsBid.Show(true);
                bidManagementMarketItemAttachmentLabel.Show(true);
                bidManagementMarketOfferDetailAttachmentBid.Show(true);
                buttonTakeBid.Show(false);
                if (!canTrade) {
                    buttonDeleteMyBid.Show(false);
                } else {
                    buttonDeleteMyBid.Show(true);
                }
            } else {
                bidManagementMarketOfferPlayerLabel.Show(false);
                bidManagementMarketOfferPlayer.Show(false);
                bidManagementMessageFromPlayerLabel.Show(false);
                bidManagementMarketOfferMessage.Show(false);
                bidManagementMarketOfferWantToHaveLabel.Show(false);
                bidManagementMarketOfferWantToHave.Show(false);
                bidManagementMarketOfferItemsLabel.Show(false);
                bidManagementMarketOfferDetailItemsBid.Show(false);
                bidManagementMarketItemAttachmentLabel.Show(false);
                bidManagementMarketOfferDetailAttachmentBid.Show(false);
                if (!canTrade) {
                    buttonTakeBid.Show(false);
                } else {
                    buttonTakeBid.Show(true);
                }
                buttonTakeBid.Show(true);
                buttonDeleteMyBid.Show(false);
            }
            bidManagementBidItemsLabel.Show(true);
            bidManagementBidItems.Show(true);
            bidManagementBidItemAttachmentLabel.Show(true);
            bidManagementBidItemAttachment.Show(true);
        } else {
            bidManagementMarketOfferPlayerLabel.Show(false);
            bidManagementMarketOfferPlayer.Show(false);
            bidManagementMessageFromPlayerLabel.Show(false);
            bidManagementMarketOfferMessage.Show(false);
            bidManagementMarketOfferWantToHaveLabel.Show(false);
            bidManagementMarketOfferWantToHave.Show(false);
            bidManagementMarketOfferItemsLabel.Show(false);
            bidManagementMarketOfferDetailItemsBid.Show(false);
            bidManagementMarketItemAttachmentLabel.Show(false);
            bidManagementMarketOfferDetailAttachmentBid.Show(false);
            bidManagementBidItemsLabel.Show(false);
            bidManagementBidItems.Show(false);
            bidManagementBidItemAttachmentLabel.Show(false);
            bidManagementBidItemAttachment.Show(false);
            buttonTakeBid.Show(false);
            buttonDeleteMyBid.Show(false);
        }
    }
}