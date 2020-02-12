class P2PTraderMenu extends UIScriptedMenu
{
	private DayZPlayer player;
	private PlayerIdentity playerIdent;
	private string playerId;
	private P2PTraderConfig config;
	private P2PTraderPlayerMarketOffer selectedItem;
	private P2PTraderPlayerPlayerOffer selectedOffer;
	private ref ItemService itemService;
	private ref array<ref P2PTraderPlayerMarketOffer> marketItems;
	private ref array<ref P2PTraderPlayerMarketOffer> marketPlayerItems;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> inactivePlayerOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> acceptedPlayerOffers;
	private Widget createOfferWidget;
	private Widget createPlayerOfferWidget;
	bool isMenuOpen = false;

    private ButtonWidget cancel;
	private ButtonWidget buttonMyOffers;
	private ButtonWidget buttonTakeOffer;
	private ButtonWidget buttonAllOffers;
	private ButtonWidget buttonDeleteMyBid;
	private ButtonWidget buttonDeleteMyOffer;
	private ButtonWidget buttonOpenCreateMyBid;
	private ButtonWidget buttonOpenCreateOffer;
	private ButtonWidget buttonSearchMarket;
	private EditBoxWidget inputSearchMarket;
	private TextListboxWidget stockItems;
	private TextListboxWidget offerDetailItems;
	private TextListboxWidget detailAttechment;
	private TextListboxWidget offerMyBidItems;
	private TextListboxWidget offerMyBidItemsAttachments;
	private MultilineTextWidget playerOfferMessageDetail;
	private TextWidget playerNameOfferDetail;
	private TextWidget playerNameBidDetail;
	private TextWidget offerPlayerLabel;
	private TextWidget offerMessageFromPlayerLabel;
	private TextWidget offerItemLabel;
	private TextWidget offerItemAttachmentLabel;
	private TextWidget offerMyBidAttachmentLabel;
	private TextWidget offerMyBidLabel;
	
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
	private MultilineTextWidget playerOfferMessageDetailBid;
	
	
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
		playerIdent = player.GetIdentity();
		playerId = playerIdent.GetPlainId();

        layoutRoot = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/mainMenu.layout");

        cancel = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "cancel" ));
        buttonOpenCreateOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonOpenCreateOffer" ));
        buttonSearchMarket = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonSearchMarket" ));
        buttonDeleteMyBid = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonDeleteMyBid" ));
        buttonDeleteMyOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonDeleteMyOffer" ));
        buttonMyOffers = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonMyOffers" ));
        buttonTakeOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonTakeOffer" ));
        buttonAllOffers = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonAllOffers" ));
        buttonOpenCreateMyBid = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonOpenCreateMyBid" ));
        stockItems = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "stockItems" ));
        offerDetailItems = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "offerDetailItems" ));
        detailAttechment = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "detailAttechment" ));
        offerMyBidItems = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "offerMyBidItems" ));
        offerMyBidItemsAttachments = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "offerMyBidItemsAttachments" ));
        playerNameOfferDetail = TextWidget.Cast( layoutRoot.FindAnyWidget( "playerNameOfferDetail" ));
        offerPlayerLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerPlayerLabel" ));
        offerItemAttachmentLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerItemAttachmentLabel" ));
        offerItemLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerItemLabel" ));
        offerMessageFromPlayerLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerMessageFromPlayerLabel" ));
        offerMyBidAttachmentLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerMyBidAttachmentLabel" ));
        offerMyBidLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerMyBidLabel" ));
        playerOfferMessageDetail = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "playerOfferMessageDetail" ));
		inputSearchMarket = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("inputSearchMarket"));
		
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(cancel,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonOpenCreateOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonSearchMarket,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonDeleteMyBid,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonDeleteMyOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonAllOffers,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonMyOffers,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonTakeOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(stockItems,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(offerDetailItems,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(offerMyBidItems,  this, "OnClick");
		
		createOfferWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/offer.layout");
		createPlayerOfferWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/bid.layout");
        
		
		//Start offer widget
        tradeableItemsOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("tradeableItemsOffer"));
        playerWhantToHaveOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("playerWhantToHaveOffer"));
        playerInventoryItemsOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("playerInventoryItemsOffer"));
        playerItemsOfferOffer = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("playerItemsOfferOffer"));
        playerTextOffer = EditBoxWidget.Cast(createOfferWidget.FindAnyWidget("playerTextOffer"));
        message = MultilineTextWidget.Cast(createOfferWidget.FindAnyWidget("message"));

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
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(offerDetailItemsBid,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnDoubleClick(playerInventoryItemsPlayerOffer,  this, "OnDoubleClick");
        WidgetEventHandler.GetInstance().RegisterOnDoubleClick(playerItemsOfferPlayerOffer,  this, "OnDoubleClick");

        //End player bid widget

        layoutRoot.Show(false);

		itemService.AddTradeableItemsToWidget(tradeableItemsOffer, "");
		
		return layoutRoot;
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
        } else if(w == buttonOpenCreateMyBid && selectedOffer) {
			playerItemsOfferPlayerOffer.ClearItems();
			
			playerTextPlayerOffer.SetText("");
			playerNameBidDetail.SetText(selectedOffer.GetOwnerName());
			playerOfferMessageDetailBid.SetText(selectedOffer.GetMessage());
			detailAttechmentBid.ClearItems();
			itemService.GetPlayerOfferItemList(offerDetailItemsBid, selectedOffer);
			createPlayerOfferWidget.Show(true);
		} else if(w == buttonOpenCreateOffer) {
			createOfferWidget.Show(true);
		} else if(w == buttonSearchOffer) {
			itemService.AddTradeableItemsToWidget(tradeableItemsOffer, inputSearchOffer.GetText());
		} else if(w == buttonSearchMarket) {
			itemService.GetMarketItemList(stockItems, marketItems, inputSearchMarket.GetText());
		} else if(w == buttonCreateCreateOffer) {
			DebugMessageP2PTrader("Click on create offer");
			messageText = itemService.CreateOffer(player, playerItemsOfferOffer, playerWhantToHaveOffer, playerTextOffer.GetText());
			
			createOfferWidget.Show(false);
		} else if(w == buttonCreateCreatePlayerOffer) {
			DebugMessageP2PTrader("Click on create player offer");
			messageText = itemService.CreateOfferToPlayer(player, playerItemsOfferPlayerOffer, selectedItem.GetId(), playerTextPlayerOffer.GetText());

			createPlayerOfferWidget.Show(false);
		} else if(w == buttonCloseCreateOffer) {
			createOfferWidget.Show(false);
		} else if(w == buttonCreateClosePlayerOffer) {
            createPlayerOfferWidget.Show(false);
		} else if(w == stockItems) {
			selectedItem = itemService.GetSelectedMarketOffer(stockItems);
			
			playerNameOfferDetail.SetText(selectedItem.GetOwnerName());
			playerOfferMessageDetail.SetText(selectedItem.GetOfferMessage());
			itemService.GetMarketOfferItemList(offerDetailItems, selectedItem);
			
			offerMessageFromPlayerLabel.Show(true);
			offerPlayerLabel.Show(true);
			offerDetailItems.Show(true);
			detailAttechment.Show(true);
			offerItemLabel.Show(true);
			offerItemAttachmentLabel.Show(true);
			
			ShowHideMyOfferForItem();
		} else if(w == offerDetailItems) {
			P2PTraderStockItem currentStockItem = itemService.GetSelectedStockItem(offerDetailItems);
			itemService.GetMarketOfferItemAttachmentList(detailAttechment, currentStockItem);
		} else if(w == offerMyBidItems) {
			P2PTraderStockItem currentMyBidItem = itemService.GetSelectedStockItem(offerMyBidItems);
			itemService.GetMarketOfferItemAttachmentList(offerMyBidItemsAttachments, currentMyBidItem);
		} else if(w == offerDetailItemsBid) {
			P2PTraderStockItem currentMyBidItemBidView = itemService.GetSelectedStockItem(offerDetailItemsBid);
			itemService.GetMarketOfferItemAttachmentList(detailAttechmentBid, currentMyBidItemBidView);
		} else if(w == buttonDeleteMyBid && selectedOffer) {
			Param2<DayZPlayer, int> paramRemovePlayerToPlayerOffer = new Param2<DayZPlayer, int>(GetGame().GetPlayer(), selectedOffer.GetId());
			GetGame().RPCSingleParam(paramRemovePlayerToPlayerOffer.param1, P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS, paramRemovePlayerToPlayerOffer, true);
			buttonDeleteMyBid.Show(false);
		} else if(w == buttonDeleteMyOffer && selectedOffer) {
			Param2<DayZPlayer, int> paramRemovePlayerToMarketOffer = new Param2<DayZPlayer, int>(GetGame().GetPlayer(), selectedOffer.GetId());
			GetGame().RPCSingleParam(paramRemovePlayerToMarketOffer.param1, P2P_TRADER_EVENT_REMOVE_OFFER, paramRemovePlayerToMarketOffer, true);
			buttonDeleteMyOffer.Show(false);
		} else if(w == buttonTakeOffer && selectedOffer && selectedItem && (P2P_TRADER_DEBUG || selectedOffer.GetOwnerId() != selectedItem.GetOwnerId())) {
			Param3<DayZPlayer, int, int> paramTakePlayerToMarketOffer = new Param3<DayZPlayer, int, int>(GetGame().GetPlayer(), selectedOffer.GetId(), selectedItem.GetId());
			GetGame().RPCSingleParam(paramTakePlayerToMarketOffer.param1, P2P_TRADER_EVENT_TAKE_OFFER, paramTakePlayerToMarketOffer, true);
			buttonDeleteMyOffer.Show(false);
		} else if(w == buttonMyOffers) {
			buttonMyOffers.Show(false);
			buttonAllOffers.Show(true);
			
			itemService.GetMarketItemList(stockItems, marketPlayerItems, inputSearchMarket.GetText());
		} else if(w == buttonAllOffers) {
			buttonMyOffers.Show(true);
			buttonAllOffers.Show(false);
			
			itemService.GetMarketItemList(stockItems, marketItems, inputSearchMarket.GetText());
		}
		
		if (messageText != "") {
		    message.SetText(messageText);
		} 
		

        return false;
    }
	
	private void ShowHideMyOfferForItem() {
		if (selectedItem) {
			selectedOffer = itemService.GetPlayerOffer(selectedItem, playerOffers);
			
			if (selectedOffer) {
				itemService.GetPlayerOfferItemList(offerMyBidItems, selectedOffer);
				offerMyBidItemsAttachments.ClearItems();
				
				offerMyBidItems.Show(true);
				offerMyBidAttachmentLabel.Show(true);
				offerMyBidLabel.Show(true);
				offerMyBidItemsAttachments.Show(true);
				buttonDeleteMyBid.Show(true);
				buttonOpenCreateMyBid.Show(false);
				
				if (P2P_TRADER_DEBUG || selectedItem.GetOwnerId() != playerId) {
					buttonOpenCreateMyBid.Show(true);
					buttonDeleteMyOffer.Show(false);
				} else {
					buttonDeleteMyOffer.Show(true);
				}
				
			} else {
				offerMyBidItems.Show(false);
				offerMyBidAttachmentLabel.Show(false);
				offerMyBidLabel.Show(false);
				offerMyBidItemsAttachments.Show(false);
				buttonDeleteMyBid.Show(false);
				buttonDeleteMyOffer.Show(false);
			}
		}
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
		stockItems.ClearItems();
		offerDetailItems.ClearItems();
	 	detailAttechment.ClearItems();
		offerMyBidItems.ClearItems();
		offerMyBidItemsAttachments.ClearItems();
		playerWhantToHaveOffer.ClearItems();
		playerInventoryItemsOffer.ClearItems();
		playerItemsOfferOffer.ClearItems();
		playerInventoryItemsPlayerOffer.ClearItems();
		playerItemsOfferPlayerOffer.ClearItems();
		tradeableItemsOffer.ClearItems();
		
		playerOffers.Clear();
		marketPlayerItems.Clear();
		marketItems.Clear();
		acceptedPlayerOffers.Clear();
		inactivePlayerOffers.Clear();
		selectedItem = null;
		selectedOffer = null;
		ShowHideMyOfferForItem();
		buttonOpenCreateMyBid.Show(false);
	}
	
		
	override void OnShow()
	{
		if (isMenuOpen) {
			DebugMessageP2PTrader("Menu is already open");
			return;
		}
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
		
		RefrechStockLists();
		RefrechPlayerLists();
		
		super.OnShow();
				
		DebugMessageP2PTrader("show action");
		
		PPEffects.SetBlurMenu(0.5);

		SetFocus(layoutRoot);
		
		offerMessageFromPlayerLabel.Show(false);
		buttonOpenCreateMyBid.Show(false);
		buttonAllOffers.Show(true);
		buttonDeleteMyOffer.Show(false);
		buttonMyOffers.Show(false);
		offerPlayerLabel.Show(false);
		offerDetailItems.Show(false);
		detailAttechment.Show(false);
		offerMyBidItems.Show(false);
		offerMyBidItemsAttachments.Show(false);
		offerMyBidAttachmentLabel.Show(false);
		offerMyBidLabel.Show(false);
		offerItemLabel.Show(false);
		offerItemAttachmentLabel.Show(false);
		buttonMyOffers.Show(false);
		buttonDeleteMyBid.Show(false);
		createPlayerOfferWidget.Show(false);
		createOfferWidget.Show(false);
		layoutRoot.Show(true);

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
				
				marketPlayerItems = new ref array<ref P2PTraderPlayerMarketOffer>;
				
				foreach(P2PTraderPlayerMarketOffer marketOffer: marketItems) {
					if (marketOffer.GetOwnerId() == playerId) {
						marketPlayerItems.Insert(marketOffer);
					}
				}
				
				itemService.GetMarketItemListInit(stockItems, marketItems);
			}
		} else if (rpc_type == P2P_TRADER_EVENT_GET_MY_BID_OFFERS_RESPONSE) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_GET_MY_BID_OFFERS_RESPONSE");
            Param3<ref array<ref P2PTraderPlayerPlayerOffer>, ref array<ref P2PTraderPlayerPlayerOffer>, ref array<ref P2PTraderPlayerPlayerOffer>> parameterPlayerBids;
            if (ctx.Read(parameterPlayerBids)) {
                playerOffers = parameterPlayerBids.param1;
                inactivePlayerOffers = parameterPlayerBids.param2;
                acceptedPlayerOffers = parameterPlayerBids.param3;
			}
		} else if (rpc_type == P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS_RESPONSE || rpc_type == P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE|| rpc_type == P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS_RESPONSE");
            Param1<bool> parameterPlayerDeleteMyBid;
            if (ctx.Read(parameterPlayerDeleteMyBid)) {
                bool hasDeleted = parameterPlayerDeleteMyBid.param1;
				RefrechPlayerLists();
			}
		} else if (rpc_type == P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE");
            Param1<bool> parameterPlayerAcceptBid;
            if (ctx.Read(parameterPlayerAcceptBid)) {
                bool hasAccepted = parameterPlayerAcceptBid.param1;
				RefrechPlayerLists();
				RefrechStockLists();
			}
		} else if (rpc_type == P2P_TRADER_EVENT_RESPONSE_ERROR) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_RESPONSE_ERROR");
            Param1<string> parameterError;
            if (ctx.Read(parameterError)) {
                string errorMessage = parameterError.param1;
				message.SetText(errorMessage);
				createOfferWidget.Show(false);
				createPlayerOfferWidget.Show(false);
			}
		}
	}
	
	void CloseMenu(){
		DebugMessageP2PTrader("check is open");
		if(isMenuOpen){
			DebugMessageP2PTrader("try close menu");
			SetFocus(NULL);
			OnHide();
			layoutRoot.Show(false);
			isMenuOpen = false;
		}	
	}
	
	bool IsInitialized() {
		return !!layoutRoot;
	}
	
	private void RefrechPlayerLists() {
		Param1<DayZPlayer> paramGetPlayerItems = new Param1<DayZPlayer>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_PLAYER_ITEMS, paramGetPlayerItems, true);
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_MY_BID_OFFERS, paramGetPlayerItems, true);
	}
	
	private void RefrechStockLists() {
		Param1<DayZPlayer> paramGetPlayerItems = new Param1<DayZPlayer>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_STOCK, paramGetPlayerItems, true);
	}

}