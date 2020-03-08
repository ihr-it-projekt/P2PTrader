class P2PTraderMenu extends UIScriptedMenu
{
	private DayZPlayer player;
	private string playerId;
	private P2PTraderConfig config;
	private P2PTraderPlayerMarketOffer selectedMarketOffer;
	private ref array<ref P2PTraderPlayerPlayerOffer> selectedPlayerOffers;
	private P2PTraderPlayerPlayerOffer selectedPlayerOffer;
	private P2PTraderPlayerPlayerOffer selectedPlayerOfferBidManagement;
	private ref ItemService itemService;
	private ref array<ref P2PTraderPlayerMarketOffer> marketItems;
	private ref array<ref P2PTraderPlayerMarketOffer> marketPlayerItems;
	private ref array<ref P2PTraderPlayerPlayerOffer> allActiveOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerActiveOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerInactiveOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerAcceptedOffers;
	private P2PTraderPlayerPlayerOffer playerOfferForSelectedStockItem;
	private Widget createOfferWidget;
	private Widget createPlayerOfferWidget;
	private Widget bidManagementWidget;
	private string bidFilterBidManagement = P2PTraderStock.OPEN_OFFER;
	private bool canTrade = false;
	bool isMenuOpen = false;
	int refreshRuns = 0;

    private ButtonWidget cancel;
	private ButtonWidget buttonMyOffers;
	private ButtonWidget buttonTakeOffer;
	private ButtonWidget buttonAllOffers;
	private ButtonWidget buttonDeleteMyOffer;
	private ButtonWidget buttonOpenCreateMyBid;
	private ButtonWidget buttonOpenCreateOffer;
	private ButtonWidget buttonSearchMarket;
	private ButtonWidget buttonManageMyBids;
	private EditBoxWidget inputSearchMarket;
	private TextListboxWidget marketOffers;
	private TextListboxWidget marketOfferItems;
	private TextListboxWidget marketOfferItemAtatmenchts;
	private TextListboxWidget marketOfferWantToHave;
	private TextListboxWidget playerOfferItems;
	private TextListboxWidget playerOffers;
	private TextListboxWidget playerOfferItemAttachments;
	private MultilineTextWidget playerOfferMessageDetail;
	private TextWidget playerNameOfferDetail;
	private TextWidget playerNameBidDetail;
	private TextWidget offerPlayerLabel;
	private TextWidget offerMessageFromPlayerLabel;
	private TextWidget offerItemLabel;
	private TextWidget offerItemAttachmentLabel;
	private TextWidget offerMyBidAttachmentLabel;
	private TextWidget offerMyBidsLabel;
	private TextWidget offerMyBidLabel;
	private TextWidget marketOfferWantToHaveLabel;
	private TextWidget playerOfferItemMessageLabel;
	
	private ButtonWidget buttonSearchOffer;
	private EditBoxWidget inputSearchOffer;
	private TextListboxWidget tradeableItemsOffer;
	private ButtonWidget buttonCloseCreateOffer;
	private ButtonWidget buttonCreateCreateOffer;
	private ButtonWidget buttonCreateClosePlayerOffer;
	private ButtonWidget buttonCreateCreatePlayerOffer;
	private TextListboxWidget playerWhantToHaveOffer;
	private TextListboxWidget playerInventoryItemsOffer;
	private TextListboxWidget playerItemsOfferOffer;
	private TextListboxWidget playerInventoryItemsPlayerOffer;
	private TextListboxWidget playerItemsOfferPlayerOffer;
	private TextListboxWidget offerDetailItemsBid;
	private TextListboxWidget detailAttechmentBid;
	private EditBoxWidget playerTextOffer;
	private EditBoxWidget playerTextPlayerOffer;
	private MultilineTextWidget message;
	private MultilineTextWidget notInNearHint;
	private MultilineTextWidget bidManagementNotInNearHint;
	private MultilineTextWidget playerOfferMessageDetailBid;
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
		
		itemService = new ItemService(config);
		
		player = GetGame().GetPlayer();
		playerId = player.GetIdentity().GetId();

        layoutRoot = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/mainMenu.layout");
		
        cancel = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "cancel" ));
        buttonOpenCreateOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonOpenCreateOffer" ));
        buttonSearchMarket = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonSearchMarket" ));
        buttonManageMyBids = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonManageMyBids" ));
        buttonDeleteMyOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonDeleteMyOffer" ));
        buttonMyOffers = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonMyOffers" ));
        buttonTakeOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonTakeOffer" ));
        buttonAllOffers = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonAllOffers" ));
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
		inputSearchMarket = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("inputSearchMarket"));
		notInNearHint = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("notInNearHint"));
		message = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("message"));
		playerOfferItemMessage = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("playerOfferItemMessage"));
		
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(cancel,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonOpenCreateOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonSearchMarket,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonManageMyBids,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonDeleteMyOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonAllOffers,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonMyOffers,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonTakeOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonOpenCreateMyBid,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(marketOffers,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(marketOfferItems,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(playerOfferItems,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(playerOffers,  this, "OnClick");
		
		createOfferWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/offer.layout");
		createPlayerOfferWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/bid.layout");
		bidManagementWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/bidManagement.layout");
        
		
		//Start offer widget
        tradeableItemsOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("tradeableItemsOffer"));
        playerWhantToHaveOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("playerWhantToHaveOffer"));
        playerInventoryItemsOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("playerInventoryItemsOffer"));
        playerItemsOfferOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("playerItemsOfferOffer"));
        playerTextOffer = EditBoxWidget.Cast(createOfferWidget.FindAnyWidget("playerTextOffer"));
        

        buttonCloseCreateOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonCloseCreateOffer"));
        buttonCreateCreateOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonCreateCreateOffer"));
        buttonSearchOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonSearchOffer"));

        inputSearchOffer = EditBoxWidget.Cast(createOfferWidget.FindAnyWidget("inputSearchOffer"));

        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCloseCreateOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonSearchOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCreateCreateOffer,  this, "OnClick");

        WidgetEventHandler.GetInstance().RegisterOnDoubleClick(tradeableItemsOffer,  this, "OnDoubleClick");
        WidgetEventHandler.GetInstance().RegisterOnDoubleClick(playerWhantToHaveOffer,  this, "OnDoubleClick");
        WidgetEventHandler.GetInstance().RegisterOnDoubleClick(playerInventoryItemsOffer,  this, "OnDoubleClick");
        WidgetEventHandler.GetInstance().RegisterOnDoubleClick(playerItemsOfferOffer,  this, "OnDoubleClick");

		layoutRoot.AddChild(createOfferWidget);
		//End offer widget
		//start player bid widget
        buttonCreateCreatePlayerOffer = ButtonWidget.Cast(createPlayerOfferWidget.FindAnyWidget("buttonCreateCreatePlayerOffer"));
        buttonCreateClosePlayerOffer = ButtonWidget.Cast(createPlayerOfferWidget.FindAnyWidget("buttonCreateClosePlayerOffer"));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCreateCreatePlayerOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCreateClosePlayerOffer,  this, "OnClick");
		
        playerNameBidDetail = TextWidget.Cast( createPlayerOfferWidget.FindAnyWidget( "playerNameBidDetail" ));
        playerOfferMessageDetailBid = MultilineTextWidget.Cast( createPlayerOfferWidget.FindAnyWidget( "playerOfferMessageDetailBid" ));
		
        playerTextPlayerOffer = EditBoxWidget.Cast(createPlayerOfferWidget.FindAnyWidget("playerTextPlayerOffer"));
        playerInventoryItemsPlayerOffer = TextListboxWidget.Cast(createPlayerOfferWidget.FindAnyWidget("playerInventoryItemsPlayerOffer"));
        playerItemsOfferPlayerOffer = TextListboxWidget.Cast(createPlayerOfferWidget.FindAnyWidget("playerItemsOfferPlayerOffer"));
        detailAttechmentBid = TextListboxWidget.Cast(createPlayerOfferWidget.FindAnyWidget("detailAttechmentBid"));
        offerDetailItemsBid = TextListboxWidget.Cast(createPlayerOfferWidget.FindAnyWidget("offerDetailItemsBid"));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(offerDetailItemsBid,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnDoubleClick(playerInventoryItemsPlayerOffer,  this, "OnDoubleClick");
        WidgetEventHandler.GetInstance().RegisterOnDoubleClick(playerItemsOfferPlayerOffer,  this, "OnDoubleClick");

        //End player bid widget
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

        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(bidManagementBids,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(bidManagementMarketOfferDetailItemsBid,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(bidManagementBidItems,  this, "OnClick");
		
		bidManagementWidget.Show(false);
		//end player offers layout

        layoutRoot.Show(false);

		itemService.AddTradeableItemsToWidget(tradeableItemsOffer, "");
		
		
		
		return layoutRoot;
    }
	
	void SetCanTrade(bool canTrade) {
		this.canTrade = canTrade;
	}

    override bool OnClick( Widget w, int x, int y, int button )	{
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
			playerItemsOfferPlayerOffer.ClearItems();
			
			playerTextPlayerOffer.SetText("");
			playerNameBidDetail.SetText(selectedMarketOffer.GetOwnerName());
			playerOfferMessageDetailBid.SetText(selectedMarketOffer.GetOfferMessage());
			detailAttechmentBid.ClearItems();
			itemService.GetMarketOfferItemList(offerDetailItemsBid, selectedMarketOffer);
			createPlayerOfferWidget.Show(true);
			return true;
		} else if(w == buttonOpenCreateOffer) {
			DebugMessageP2PTrader("click buttonOpenCreateOffer");
			if (config.traderConfigParams.maxMarketOffersPerPlayer == marketPlayerItems.Count()) {
				message.SetText("#you_reach_max_bid_offers_per_player");
			} else {
				createOfferWidget.Show(true);
			}
			return true;
		} else if(w == buttonSearchOffer) {
			DebugMessageP2PTrader("click buttonSearchOffer");
			itemService.AddTradeableItemsToWidget(tradeableItemsOffer, inputSearchOffer.GetText());
			return true;
		} else if(w == buttonSearchMarket) {
			DebugMessageP2PTrader("click buttonSearchMarket");
			itemService.GetMarketItemList(marketOffers, marketItems, inputSearchMarket.GetText());
			return true;
		} else if(w == buttonCreateCreateOffer) {
			DebugMessageP2PTrader("Click on create offer");
			messageText = itemService.CreateOffer(player, playerItemsOfferOffer, playerWhantToHaveOffer, playerTextOffer.GetText());
			message.SetText(messageText);
			
			playerItemsOfferOffer.ClearItems();
			playerWhantToHaveOffer.ClearItems();
			createOfferWidget.Show(false);
			return true;
		} else if(w == buttonCreateCreatePlayerOffer) {
			DebugMessageP2PTrader("Click on create player offer");
			messageText = itemService.CreateOfferToPlayer(player, playerItemsOfferPlayerOffer, selectedMarketOffer.GetId(), playerTextPlayerOffer.GetText());
			message.SetText(messageText);

			createPlayerOfferWidget.Show(false);
			return true;
		} else if(w == buttonCloseCreateOffer) {
			DebugMessageP2PTrader("click buttonCloseCreateOffer");
			playerItemsOfferOffer.ClearItems();
			playerWhantToHaveOffer.ClearItems();
			createOfferWidget.Show(false);
			return true;
		} else if(w == buttonCreateClosePlayerOffer) {
			DebugMessageP2PTrader("click buttonCreateClosePlayerOffer");
            createPlayerOfferWidget.Show(false);
			return true;
		} else if(w == marketOffers) {
			DebugMessageP2PTrader("click marketOffers");
			DebugMessageP2PTrader("try get selected item");
			selectedMarketOffer = itemService.GetSelectedMarketOffer(marketOffers);
			
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
		} else if(w == offerDetailItemsBid) {
			DebugMessageP2PTrader("click offerDetailItemsBid");
			P2PTraderStockItem currentOfferDetailItem = itemService.GetSelectedItemPlayerOffer(offerDetailItemsBid);
			if (!currentOfferDetailItem) {
				return true;
			}
			itemService.GetMarketOfferItemAttachmentList(detailAttechmentBid, currentOfferDetailItem);
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
		} else if(w == buttonMyOffers) {
			DebugMessageP2PTrader("click buttonMyOffers");
			buttonMyOffers.Show(false);
			buttonAllOffers.Show(true);
			
			itemService.GetMarketItemList(marketOffers, marketPlayerItems, inputSearchMarket.GetText());
			return true;
		} else if(w == buttonAllOffers) {
			DebugMessageP2PTrader("click buttonAllOffers");
			buttonMyOffers.Show(true);
			buttonAllOffers.Show(false);
			
			itemService.GetMarketItemList(marketOffers, marketItems, inputSearchMarket.GetText());
			return true;
		} else if(w == buttonManageMyBids && playerActiveOffers) {
			selectedPlayerOfferBidManagement = null;
			bidManagementWidget.Show(true);
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
	
	override bool OnDoubleClick(Widget w, int x, int y, int button ) {
		bool actionRuns = super.OnClick(w, x, y, button);
		if (actionRuns) {
            return actionRuns;
        } else if (w == tradeableItemsOffer){
            DebugMessageP2PTrader("double click tradeableItemsOffer");
			itemService.MoveItemFromListWidgetToListWidget(tradeableItemsOffer, playerWhantToHaveOffer, false);
			
            return true;
        } else if (w == playerWhantToHaveOffer){
            DebugMessageP2PTrader("double click playerWhantToHaveOffer");
			itemService.MoveItemFromListWidgetToListWidget(playerWhantToHaveOffer, null);
			
            return true;
        } else if (w == playerInventoryItemsOffer){
            DebugMessageP2PTrader("double click playerInventoryItemsOffer");
			itemService.MoveItemFromListWidgetToListWidget(playerInventoryItemsOffer, playerItemsOfferOffer);
			
            return true;
        } else if (w == playerItemsOfferOffer){
            DebugMessageP2PTrader("double click playerItemsOfferOffer");
			itemService.MoveItemFromListWidgetToListWidget(playerItemsOfferOffer, playerInventoryItemsOffer);
			
            return true;
        } else if (w == playerInventoryItemsPlayerOffer){
            DebugMessageP2PTrader("double click playerInventoryItemsPlayerOffer");
			itemService.MoveItemFromListWidgetToListWidget(playerInventoryItemsPlayerOffer, playerItemsOfferPlayerOffer);

            return true;
        } else if (w == playerItemsOfferPlayerOffer){
            DebugMessageP2PTrader("double click playerItemsOfferPlayerOffer");
			itemService.MoveItemFromListWidgetToListWidget(playerItemsOfferPlayerOffer, playerInventoryItemsPlayerOffer);

            return true;
        }
		
		return false;
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
		playerInventoryItemsOffer.ClearItems();
		marketOffers.ClearItems();
		marketOfferItems.ClearItems();
	 	marketOfferItemAtatmenchts.ClearItems();
		playerOfferItems.ClearItems();
		playerOfferItemAttachments.ClearItems();
		playerWhantToHaveOffer.ClearItems();
		playerInventoryItemsOffer.ClearItems();
		playerItemsOfferOffer.ClearItems();
		playerInventoryItemsPlayerOffer.ClearItems();
		playerItemsOfferPlayerOffer.ClearItems();
		tradeableItemsOffer.ClearItems();
		
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
		
		RefrechStockLists();
		RefreshPlayerLists();
		
		super.OnShow();
				
		DebugMessageP2PTrader("show action");
		
		PPEffects.SetBlurMenu(0.5);

		SetFocus(layoutRoot);
		
		offerMessageFromPlayerLabel.Show(false);
		buttonOpenCreateMyBid.Show(false);
		buttonAllOffers.Show(false);
		buttonDeleteMyOffer.Show(false);
		buttonMyOffers.Show(true);
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
		createOfferWidget.Show(false);
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
                array<ref P2PTraderItem> playerItems = parameterPlayerItems.param1;
				itemService.GetPlayerItemList(playerInventoryItemsOffer, playerItems);
				itemService.GetPlayerItemList(playerInventoryItemsPlayerOffer, playerItems);
			}
		} else if (rpc_type == P2P_TRADER_EVENT_GET_STOCK_RESPONSE) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_GET_STOCK_RESPONSE");
            Param1<ref array<ref P2PTraderPlayerMarketOffer>> parameterStock;
            if (ctx.Read(parameterStock)) {
                marketItems = parameterStock.param1;
				
				DebugMessageP2PTrader("got market items: " + marketItems.Count().ToString());
				
				marketPlayerItems = new ref array<ref P2PTraderPlayerMarketOffer>;
				
				foreach(P2PTraderPlayerMarketOffer marketOfferItems: marketItems) {
					if (marketOfferItems.GetOwnerId() == playerId) {
						DebugMessageP2PTrader("added to player list");
						marketPlayerItems.Insert(marketOfferItems);
					}
				}
				
				itemService.GetMarketItemListInit(marketOffers, marketItems);
				
				if (!buttonMyOffers.IsVisible()) {
					itemService.GetMarketItemList(marketOffers, marketPlayerItems, inputSearchMarket.GetText());
				}
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
			RefrechStockLists();
			if (rpc_type == P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE) {
				selectedMarketOffer = null;
				selectedPlayerOffer = null;
				selectedPlayerOffers = null;
			}
			ShowHideMyOfferForItem();
			
		} else if (rpc_type == P2P_TRADER_EVENT_RESPONSE_ERROR) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_RESPONSE_ERROR");
            Param1<string> parameterError;
            if (ctx.Read(parameterError)) {
				message.SetText(parameterError.param1);
				createOfferWidget.Show(false);
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
			if (createOfferWidget.IsVisible()) {
				createOfferWidget.Show(false);
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
	
	private void RefrechStockLists() {
		Param1<DayZPlayer> paramGetPlayerItems = new Param1<DayZPlayer>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_STOCK, paramGetPlayerItems, true);
	}

}