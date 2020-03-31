class P2PTraderMenu extends UIScriptedMenu
{
	private DayZPlayer player;
	private string playerId;
	private P2PTraderConfig config;
	private P2PTraderPlayerMarketOffer selectedMarketOffer;
	private ref array<ref P2PTraderPlayerPlayerOffer> selectedPlayerOffers;
	private P2PTraderPlayerPlayerOffer selectedPlayerOffer;
	private ref P2PItemService itemService;
	private ref array<ref P2PTraderPlayerMarketOffer> marketItems;
	private ref array<ref P2PTraderPlayerMarketOffer> marketPlayerItems;
	private ref array<ref P2PTraderPlayerPlayerOffer> allActiveOffers;
	private ref array<ref P2PTraderPlayerPlayerOffer> playerActiveOffers;
	private P2PTraderPlayerPlayerOffer playerOfferForSelectedStockItem;
	private ref P2PTraderOfferWidget offerWidget;
	private ref P2PTraderPlayerBidWidget playerBidWidget;
	private ref P2PTraderBidManagementWidget bidManagementWidget;
	private ref P2PTraderUserListEventService userListEventService;

	private Widget createPlayerOfferWidget;
	private bool canTrade = false;
	private EntityAI mainMenuPreviewItem;
	private ref P2PTraderItemListenerManger itemListenManager;
	private ref P2PTraderMainMenuFilterListener mainMenuFilterListener;
	bool isMenuOpen = false;
	
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
	private TextListboxWidget marketOfferItemAttachments;
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
	private MultilineTextWidget playerOfferItemMessage;

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


        cancel = ButtonWidget.Cast( layoutRoot.FindAnyWidget("cancel"));
        buttonOpenCreateOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget("buttonOpenCreateOffer"));
        buttonManageMyBids = ButtonWidget.Cast( layoutRoot.FindAnyWidget("buttonManageMyBids"));
        buttonDeleteMyOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget("buttonDeleteMyOffer"));
        buttonTakeOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget("buttonTakeOffer"));
        buttonOpenCreateMyBid = ButtonWidget.Cast( layoutRoot.FindAnyWidget("buttonOpenCreateMyBid"));
        marketOffers = TextListboxWidget.Cast( layoutRoot.FindAnyWidget("marketOffers"));
        marketOfferItems = TextListboxWidget.Cast( layoutRoot.FindAnyWidget("marketOfferItems"));
        marketOfferItemAttachments = TextListboxWidget.Cast( layoutRoot.FindAnyWidget("marketOfferItemAttachments"));
        marketOfferWantToHave = TextListboxWidget.Cast( layoutRoot.FindAnyWidget("marketOfferWantToHave"));
        playerOffers = TextListboxWidget.Cast( layoutRoot.FindAnyWidget("playerOffers"));
        playerOfferItems = TextListboxWidget.Cast( layoutRoot.FindAnyWidget("playerOfferItems"));
        playerOfferItemAttachments = TextListboxWidget.Cast( layoutRoot.FindAnyWidget("playerOfferItemAttachments"));
        playerNameOfferDetail = TextWidget.Cast( layoutRoot.FindAnyWidget("playerNameOfferDetail"));
        offerPlayerLabel = TextWidget.Cast( layoutRoot.FindAnyWidget("offerPlayerLabel"));
        marketOfferWantToHaveLabel = TextWidget.Cast( layoutRoot.FindAnyWidget("marketOfferWantToHaveLabel"));
        playerOfferItemMessageLabel = TextWidget.Cast( layoutRoot.FindAnyWidget("playerOfferItemMessageLabel"));
        offerItemAttachmentLabel = TextWidget.Cast( layoutRoot.FindAnyWidget("offerItemAttachmentLabel"));
        offerItemLabel = TextWidget.Cast( layoutRoot.FindAnyWidget("offerItemLabel"));
        offerMessageFromPlayerLabel = TextWidget.Cast( layoutRoot.FindAnyWidget("offerMessageFromPlayerLabel"));
        offerMyBidAttachmentLabel = TextWidget.Cast( layoutRoot.FindAnyWidget("offerMyBidAttachmentLabel"));
        offerMyBidLabel = TextWidget.Cast( layoutRoot.FindAnyWidget("offerMyBidLabel"));
        offerMyBidsLabel = TextWidget.Cast( layoutRoot.FindAnyWidget("offerMyBidsLabel"));
        playerOfferMessageDetail = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget("playerOfferMessageDetail"));
		notInNearHint = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("notInNearHint"));
		message = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("message"));
		playerOfferItemMessage = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("playerOfferItemMessage"));

		mainMenuItemPreview = ItemPreviewWidget.Cast(layoutRoot.FindAnyWidget("mainMenuItemPreview"));
		mainMenuItemPreviewText = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("mainMenuItemPreviewText"));
		mainMenuItemPreviewHealth = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("mainMenuItemPreviewHealth"));
		mainMenuItemPreviewQuantity = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("mainMenuItemPreviewQuantity"));

		itemListenManager.AddPreviewListener(mainMenuItemPreviewText, mainMenuItemPreview, marketOfferWantToHave);
		itemListenManager.AddPreviewListener(mainMenuItemPreviewText, mainMenuItemPreview, marketOfferItems);
		itemListenManager.AddPreviewListener(mainMenuItemPreviewText, mainMenuItemPreview, marketOfferItemAttachments);
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

        userListEventService = new P2PTraderUserListEventService(player);

		offerWidget = new P2PTraderOfferWidget(player, layoutRoot, itemListenManager, itemService, message);
		offerWidget.Init();
		playerBidWidget = new P2PTraderPlayerBidWidget(player, layoutRoot, itemListenManager, itemService, message);
		playerBidWidget.Init();
		bidManagementWidget = new P2PTraderBidManagementWidget(player, layoutRoot, itemListenManager, itemService, message, userListEventService, marketItems);
		bidManagementWidget.Init();

        layoutRoot.Show(false);
		
		return layoutRoot;
    }
	
	void SetCanTrade(bool canTrade) {
		this.canTrade = canTrade;
		bidManagementWidget.SetCanTrade(canTrade);
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
			if (config.traderConfigParams.maxMarketOffersPerPlayer == playerActiveOffers.Count() + bidManagementWidget.GetCountPlayerOffers()) {
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
			marketOfferItemAttachments.Show(true);
			offerItemLabel.Show(true);
			
			marketOfferItemAttachments.ClearItems();
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
			itemService.GetMarketOfferItemAttachmentList(marketOfferItemAttachments, currentStockItem);
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
			marketOfferItemAttachments.ClearItems();
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
			marketOfferItemAttachments.ClearItems();
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
			mainMenuItemPreview.Show(false);
			mainMenuItemPreviewText.Show(false);
            bidManagementWidget.OnShow();

			return true;
		}
		return false;
    }
	
	private void ShowHideMyOfferForItem() {
		if (selectedMarketOffer) {
			marketOfferWantToHave.Show(true);
			if(selectedMarketOffer.GetOwnerId() != playerId) {
				buttonDeleteMyOffer.Show(false);
				buttonTakeOffer.Show(false);
				
				if (!canTrade) {
					buttonOpenCreateMyBid.Show(false);
				} else if (playerOfferForSelectedStockItem) {
					buttonOpenCreateMyBid.Show(false);
				} else {
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
	 	marketOfferItemAttachments.ClearItems();
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
		userListEventService.ResetRefresh();
		
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
		
		userListEventService.RefreshStockLists();
		userListEventService.RefreshPlayerLists();
		
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
		marketOfferItemAttachments.Show(false);
		playerOffers.Show(false);
		playerOfferItems.Show(false);
		playerOfferItemAttachments.Show(false);
		offerMyBidAttachmentLabel.Show(false);
		offerMyBidLabel.Show(false);
		offerMyBidsLabel.Show(false);
		offerItemLabel.Show(false);
		offerItemAttachmentLabel.Show(false);
        offerWidget.OnHide();
        bidManagementWidget.OnHide();
        playerBidWidget.OnHide();
		marketOfferWantToHave.Show(false);
		layoutRoot.Show(true);
		buttonManageMyBids.Show(false);
		playerOfferItemMessageLabel.Show(false);
		playerOfferItemMessage.Show(false);
		buttonOpenCreateOffer.Show(canTrade);
		notInNearHint.Show(!canTrade);

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
                offerWidget.OnGetPlayerItems(parameterPlayerItems.param1);
                playerBidWidget.OnGetPlayerItems(parameterPlayerItems.param1);
			}
			userListEventService.DownCountRefresh();
		} else if (rpc_type == P2P_TRADER_EVENT_GET_STOCK_RESPONSE) {
			DebugMessageP2PTrader("receive P2P_TRADER_EVENT_GET_STOCK_RESPONSE");
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
			bidManagementWidget.OnGetAllBidOffers(playerActiveOffers);

			buttonManageMyBids.Show(true);
			userListEventService.DownCountRefresh();
			
		} else if (rpc_type == P2P_TRADER_EVENT_DELETE_MY_BID_OFFERS_RESPONSE || rpc_type == P2P_TRADER_EVENT_NEW_OFFER_FOR_PLAYER_RESPONSE || rpc_type == P2P_TRADER_EVENT_TAKE_OFFER_RESPONSE || rpc_type == P2P_TRADER_EVENT_NEW_OFFER_RESPONSE || rpc_type == P2P_TRADER_EVENT_REMOVE_OFFER_RESPONSE) {
			DebugMessageP2PTrader("receive EVENT and Refresh lists");
           	userListEventService.RefreshPlayerLists();
			userListEventService.RefreshStockLists();
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
			DebugMessageP2PTrader("receive P2P_TRADER_EVENT_RESPONSE_ERROR");
            Param1<string> parameterError;
            if (ctx.Read(parameterError)) {
				message.SetText(parameterError.param1);
				offerWidget.OnHide();
				createPlayerOfferWidget.Show(false);
			}
		} if (rpc_type == P2P_TRADER_EVENT_GET_PLAYER_ACCEPTED_INACTIVE_OFFERS_RESPONSE) {
          DebugMessageP2PTrader("receive P2P_TRADER_EVENT_GET_PLAYER_ACCEPTED_INACTIVE_OFFERS_RESPONSE");
          Param2<ref array<ref P2PTraderPlayerPlayerOffer>, ref array<ref P2PTraderPlayerPlayerOffer>> parameterOffers;
          if (ctx.Read(parameterOffers)) {
              bidManagementWidget.SetPlayerOffers(parameterOffers.param1, parameterOffers.param2);
          }
          userListEventService.DownCountRefresh();
        }
	}
	
	void CloseMenu(){
		DebugMessageP2PTrader("check is open");
		if(isMenuOpen && userListEventService.RefreshFinished()){
			if (offerWidget.IsWidgetVisible()) {
				offerWidget.OnHide();
			} else if(playerBidWidget.IsWidgetVisible()) {
				playerBidWidget.OnHide();
			} else if(bidManagementWidget.IsWidgetVisible()) {
				bidManagementWidget.OnHide();
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
}