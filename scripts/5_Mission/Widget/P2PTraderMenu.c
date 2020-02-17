class P2PTraderMenu extends UIScriptedMenu
{
	private DayZPlayer player;
	private PlayerIdentity playerIdent;
	private string playerId;
	private P2PTraderConfig config;
	private P2PTraderPlayerMarketOffer selectedStockItem;
	private array<ref P2PTraderPlayerPlayerOffer> selectedPlayerOffers;
	private P2PTraderPlayerPlayerOffer selectedPlayerOffer;
	private ref ItemService itemService;
	private ref array<ref P2PTraderPlayerMarketOffer> marketItems;
	private ref array<ref P2PTraderPlayerMarketOffer> marketPlayerItems;
	private ref array<ref P2PTraderPlayerPlayerOffer> allActiveOffers;
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
	private TextListboxWidget offerPlayerBidItems;
	private TextListboxWidget offerPlayerBidItemsAttachments;
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
        offerPlayerBidItems = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "offerPlayerBidItems" ));
        offerPlayerBidItemsAttachments = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "offerPlayerBidItemsAttachments" ));
        playerNameOfferDetail = TextWidget.Cast( layoutRoot.FindAnyWidget( "playerNameOfferDetail" ));
        offerPlayerLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerPlayerLabel" ));
        offerItemAttachmentLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerItemAttachmentLabel" ));
        offerItemLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerItemLabel" ));
        offerMessageFromPlayerLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerMessageFromPlayerLabel" ));
        offerMyBidAttachmentLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerMyBidAttachmentLabel" ));
        offerMyBidLabel = TextWidget.Cast( layoutRoot.FindAnyWidget( "offerMyBidLabel" ));
        playerOfferMessageDetail = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "playerOfferMessageDetail" ));
		inputSearchMarket = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("inputSearchMarket"));
		message = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("message"));
		
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(cancel,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonOpenCreateOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonSearchMarket,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonDeleteMyBid,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonDeleteMyOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonAllOffers,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonMyOffers,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonTakeOffer,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonOpenCreateMyBid,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(stockItems,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(offerDetailItems,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(offerPlayerBidItems,  this, "OnClick");
		
		createOfferWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/offer.layout");
		createPlayerOfferWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/bid.layout");
        
		
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
        } else if(w == buttonOpenCreateMyBid && selectedStockItem) {
			DebugMessageP2PTrader("click buttonOpenCreateMyBid");
			playerItemsOfferPlayerOffer.ClearItems();
			
			playerTextPlayerOffer.SetText("");
			playerNameBidDetail.SetText(selectedStockItem.GetOwnerName());
			playerOfferMessageDetailBid.SetText(selectedStockItem.GetOfferMessage());
			detailAttechmentBid.ClearItems();
			itemService.GetMarketOfferItemList(offerDetailItemsBid, selectedStockItem);
			createPlayerOfferWidget.Show(true);
		} else if(w == buttonOpenCreateOffer) {
			DebugMessageP2PTrader("click buttonOpenCreateOffer");
			createOfferWidget.Show(true);
		} else if(w == buttonSearchOffer) {
			DebugMessageP2PTrader("click buttonSearchOffer");
			itemService.AddTradeableItemsToWidget(tradeableItemsOffer, inputSearchOffer.GetText());
		} else if(w == buttonSearchMarket) {
			DebugMessageP2PTrader("click buttonSearchMarket");
			itemService.GetMarketItemList(stockItems, marketItems, inputSearchMarket.GetText());
		} else if(w == buttonCreateCreateOffer) {
			DebugMessageP2PTrader("Click on create offer");
			messageText = itemService.CreateOffer(player, playerItemsOfferOffer, playerWhantToHaveOffer, playerTextOffer.GetText());
			
			createOfferWidget.Show(false);
		} else if(w == buttonCreateCreatePlayerOffer) {
			DebugMessageP2PTrader("Click on create player offer");
			messageText = itemService.CreateOfferToPlayer(player, playerItemsOfferPlayerOffer, selectedStockItem.GetId(), playerTextPlayerOffer.GetText());

			createPlayerOfferWidget.Show(false);
		} else if(w == buttonCloseCreateOffer) {
			DebugMessageP2PTrader("click buttonCloseCreateOffer");
			createOfferWidget.Show(false);
		} else if(w == buttonCreateClosePlayerOffer) {
			DebugMessageP2PTrader("click buttonCreateClosePlayerOffer");
            createPlayerOfferWidget.Show(false);
		} else if(w == stockItems) {
			DebugMessageP2PTrader("click stockItems");
			DebugMessageP2PTrader("try get selected item");
			selectedStockItem = itemService.GetSelectedMarketOffer(stockItems);
			
			DebugMessageP2PTrader("config filds");
			playerNameOfferDetail.SetText(selectedStockItem.GetOwnerName());
			playerOfferMessageDetail.SetText(selectedStockItem.GetOfferMessage());
			
			DebugMessageP2PTrader("try set items to list");
			itemService.GetMarketOfferItemList(offerDetailItems, selectedStockItem);
			
			offerMessageFromPlayerLabel.Show(true);
			offerPlayerLabel.Show(true);
			offerDetailItems.Show(true);
			detailAttechment.Show(true);
			offerItemLabel.Show(true);
			offerItemAttachmentLabel.Show(true);
			DebugMessageP2PTrader("try ShowHideMyOfferForItem");
			ShowHideMyOfferForItem();
		} else if(w == offerDetailItems) {
			DebugMessageP2PTrader("click offerDetailItems");
			P2PTraderStockItem currentStockItem = itemService.GetSelectedStockItem(offerDetailItems);
			itemService.GetMarketOfferItemAttachmentList(detailAttechment, currentStockItem);
		} else if(w == offerDetailItemsBid) {
			DebugMessageP2PTrader("click offerDetailItems");
			P2PTraderStockItem currentStockBidItem = itemService.GetSelectedStockItem(offerDetailItemsBid);
			itemService.GetMarketOfferItemAttachmentList(detailAttechmentBid, currentStockBidItem);
		} else if(w == offerPlayerBidItems) {
			DebugMessageP2PTrader("click offerPlayerBidItems");
			P2PTraderStockItem currentMyBidItem = itemService.GetSelectedStockItem(offerPlayerBidItems);
			itemService.GetMarketOfferItemAttachmentList(offerPlayerBidItemsAttachments, currentMyBidItem);
		} else if(w == offerDetailItemsBid) {
			DebugMessageP2PTrader("click offerDetailItemsBid");
			P2PTraderStockItem currentMyBidItemBidView = itemService.GetSelectedStockItem(offerDetailItemsBid);
			itemService.GetMarketOfferItemAttachmentList(detailAttechmentBid, currentMyBidItemBidView);
		} else if(w == buttonDeleteMyBid) {
			DebugMessageP2PTrader("click buttonDeleteMyBid");
			if (!selectedPlayerOffer) {
				DebugMessageP2PTrader("no selected offer");
				return true;
			}
			DebugMessageP2PTrader("click buttonDeleteMyBid");
			Param2<DayZPlayer, int> paramRemovePlayerToPlayerOffer = new Param2<DayZPlayer, int>(GetGame().GetPlayer(), selectedPlayerOffer.GetId());
			GetGame().RPCSingleParam(paramRemovePlayerToPlayerOffer.param1, P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS, paramRemovePlayerToPlayerOffer, true);
			buttonDeleteMyBid.Show(false);
		} else if(w == buttonDeleteMyOffer) {
			DebugMessageP2PTrader("click buttonDeleteMyOffer");
			if (!selectedStockItem) {
				DebugMessageP2PTrader("no selected selectedStockItem");
				return true;
			}
			
			Param2<DayZPlayer, int> paramRemovePlayerToMarketOffer = new Param2<DayZPlayer, int>(GetGame().GetPlayer(), selectedStockItem.GetId());
			GetGame().RPCSingleParam(paramRemovePlayerToMarketOffer.param1, P2P_TRADER_EVENT_REMOVE_OFFER, paramRemovePlayerToMarketOffer, true);
			buttonDeleteMyOffer.Show(false);
		} else if(w == buttonTakeOffer && selectedPlayerOffer && selectedStockItem && (P2P_TRADER_DEBUG_BUTTON || selectedPlayerOffer.GetOwnerId() != selectedStockItem.GetOwnerId())) {
			DebugMessageP2PTrader("click buttonTakeOffer");
			Param3<DayZPlayer, int, int> paramTakePlayerToMarketOffer = new Param3<DayZPlayer, int, int>(GetGame().GetPlayer(), selectedPlayerOffer.GetId(), selectedStockItem.GetId());
			GetGame().RPCSingleParam(paramTakePlayerToMarketOffer.param1, P2P_TRADER_EVENT_TAKE_OFFER, paramTakePlayerToMarketOffer, true);
			buttonDeleteMyOffer.Show(false);
		} else if(w == buttonMyOffers) {
			DebugMessageP2PTrader("click buttonMyOffers");
			buttonMyOffers.Show(false);
			buttonAllOffers.Show(true);
			
			itemService.GetMarketItemList(stockItems, marketPlayerItems, inputSearchMarket.GetText());
		} else if(w == buttonAllOffers) {
			DebugMessageP2PTrader("click buttonAllOffers");
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
		if (selectedStockItem) {
			selectedPlayerOffers = itemService.GetPlayerOffersForMarketOffer(selectedStockItem, allActiveOffers);
			DebugMessageP2PTrader("Select a offer");
			
			if (selectedPlayerOffers) {
				itemService.GetPlayerOfferItemsList(offerPlayerBidItems, selectedPlayerOffers);
			}
			offerPlayerBidItemsAttachments.ClearItems();
			
			offerPlayerBidItems.Show(true);
			offerMyBidAttachmentLabel.Show(true);
			offerMyBidLabel.Show(true);
			offerPlayerBidItemsAttachments.Show(true);
			
			
			if (P2P_TRADER_DEBUG_BUTTON) {
				buttonOpenCreateMyBid.Show(true);
				buttonDeleteMyOffer.Show(true);
				buttonDeleteMyBid.Show(true);
			} else if(selectedStockItem.GetOwnerId() != GetGame().GetPlayer().GetIdentity().GetPlainId()) {
				buttonOpenCreateMyBid.Show(true);
				buttonDeleteMyOffer.Show(false);
				buttonDeleteMyBid.Show(true);
			}else {
				buttonOpenCreateMyBid.Show(false);
				buttonDeleteMyOffer.Show(true);
				buttonDeleteMyBid.Show(false);
			}
		
		} else {
			offerPlayerBidItems.Show(false);
			offerMyBidAttachmentLabel.Show(false);
			offerMyBidLabel.Show(false);
			offerPlayerBidItemsAttachments.Show(false);
			buttonOpenCreateMyBid.Show(false);
			buttonDeleteMyBid.Show(false);
			buttonDeleteMyOffer.Show(false);
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
		offerPlayerBidItems.ClearItems();
		offerPlayerBidItemsAttachments.ClearItems();
		playerWhantToHaveOffer.ClearItems();
		playerInventoryItemsOffer.ClearItems();
		playerItemsOfferOffer.ClearItems();
		playerInventoryItemsPlayerOffer.ClearItems();
		playerItemsOfferPlayerOffer.ClearItems();
		tradeableItemsOffer.ClearItems();
		
		allActiveOffers.Clear();
		marketPlayerItems.Clear();
		marketItems.Clear();
		selectedStockItem = null;
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
		
		player = GetGame().GetPlayer();
		playerIdent = player.GetIdentity();
		playerId = playerIdent.GetPlainId();
		
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
		offerPlayerBidItems.Show(false);
		offerPlayerBidItemsAttachments.Show(false);
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
				
				DebugMessageP2PTrader("got market items: " + marketItems.Count().ToString());
				
				marketPlayerItems = new ref array<ref P2PTraderPlayerMarketOffer>;
				
				player = GetGame().GetPlayer();
				playerIdent = player.GetIdentity();
				playerId = GetGame().GetPlayer().GetIdentity().GetPlainId();
				
				foreach(P2PTraderPlayerMarketOffer marketOffer: marketItems) {
					if (marketOffer.GetOwnerId() == playerId) {
						DebugMessageP2PTrader("added to player list");
						marketPlayerItems.Insert(marketOffer);
					}
				}
				
				itemService.GetMarketItemListInit(stockItems, marketItems);
			}
		} else if (rpc_type == P2P_TRADER_EVENT_GET_ALL_BID_OFFERS_RESPONSE) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_GET_ALL_BID_OFFERS_RESPONSE");
            Param1<ref array<ref P2PTraderPlayerPlayerOffer>> parameterPlayerBids;
            if (ctx.Read(parameterPlayerBids)) {
                allActiveOffers = parameterPlayerBids.param1;
			}
		} else if (rpc_type == P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS_RESPONSE || rpc_type == P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE || rpc_type == P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE || rpc_type == P2P_TRADER_EVENT_NEW_OFFER_RESPONSE || rpc_type == P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE) {
			DebugMessageP2PTrader("recive EVENT and Refresh lists");
           	RefrechPlayerLists();
			RefrechStockLists();
			
		} else if (rpc_type == P2P_TRADER_EVENT_RESPONSE_ERROR) {
			DebugMessageP2PTrader("recive P2P_TRADER_EVENT_RESPONSE_ERROR");
            Param1<string> parameterError;
            if (ctx.Read(parameterError)) {
				message.SetText(parameterError.param1);
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
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_ALL_BID_OFFERS, paramGetPlayerItems, true);
	}
	
	private void RefrechStockLists() {
		Param1<DayZPlayer> paramGetPlayerItems = new Param1<DayZPlayer>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetPlayerItems.param1, P2P_TRADER_EVENT_GET_STOCK, paramGetPlayerItems, true);
	}

}