class P2PTraderMenu extends UIScriptedMenu
{
	private DayZPlayer player;
	private string playerId;
	private P2PTraderConfig config;
	private P2PTraderPlayerMarketOffer selectedMarketOffer;
	private ref array<ref P2PTraderPlayerPlayerOffer> selectedPlayerOffers;
	private P2PTraderPlayerPlayerOffer selectedPlayerOffer;
	private P2PTraderPlayerPlayerOffer selectedPlayerOfferBidManagement;
	private ref P2PItemService itemService;
	private ref array<ref P2PTraderPlayerMarketOffer> marketItems;
	private ref array<ref P2PTraderPlayerMarketOffer> marketPlayerItems;
	private ref array<ref P2PTraderPlayerPlayerOffer> allActiveOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerActiveOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerInactiveOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerAcceptedOffers;
	private P2PTraderPlayerPlayerOffer playerOfferForSelectedStockItem;
	private ref P2PTraderOfferWidget offerWidget;
	private ref P2PTraderPlayerBidWidget playerBidWidget;
	private Widget createPlayerOfferWidget;
	private Widget bidManagementWidget;
	private string bidFilterBidManagement = P2PTraderStock.OPEN_OFFER;
	private bool canTrade = false;
	private EntityAI mainMenuPreviewItem;
	private ref P2PTraderItemListenerManger itemListenManager;
	private ref P2PTraderMainMenuFilterListener mainMenuFilterListener;
	bool isMenuOpen = false;
	int refreshRuns = 0;
	
	private ItemPreviewWidget mainMenuItemPreview;
	private MultilineTextWidget mainMenuItemPreviewText;
	private MultilineTextWidget mainMenuItemPreviewHealth;
	private MultilineTextWidget mainMenuItemPreviewQuantity;

    private ButtonWidget cancel;
	private ButtonWidget buttonTakeOffer;
	private ButtonWidget buttonDeleteMyOffer;
	private ButtonWidget buttonOpenCreateMyBid;
	private ButtonWidget buttonOpenCreateOffer;
	private ButtonWidget buttonManageMyBids;
	private TextListboxWidget marketOffers;
	private TextListboxWidget marketOfferItems;
	private TextListboxWidget marketOfferItemAtatmenchts;
	private TextListboxWidget marketOfferWantToHave;
	private TextListboxWidget playerOfferItems;
	private TextListboxWidget playerOffers;
	private TextListboxWidget playerOfferItemAttachments;
	private MultilineTextWidget playerOfferMessageDetail;
	private TextWidget playerNameOfferDetail;
	private TextWidget offerPlayerLabel;
	private TextWidget offerMessageFromPlayerLabel;
	private TextWidget offerItemLabel;
	private TextWidget offerItemAttachmentLabel;
	private TextWidget offerMyBidAttachmentLabel;
	private TextWidget offerMyBidsLabel;
	private TextWidget offerMyBidLabel;
	private TextWidget marketOfferWantToHaveLabel;
	private TextWidget playerOfferItemMessageLabel;
	private MultilineTextWidget message;
	private MultilineTextWidget notInNearHint;
	private MultilineTextWidget bidManagementNotInNearHint;
	private MultilineTextWidget playerOfferItemMessage;

	private ButtonWidget buttonAcceptedBids;
	private ButtonWidget buttonCanceledBids;
	private ButtonWidget buttonOpenBids;
	private ButtonWidget buttonDeleteMyBid;
	private ButtonWidget buttonTakeBid;
	private ButtonWidget bidManagementCloseButton;
	
	private TextWidget bidManagementBidItemsLabel;
	private TextWidget bidManagementBidItemAttachmentLabel;
	private TextWidget bidManagementMarketOfferPlayerLabel;
	private TextWidget bidManagementMarketOfferPlayer;
	private TextWidget bidManagementMessageFromPlayerLabel;
	private TextWidget bidManagementMarketOfferWantToHaveLabel;
	private TextWidget bidManagementMarketOfferItemsLabel;
	private TextWidget bidManagementMarketItemAttachmentLabel;
	private TextWidget bidManagementBidHint;
	
	private MultilineTextWidget bidManagementMarketOfferMessage;
	
	private TextListboxWidget bidManagementBids;
	private TextListboxWidget bidManagementMarketOfferWantToHave;
	private TextListboxWidget bidManagementMarketOfferDetailItemsBid;
	private TextListboxWidget bidManagementMarketOfferDetailAttachmentBid;
	private TextListboxWidget bidManagementBidItems;
	private TextListboxWidget bidManagementBidItemAttachment;
	
