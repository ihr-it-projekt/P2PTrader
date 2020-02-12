class P2PTraderMenu extends UIScriptedMenu
{
	private DayZPlayer player;
	private P2PTraderConfig config;
	private P2PTraderPlayerMarketOffer selectedItem;
	private P2PTraderPlayerPlayerOffer selectedOffer;
	private ref ItemService itemService;
	private ref array<ref P2PTraderPlayerMarketOffer> marketItems;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> inactivePlayerOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> acceptedPlayerOffers;
	private Widget createOfferWidget;
	private Widget createPlayerOfferWidget;
	bool isMenuOpen = false;

    private ButtonWidget cancel;
	private ButtonWidget buttonMyOffers;
	private ButtonWidget buttonDeleteMyBid;
	private ButtonWidget buttonEditMyBid;
	private ButtonWidget buttonCreateMyBid;
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
	private EditBoxWidget playerTextOffer;
	private EditBoxWidget playerTextPlayerOffer;
	private MultilineTextWidget message;
	
	
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

        layoutRoot = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/mainMenu.layout");

        cancel = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "cancel" ));
        buttonOpenCreateOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonOpenCreateOffer" ));
        buttonSearchMarket = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonSearchMarket" ));
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
		offerMessageFromPlayerLabel.Show(false);
		offerPlayerLabel.Show(false);
		offerDetailItems.Show(false);
		detailAttechment.Show(false);
		offerMyBidItems.Show(false);
		offerMyBidItemsAttachments.Show(false);
		offerMyBidAttachmentLabel.Show(false);
		offerMyBidLabel.Show(false);
		offerItemLabel.Show(false);
		offerItemAttachmentLabel.Show(false);
		
		
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(cancel,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonOpenCreateOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonSearchMarket,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(stockItems,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(offerDetailItems,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(offerMyBidItems,  this, "OnClick");
		
		createOfferWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/offer.layout");
		createOfferWidget.Show(false);
        createPlayerOfferWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/playerOffer.layout");
        createPlayerOfferWidget.Show(false);
		
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
        playerTextPlayerOffer = EditBoxWidget.Cast(createPlayerOfferWidget.FindAnyWidget("playerTextPlayerOffer"));
        playerInventoryItemsPlayerOffer = TextListboxWidget.Cast(createPlayerOfferWidget.FindAnyWidget("playerInventoryItemsPlayerOffer"));
        playerItemsOfferPlayerOffer = TextListboxWidget.Cast(createPlayerOfferWidget.FindAnyWidget("playerItemsOfferPlayerOffer"));
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
        } else if(w == buttonOpenCreateOffer) {
			createOfferWidget.Show(true);
		} else if(w == buttonSearchOffer) {
			itemService.AddTradeableItemsToWidget(tradeableItemsOffer, inputSearchOffer.GetText());
		} else if(w == buttonSearchMarket) {
			itemService.GetMarketItemList(stockItems, marketItems, inputSearchMarket.GetText());
		} else if(w == buttonCreateCreateOffer) {
			DebugMessageP2PTrader("Click on create offer");
			messageText = itemService.CreateOffer(player, playerItemsOfferOffer, playerWhantToHaveOffer, playerTextOffer.GetText());

			if (messageText != "") {
			    message.SetText(messageText);
			} else {
			    createOfferWidget.Show(false);
			}

		} else if(w == buttonCreateCreatePlayerOffer) {
			DebugMessageP2PTrader("Click on create player offer");
			
			messageText = itemService.CreateOfferToPlayer(player, playerItemsOfferPlayerOffer, selectedItem.GetId(), playerTextPlayerOffer.GetText());

			if (messageText != "") {
			    message.SetText(messageText);
			} else {
			    createOfferWidget.Show(false);
			}

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
			P2PTraderStockItem currentStockItem = itemService.GetSelectedMarketOfferItem(offerDetailItems);

			itemService.GetMarketOfferItemAttachmentList(detailAttechment, currentStockItem);
		} else if(w == offerMyBidItems) {
			P2PTraderStockItem currentMyBidItem = itemService.GetSelectedMarketOfferItem(offerMyBidItems);

			itemService.GetMarketOfferItemAttachmentList(offerMyBidItemsAttachments, currentMyBidItem);
		}

        return false;
    }
	
	private void ShowHideMyOfferForItem() {
		if (selectedItem) {
			selectedOffer = itemService.GetPlayerOffer(selectedItem, playerOffers);
			
			if (selectedOffer) {
				itemService.GetPlayerOfferItemList(offerMyBidItems, selectedOffer);
				
				offerMyBidItems.Show(true);
				offerMyBidAttachmentLabel.Show(true);
				offerMyBidLabel.Show(true);
				offerMyBidItemsAttachments.Show(true);
				buttonCreateMyBid.Show(false);
			} else {
				offerMyBidItems.Show(false);
				offerMyBidAttachmentLabel.Show(false);
				offerMyBidLabel.Show(false);
				offerMyBidItemsAttachments.Show(false);
				buttonCreateMyBid.Show(true);
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
	}
	
		
	override void OnShow()
	{
		if (isMenuOpen) {
			DebugMessageP2PTrader("Menu is already open");
			return;
		}
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
		
		Param1<DayZPlayer> paramGetPlayerItems = new Param1<DayZPlayer>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_PLAYER_ITEMS, paramGetPlayerItems, true);
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_STOCK, paramGetPlayerItems, true);
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_MY_BID_OFFERS, paramGetPlayerItems, true);
		
		super.OnShow();
				
		DebugMessageP2PTrader("show action");
		
		PPEffects.SetBlurMenu(0.5);

		SetFocus(layoutRoot);
		
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
				itemService.GetMarketItemListInit(stockItems, marketItems);
			}
		}else if (rpc_type == P2P_TRADER_EVENT_GET_MY_BID_OFFERS_RESPONSE) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_GET_MY_BID_OFFERS_RESPONSE");
            Param3<ref array<ref P2PTraderPlayerPlayerOffer>, ref array<ref P2PTraderPlayerPlayerOffer>, ref array<ref P2PTraderPlayerPlayerOffer>> parameterPlayerBids;
            if (ctx.Read(parameterPlayerBids)) {
                playerOffers = parameterPlayerBids.param1;
                inactivePlayerOffers = parameterPlayerBids.param2;
                acceptedPlayerOffers = parameterPlayerBids.param3;
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

}