	private ItemPreviewWidget bidManagemenMenuMenuItemPreview;
	private MultilineTextWidget bidManagemenMenuItemPreviewText;

	
	void SetConfig(P2PTraderConfig configExt) {
        config = configExt;
	}

    override Widget Init()
    {
		
        if (IsServerP2PTrader()){
            DebugMessageP2PTrader("can not init, is server");
            return null;
        }

        if (IsInitialized()) {
            return layoutRoot;
        }

        super.Init();
		
		itemService = new P2PItemService(config);
		player = GetGame().GetPlayer();
		playerId = player.GetIdentity().GetId();
		itemListenManager = new P2PTraderItemListenerManger(itemService);
		marketItems = new ref array<ref P2PTraderPlayerMarketOffer>;
		marketPlayerItems = new ref array<ref P2PTraderPlayerMarketOffer>;

        layoutRoot = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/mainMenu.layout");


        cancel = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "cancel" ));
        buttonOpenCreateOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonOpenCreateOffer" ));
        buttonManageMyBids = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonManageMyBids" ));
        buttonDeleteMyOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonDeleteMyOffer" ));
        buttonTakeOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonTakeOffer" ));
        buttonOpenCreateMyBid = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonOpenCreateMyBid" ));
        marketOffers = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "marketOffers" ));
        marketOfferItems = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "marketOfferItems" ));
        marketOfferItemAtatmenchts = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "marketOfferItemAtatmenchts" ));
        marketOfferWantToHave = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "marketOfferWantToHave" ));
        playerOffers = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "playerOffers" ));
        playerOfferItems = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "playerOfferItems" ));
        playerOfferItemAttachments = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "playerOfferItemAttachments" ));
        playerNameOfferDetail = TextWidget.Cast( layoutRoot.FindAnyWidget( "playerNameOfferDetail" ));
        offerPlayerLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerPlayerLabel" ));
        marketOfferWantToHaveLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "marketOfferWantToHaveLabel" ));
        playerOfferItemMessageLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "playerOfferItemMessageLabel" ));
        offerItemAttachmentLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerItemAttachmentLabel" ));
        offerItemLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerItemLabel" ));
        offerMessageFromPlayerLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerMessageFromPlayerLabel" ));
        offerMyBidAttachmentLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerMyBidAttachmentLabel" ));
        offerMyBidLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerMyBidLabel" ));
        offerMyBidsLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerMyBidsLabel" ));
        playerOfferMessageDetail = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "playerOfferMessageDetail" ));
		notInNearHint = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("notInNearHint"));
		message = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("message"));
		playerOfferItemMessage = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("playerOfferItemMessage"));

		mainMenuItemPreview = ItemPreviewWidget.Cast(layoutRoot.FindAnyWidget("mainMenuItemPreview"));
		mainMenuItemPreviewText = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("mainMenuItemPreviewText"));
		mainMenuItemPreviewHealth = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("mainMenuItemPreviewHealth"));
		mainMenuItemPreviewQuantity = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("mainMenuItemPreviewQuantity"));

		itemListenManager.AddPreviewListener(mainMenuItemPreviewText, mainMenuItemPreview, marketOfferWantToHave);
		itemListenManager.AddPreviewListener(mainMenuItemPreviewText, mainMenuItemPreview, marketOfferItems);
		itemListenManager.AddPreviewListener(mainMenuItemPreviewText, mainMenuItemPreview, marketOfferItemAtatmenchts);
		itemListenManager.AddPreviewListener(mainMenuItemPreviewText, mainMenuItemPreview, playerOfferItems);
		itemListenManager.AddPreviewListener(mainMenuItemPreviewText, mainMenuItemPreview, playerOfferItemAttachments);

		mainMenuFilterListener = new P2PTraderMainMenuFilterListener(layoutRoot, itemService, marketOffers);

        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(cancel,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonOpenCreateOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonManageMyBids,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonDeleteMyOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonTakeOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonOpenCreateMyBid,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(marketOffers,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(marketOfferItems,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(playerOfferItems,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(playerOffers,  this, "OnClick");

		offerWidget = new P2PTraderOfferWidget(player, layoutRoot, itemListenManager, itemService, message);
		playerBidWidget = new P2PTraderPlayerBidWidget(player, layoutRoot, itemListenManager, itemService, message);

		bidManagementWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/bidManagement.layout");

		//start player offers layout
		
        buttonAcceptedBids = ButtonWidget.Cast( bidManagementWidget.FindAnyWidget( "buttonAcceptedBids" ));
        buttonCanceledBids = ButtonWidget.Cast( bidManagementWidget.FindAnyWidget( "buttonCanceledBids" ));
        buttonOpenBids = ButtonWidget.Cast( bidManagementWidget.FindAnyWidget( "buttonOpenBids" ));
        buttonDeleteMyBid = ButtonWidget.Cast( bidManagementWidget.FindAnyWidget( "buttonDeleteMyBid" ));
        buttonTakeBid = ButtonWidget.Cast( bidManagementWidget.FindAnyWidget( "buttonTakeBid" ));
        bidManagementCloseButton = ButtonWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementCloseButton" ));

        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonAcceptedBids,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCanceledBids,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonOpenBids,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonDeleteMyBid,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonTakeBid,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(bidManagementCloseButton,  this, "OnClick");

        bidManagementBidItemsLabel = TextWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementBidItemsLabel" ));
        bidManagementBidItemAttachmentLabel = TextWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementBidItemAttachmentLabel" ));
        bidManagementMarketOfferPlayerLabel = TextWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementMarketOfferPlayerLabel" ));
        bidManagementMarketOfferPlayer = TextWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementMarketOfferPlayer" ));
        bidManagementMessageFromPlayerLabel = TextWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementMessageFromPlayerLabel" ));
        bidManagementMarketOfferWantToHaveLabel = TextWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementMarketOfferWantToHaveLabel" ));
        bidManagementMarketOfferItemsLabel = TextWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementMarketOfferItemsLabel" ));
        bidManagementMarketItemAttachmentLabel = TextWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementMarketItemAttachmentLabel" ));
        bidManagementBidHint = TextWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementBidHint" ));
        bidManagementNotInNearHint = MultilineTextWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementNotInNearHint" ));

        bidManagementMarketOfferMessage = MultilineTextWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementMarketOfferMessage" ));

        bidManagementBids = TextListboxWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementBids" ));
        bidManagementMarketOfferWantToHave = TextListboxWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementMarketOfferWantToHave" ));
        bidManagementMarketOfferDetailItemsBid = TextListboxWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementMarketOfferDetailItemsBid" ));
        bidManagementMarketOfferDetailAttachmentBid = TextListboxWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementMarketOfferDetailAttachmentBid" ));
        bidManagementBidItems = TextListboxWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementBidItems" ));
        bidManagementBidItemAttachment = TextListboxWidget.Cast( bidManagementWidget.FindAnyWidget( "bidManagementBidItemAttachment" ));

        bidManagemenMenuItemPreviewText = MultilineTextWidget.Cast(bidManagementWidget.FindAnyWidget("bidManagemenMenuItemPreviewText"));
        bidManagemenMenuMenuItemPreview = ItemPreviewWidget.Cast(bidManagementWidget.FindAnyWidget("bidManagemenMenuMenuItemPreview"));
		
		itemListenManager.AddPreviewListener(bidManagemenMenuItemPreviewText, bidManagemenMenuMenuItemPreview, bidManagementBidItems);
		itemListenManager.AddPreviewListener(bidManagemenMenuItemPreviewText, bidManagemenMenuMenuItemPreview, bidManagementBidItemAttachment);
		itemListenManager.AddPreviewListener(bidManagemenMenuItemPreviewText, bidManagemenMenuMenuItemPreview, bidManagementMarketOfferDetailItemsBid);
		itemListenManager.AddPreviewListener(bidManagemenMenuItemPreviewText, bidManagemenMenuMenuItemPreview, bidManagementMarketOfferDetailAttachmentBid);

        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(bidManagementBids,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(bidManagementMarketOfferDetailItemsBid,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(bidManagementBidItems,  this, "OnClick");
		
		bidManagementWidget.Show(false);
		//end player offers layout

        layoutRoot.Show(false);
		
		return layoutRoot;
    }
	
	void SetCanTrade(bool canTrade) {
		this.canTrade = canTrade;
	}

    override bool OnClick(Widget w, int x, int y, int button)	{
        bool actionRuns = super.OnClick(w, x, y, button);
        string messageText;

        if (actionRuns) {
            return actionRuns;
        } else if (w == cancel){
            DebugMessageP2PTrader("click cancel");
            CloseMenu();
            return true;
        } else if(w == buttonOpenCreateMyBid && selectedMarketOffer) {
			if (config.traderConfigParams.maxMarketOffersPerPlayer == playerActiveOffers.Count() + playerInactiveOffers.Count() + playerAcceptedOffers.Count()) {
				message.SetText("#you_reach_max_market_offers_per_player");
				return true;
			}
			DebugMessageP2PTrader("click buttonOpenCreateMyBid");

            playerBidWidget.SetMarketOfferDetails(selectedMarketOffer);
            playerBidWidget.OnShow();

			mainMenuItemPreview.Show(false);
			mainMenuItemPreviewText.Show(false);

			return true;
		} else if(w == buttonOpenCreateOffer) {
			DebugMessageP2PTrader("click buttonOpenCreateOffer");
			if (config.traderConfigParams.maxMarketOffersPerPlayer == marketPlayerItems.Count()) {
				message.SetText("#you_reach_max_bid_offers_per_player");
			} else {
				offerWidget.OnShow();
                mainMenuItemPreview.Show(false);
                mainMenuItemPreviewText.Show(false);
			}
			return true;
		} else if(w == marketOffers) {
			DebugMessageP2PTrader("click marketOffers");
			DebugMessageP2PTrader("try get selected item");
			selectedMarketOffer = itemService.GetSelectedMarketOffer(marketOffers);
			
			if (!selectedMarketOffer) {
				return true;
			}
			
			playerOfferForSelectedStockItem = itemService.GetPlayerSingleOffersForMarketOffer(selectedMarketOffer, playerActiveOffers);
			
			DebugMessageP2PTrader("config filds");
			playerNameOfferDetail.SetText(selectedMarketOffer.GetOwnerName());
			playerOfferMessageDetail.SetText(selectedMarketOffer.GetOfferMessage());
			
			DebugMessageP2PTrader("try set items to list");
			itemService.GetMarketOfferItemList(marketOfferItems, selectedMarketOffer);
			selectedPlayerOffers = itemService.GetPlayerOffersForMarketOffer(selectedMarketOffer, allActiveOffers);
			
			marketOfferWantToHave.ClearItems();
			playerOffers.ClearItems();
			selectedPlayerOffer = null;
			playerOfferItems.ClearItems();
			playerOfferItemAttachments.ClearItems();
			if (selectedPlayerOffers && selectedPlayerOffers.Count() > 0) {
				DebugMessageP2PTrader("offer is selected");
				itemService.GetActiveOffersForStockItem(playerOffers, selectedPlayerOffers);
			} else {
				DebugMessageP2PTrader("no offer found offer is selected");
			}
			
			marketOfferWantToHave.ClearItems();
			
			if(selectedMarketOffer.GetWantedItems().Count() > 0) {
				itemService.GetTraderStockItemList(marketOfferWantToHave, selectedMarketOffer.GetWantedItems());
			}
			
			playerOfferItemAttachments.ClearItems();
			
			offerMessageFromPlayerLabel.Show(true);
			offerPlayerLabel.Show(true);
			marketOfferWantToHaveLabel.Show(true);
			marketOfferItems.Show(true);
			marketOfferItemAtatmenchts.Show(true);
			offerItemLabel.Show(true);
			
			marketOfferItemAtatmenchts.ClearItems();
			offerItemAttachmentLabel.Show(true);
			DebugMessageP2PTrader("try ShowHideMyOfferForItem");
			ShowHideMyOfferForItem();
			return true;
		} else if(w == marketOfferItems) {
			DebugMessageP2PTrader("click marketOfferItems");
			P2PTraderStockItem currentStockItem = itemService.GetSelectedItemPlayerOffer(marketOfferItems);
			if (!currentStockItem) {
				return true;
			}
			itemService.GetMarketOfferItemAttachmentList(marketOfferItemAtatmenchts, currentStockItem);
			return true;
		} else if(w == playerOffers) {
			DebugMessageP2PTrader("click playerOffers");
			selectedPlayerOffer = itemService.GetSelectedStockItem(playerOffers);
			if (!selectedPlayerOffer) {
				return true;
			}
			itemService.GetTraderStockItemList(playerOfferItems, selectedPlayerOffer.GetOfferItems());
			buttonTakeOffer.Show(true);
			ShowHideMyOfferForItem();
			return true;
		} else if(w == playerOfferItems) {
			DebugMessageP2PTrader("click playerOfferItems");
			P2PTraderStockItem currentMyBidItem = itemService.GetSelectedItemPlayerOffer(playerOfferItems);
			if (!currentMyBidItem) {
				return true;
			}
			
			itemService.GetMarketOfferItemAttachmentList(playerOfferItemAttachments, currentMyBidItem);
			
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
			mainMenuItemPreview.Show(false);
			mainMenuItemPreviewText.Show(false);
			RefreshPlayerLists();
			return true;
		} else if(w == buttonDeleteMyOffer) {
			DebugMessageP2PTrader("click buttonDeleteMyOffer");
			if (!selectedMarketOffer) {
				DebugMessageP2PTrader("no selected selectedMarketOffer");
				return true;
			}
			
			Param2<DayZPlayer, int> paramRemovePlayerToMarketOffer = new Param2<DayZPlayer, int>(GetGame().GetPlayer(), selectedMarketOffer.GetId());
			GetGame().RPCSingleParam(paramRemovePlayerToMarketOffer.param1, P2P_TRADER_EVENT_REMOVE_OFFER, paramRemovePlayerToMarketOffer, true);
			selectedMarketOffer = null;
			selectedPlayerOffer = null;
			marketOfferItems.ClearItems();
			marketOfferItemAtatmenchts.ClearItems();
			playerOffers.ClearItems();
			playerOfferItems.ClearItems();
			playerOfferItemAttachments.ClearItems();
			mainMenuItemPreview.Show(false);
			mainMenuItemPreviewText.Show(false);
			ShowHideMyOfferForItem();
			return true;
			
		} else if(w == buttonTakeOffer && selectedPlayerOffer && selectedMarketOffer && selectedPlayerOffer.GetOwnerId() != selectedMarketOffer.GetOwnerId()) {
			DebugMessageP2PTrader("click buttonTakeOffer");
			marketOfferItems.ClearItems();
			marketOfferItemAtatmenchts.ClearItems();
			playerOffers.ClearItems();
			playerOfferItems.ClearItems();
			playerOfferItemAttachments.ClearItems();
			marketOfferWantToHave.ClearItems();
			Param3<DayZPlayer, int, int> paramTakePlayerToMarketOffer = new Param3<DayZPlayer, int, int>(GetGame().GetPlayer(), selectedPlayerOffer.GetId(), selectedMarketOffer.GetId());
			GetGame().RPCSingleParam(paramTakePlayerToMarketOffer.param1, P2P_TRADER_EVENT_TAKE_OFFER, paramTakePlayerToMarketOffer, true);
			selectedPlayerOffer = null;
			buttonDeleteMyOffer.Show(false);
			return true;
		} else if(w == buttonManageMyBids && playerActiveOffers) {
			selectedPlayerOfferBidManagement = null;
			bidManagementWidget.Show(true);
			mainMenuItemPreview.Show(false);
			mainMenuItemPreviewText.Show(false);
			if(playerActiveOffers.Count() == 0) {
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
		} else if(w == buttonCanceledBids) {
			selectedPlayerOfferBidManagement = null;
			bidManagementBidItemAttachment.ClearItems();
			bidManagementBidItems.ClearItems();
			playerOfferItemAttachments.ClearItems();
			
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
		} else if(w == buttonAcceptedBids) {
			selectedPlayerOfferBidManagement = null;
			bidManagementBidItemAttachment.ClearItems();
			bidManagementBidItems.ClearItems();
			playerOfferItemAttachments.ClearItems();
			
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
		} else if(w == buttonOpenBids) {
			bidManagementBidItemAttachment.ClearItems();
			bidManagementBidItems.ClearItems();
			playerOfferItemAttachments.ClearItems();
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
			bidManagementWidget.Show(false);
			bidManagementBids.ClearItems();
			bidManagementMarketOfferWantToHave.ClearItems();
			bidManagementMarketOfferDetailItemsBid.ClearItems();
			bidManagementMarketOfferDetailAttachmentBid.ClearItems();
			bidManagementBidItems.ClearItems();
			bidManagementBidItemAttachment.ClearItems();
			return true;
		} else if(w == bidManagementBidItems) {
			P2PTraderStockItem selectedBidItemBidManagement = itemService.GetSelectedItemPlayerOffer(bidManagementBidItems);
			if (selectedBidItemBidManagement) {
				itemService.GetMarketOfferItemAttachmentList(bidManagementBidItemAttachment, selectedBidItemBidManagement);
			}
			ShowHideBidManagementButtons();
			return true;
		} else if(w == bidManagementBids) {
			selectedPlayerOfferBidManagement = itemService.GetSelectedStockItem(bidManagementBids);
			P2PTraderPlayerMarketOffer selectedMarketOfferBitManagement;
			if (selectedPlayerOfferBidManagement) {
				foreach(P2PTraderPlayerMarketOffer marketOfferItems: marketItems) {
					if (selectedPlayerOfferBidManagement.GetPlayerToMarketOfferId() == marketOfferItems.GetId()) {
						selectedMarketOfferBitManagement = marketOfferItems;
						break;
					}
				}
				
				itemService.GetTraderStockItemList(bidManagementBidItems, selectedPlayerOfferBidManagement.GetOfferItems());
			}
			
			if (selectedMarketOfferBitManagement) {
				bidManagementMarketOfferPlayer.SetText(selectedMarketOfferBitManagement.GetOwnerName());
				bidManagementMarketOfferMessage.SetText(selectedMarketOfferBitManagement.GetOfferMessage());
				
				bidManagementMarketOfferWantToHave.ClearItems();
			
				if(selectedMarketOfferBitManagement.GetWantedItems().Count() > 0) {
					itemService.GetTraderStockItemList(bidManagementMarketOfferWantToHave, selectedMarketOfferBitManagement.GetWantedItems());
				}
				
				itemService.GetMarketOfferItemList(bidManagementMarketOfferDetailItemsBid, selectedMarketOfferBitManagement);
			
			}
			ShowHideBidManagementButtons();
			return true;
		}
		return false;
    }
	
	private void ShowHideBidManagementButtons() {
		
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
	
	}
	
	private void ShowHideMyOfferForItem() {
		if (selectedMarketOffer) {
			marketOfferWantToHave.Show(true);
			if(selectedMarketOffer.GetOwnerId() != playerId) {
				buttonDeleteMyOffer.Show(false);
				buttonTakeOffer.Show(false);
				
				if (!canTrade) {
					buttonDeleteMyBid.Show(false);
					buttonOpenCreateMyBid.Show(false);
				} else if (playerOfferForSelectedStockItem) {
					buttonDeleteMyBid.Show(true);
					buttonOpenCreateMyBid.Show(false);
				} else {
					buttonDeleteMyBid.Show(false);
					buttonOpenCreateMyBid.Show(true);
				}
				
				offerMyBidLabel.Show(false);
				offerMyBidsLabel.Show(false);
				playerOffers.Show(false);
				playerOfferItems.Show(false);
				offerMyBidAttachmentLabel.Show(false);
				playerOfferItemAttachments.Show(false);
				playerOfferItemMessage.Show(false);
				playerOfferItemMessageLabel.Show(false);
			} else {
				buttonOpenCreateMyBid.Show(false);
				buttonDeleteMyBid.Show(false);
				playerOffers.Show(true);
				playerOfferItems.Show(true);
				offerMyBidLabel.Show(true);
				offerMyBidsLabel.Show(true);
				offerMyBidAttachmentLabel.Show(true);
				playerOfferItemAttachments.Show(true);
				playerOfferItemMessage.Show(true);
				playerOfferItemMessageLabel.Show(true);
                if (selectedPlayerOffer) {
                    playerOfferItemMessage.SetText(selectedPlayerOffer.GetMessage());
                } else {
                    playerOfferItemMessage.SetText("");
                }
				if (!canTrade) {
					buttonTakeOffer.Show(false);
					buttonDeleteMyOffer.Show(false);
				} else {
					if(selectedPlayerOffer) {
						buttonTakeOffer.Show(true);
					}
					buttonDeleteMyOffer.Show(true);
				} 
			}
		
		} else {
			playerOffers.Show(false);
			playerOfferItems.Show(false);
			offerMyBidAttachmentLabel.Show(false);
			offerMyBidLabel.Show(false);
			offerMyBidsLabel.Show(false);
			playerOfferItemAttachments.Show(false);
			buttonOpenCreateMyBid.Show(false);
			buttonDeleteMyBid.Show(false);
			buttonDeleteMyOffer.Show(false);
			buttonTakeOffer.Show(false);
			marketOfferWantToHave.Show(false);
			playerOfferItemMessage.Show(false);
			playerOfferItemMessageLabel.Show(false);
		}
		
		buttonOpenCreateOffer.Show(canTrade);
	}
	
	override void OnHide()
	{
		if (!isMenuOpen) {
			return;
		}
		
		DebugMessageP2PTrader("hide action");
		super.OnHide();

		PPEffects.SetBlurMenu(0);

		GetGame().GetUIManager().ShowCursor(false);
		GetGame().GetUIManager().ShowUICursor(false);
		GetGame().GetInput().ResetGameFocus();
		GetGame().GetMission().PlayerControlEnable(true);
		GetGame().GetUIManager().Back();
		GetGame().GetMission().GetHud().Show( true );

		Close();
		isMenuOpen = false;
		GetDayZGame().Event_OnRPC.Remove(HandleEvents);
		marketOffers.ClearItems();
		marketOfferItems.ClearItems();
	 	marketOfferItemAtatmenchts.ClearItems();
		playerOfferItems.ClearItems();
		playerOfferItemAttachments.ClearItems();
		
		allActiveOffers.Clear();
		marketPlayerItems.Clear();
		marketItems.Clear();
		
		marketOfferWantToHave.ClearItems();
		selectedMarketOffer = null;
		selectedPlayerOffer = null;
		ShowHideMyOfferForItem();
		buttonOpenCreateMyBid.Show(false);
	}
	
		
	override void OnShow()
	{
		if (isMenuOpen) {
			DebugMessageP2PTrader("Menu is already open");
			return;
		}
		refreshRuns = 0;
		
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
		
		RefreshStockLists();
		RefreshPlayerLists();
		
		super.OnShow();
				
		DebugMessageP2PTrader("show action");
		
		PPEffects.SetBlurMenu(0.5);

		SetFocus(layoutRoot);
		mainMenuFilterListener.OnShow();
		
		offerMessageFromPlayerLabel.Show(false);
		buttonOpenCreateMyBid.Show(false);
		buttonDeleteMyOffer.Show(false);
		buttonTakeOffer.Show(false);
		marketOfferWantToHaveLabel.Show(false);
		offerPlayerLabel.Show(false);
		marketOfferItems.Show(false);
		marketOfferItemAtatmenchts.Show(false);
		playerOffers.Show(false);
		playerOfferItems.Show(false);
		playerOfferItemAttachments.Show(false);
		offerMyBidAttachmentLabel.Show(false);
		offerMyBidLabel.Show(false);
		offerMyBidsLabel.Show(false);
		offerItemLabel.Show(false);
		offerItemAttachmentLabel.Show(false);
		buttonDeleteMyBid.Show(false);
		createPlayerOfferWidget.Show(false);
        offerWidget.OnHide();
		marketOfferWantToHave.Show(false);
		layoutRoot.Show(true);
		bidManagementWidget.Show(false);
		buttonManageMyBids.Show(false);
		playerOfferItemMessageLabel.Show(false);
		playerOfferItemMessage.Show(false);
		buttonOpenCreateOffer.Show(canTrade);
		notInNearHint.Show(!canTrade);
		bidManagementNotInNearHint.Show(!canTrade);

		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
		GetGame().GetUIManager().ShowUICursor(true);
		GetGame().GetUIManager().ShowCursor(true);
		GetGame().GetInput().ChangeGameFocus( 1 );
		GetGame().GetMission().GetHud().Show( false );
		isMenuOpen = true;
	}
	
	 void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (IsServerP2PTrader()) {
            return;
        } 
		if (rpc_type == P2P_TRADER_EVENT_GET_PLAYER_ITEMS_RESPONSE) {
			refreshRuns = refreshRuns - 1;
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_GET_PLAYER_ITEMS_RESPONSE");
            Param1<ref array<ref P2PTraderItem>> parameterPlayerItems;
            if (ctx.Read(parameterPlayerItems)) {
                offerWidget.OnGetPlayerItems(parameterPlayerItems.param1);
                playerBidWidget.OnGetPlayerItems(parameterPlayerItems.param1);
			}
		} else if (rpc_type == P2P_TRADER_EVENT_GET_STOCK_RESPONSE) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_GET_STOCK_RESPONSE");
            Param1<ref array<ref P2PTraderPlayerMarketOffer>> parameterStock;
            if (ctx.Read(parameterStock)) {
				DebugMessageP2PTrader("got market items: " + parameterStock.param1.Count().ToString());
				
				marketItems.Clear();
				marketPlayerItems.Clear();
				array<ref P2PTraderPlayerMarketOffer> stock = parameterStock.param1;

				if (stock && stock.Count()> 0){
					foreach(P2PTraderPlayerMarketOffer marketOfferItems: stock) {
						if (marketOfferItems.GetOwnerId() == playerId) {
							DebugMessageP2PTrader("added to player list");
							marketPlayerItems.Insert(marketOfferItems);
						}
						marketItems.Insert(marketOfferItems);
					}
				} else if (stock && stock.Count() == 0) {
					DebugMessageP2PTrader("empty stock recived");
				} else {
					DebugMessageP2PTrader("no stock recived");
				}
				
				itemService.InitMarketItems(marketItems);
				
				mainMenuFilterListener.OnGetStockEvent(marketItems, marketPlayerItems);
			}
		} else if (rpc_type == P2P_TRADER_EVENT_GET_ALL_BID_OFFERS_RESPONSE) {
			refreshRuns = refreshRuns - 1;
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_GET_ALL_BID_OFFERS_RESPONSE");
            Param1<ref array<ref P2PTraderPlayerPlayerOffer>> parameterPlayerBids;
            if (ctx.Read(parameterPlayerBids)) {
                allActiveOffers = parameterPlayerBids.param1;
			}
			playerActiveOffers = new array<ref P2PTraderPlayerPlayerOffer>;
			
			foreach(P2PTraderPlayerPlayerOffer activeOffer: allActiveOffers) {
				if ( playerId == activeOffer.GetOwnerId()) {
					playerActiveOffers.Insert(activeOffer);
				}
			}
			
			if(bidManagementWidget.IsVisible() && playerActiveOffers.Count() == 0 && P2PTraderStock.INACTIVE_OFFER == bidFilterBidManagement) {
				bidManagementBidHint.Show(true);
				bidManagementBids.Show(false);
			} else if(bidManagementWidget.IsVisible() && playerActiveOffers.Count() > 0 && P2PTraderStock.INACTIVE_OFFER == bidFilterBidManagement){
				itemService.GetActiveOffersForStockItem(bidManagementBids, playerActiveOffers);
				bidManagementBidHint.Show(false);
				bidManagementBids.Show(true);
			}
			
			buttonManageMyBids.Show(true);
			
		} else if (rpc_type == P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS_RESPONSE || rpc_type == P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE || rpc_type == P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE || rpc_type == P2P_TRADER_EVENT_NEW_OFFER_RESPONSE || rpc_type == P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE) {
			DebugMessageP2PTrader("recive EVENT and Refresh lists");
           	RefreshPlayerLists();
			RefreshStockLists();
			if (rpc_type == P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE) {
				selectedMarketOffer = null;
				selectedPlayerOffer = null;
				selectedPlayerOffers = null;
			}
			Param1<string> parameterResponse;
            if (ctx.Read(parameterResponse)) {
				message.SetText(parameterResponse.param1);
			}
			ShowHideMyOfferForItem();
			
		} else if (rpc_type == P2P_TRADER_EVENT_RESPONSE_ERROR) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_RESPONSE_ERROR");
            Param1<string> parameterError;
            if (ctx.Read(parameterError)) {
				message.SetText(parameterError.param1);
				offerWidget.OnHide();
				createPlayerOfferWidget.Show(false);
			}
		} else if (rpc_type == P2P_TRADER_EVENT_GET_PLAYER_ACCEPTED_INACTIVE_OFFERS_RESPONSE) {
			refreshRuns = refreshRuns - 1;
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_GET_PLAYER_ACCEPTED_INACTIVE_OFFERS_RESPONSE");
            Param2<ref array<ref P2PTraderPlayerPlayerOffer>, ref array<ref P2PTraderPlayerPlayerOffer>> parameterOffers;
            if (ctx.Read(parameterOffers)) {
				playerInactiveOffers = parameterOffers.param1;
				playerAcceptedOffers = parameterOffers.param2;
				
				if (playerInactiveOffers) {
					DebugMessageP2PTrader("playerInactiveOffers == null");
				} else {
					DebugMessageP2PTrader("playerInactiveOffers:" + playerInactiveOffers.Count());
				}
				if (playerAcceptedOffers) {
					DebugMessageP2PTrader("playerAcceptedOffers == null");
				} else {
					DebugMessageP2PTrader("playerAcceptedOffers:" + playerAcceptedOffers.Count());
				}
								
				if (bidManagementWidget.IsVisible()) {
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
		}
	}
	
	void CloseMenu(){
		DebugMessageP2PTrader("check is open");
		if(isMenuOpen){
			if (offerWidget.IsWidgetVisible()) {
				offerWidget.OnHide();
			} else if(createPlayerOfferWidget.IsVisible()) {
				createPlayerOfferWidget.Show(false);
			} else if(bidManagementWidget.IsVisible()) {
				bidManagementWidget.Show(false);
			} else {
				DebugMessageP2PTrader("try close menu");
				SetFocus(NULL);
				OnHide();
				layoutRoot.Show(false);
				
				isMenuOpen = false;
			}
			
		}	
	}
	
	bool IsInitialized() {
		return !!layoutRoot;
	}
	
	private void RefreshPlayerLists() {
		Param1<DayZPlayer> paramGetPlayerItems = new Param1<DayZPlayer>(player);
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_PLAYER_ITEMS, paramGetPlayerItems, true);
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_ALL_BID_OFFERS, paramGetPlayerItems, true);
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_PLAYER_ACCEPTED_INACTIVE_OFFERS, paramGetPlayerItems, true);
		refreshRuns = 3;
	}
	
	private void RefreshStockLists() {
		Param1<DayZPlayer> paramGetPlayerItems = new Param1<DayZPlayer>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_STOCK, paramGetPlayerItems, true);
	}

}