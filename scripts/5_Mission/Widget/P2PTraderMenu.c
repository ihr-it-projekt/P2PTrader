class P2PTraderMenu extends UIScriptedMenu
{
	private DayZPlayer player;
    private ButtonWidget cancel;
	private P2PTraderConfig config;
	private ButtonWidget buttonCreateOffer;
	private ButtonWidget buttonSearchOffer;
	private ButtonWidget buttonCloaseCreateOffer;
	private UIActionEditableText inputSearchOffer;
	private TextListboxWidget tradeableItems;
	private ref ItemService itemService;
	private Widget createOfferWidget;
	bool isMenuOpen = false;
	
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
		
		player = GetGame().GetPlayer();

        layoutRoot = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layouts/mainMenu.layout");

        cancel = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "cancel" ));
        buttonCreateOffer = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "buttonCreateOffer" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(cancel,  this, "OnClick");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCreateOffer,  this, "OnClick");
		
		createOfferWidget = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layouts/offer.layout");
		createOfferWidget.Show(false);
		
		
		//Start offer widget
        tradeableItems = TextListboxWidget.Cast(createOfferWidget.FindAnyWidget("tradeableItems"));
		
        buttonCloaseCreateOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonCloaseCreateOffer"));
        buttonSearchOffer = ButtonWidget.Cast(createOfferWidget.FindAnyWidget("buttonSearchOffer"));
		
        inputSearchOffer = UIActionEditableText.Cast(createOfferWidget.FindAnyWidget("inputSearchOffer"));
		
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonCloaseCreateOffer,  this, "OnClick");
        buttonSearchOffer.GetInstance().RegisterOnMouseButtonDown(buttonCloaseCreateOffer,  this, "OnClick");
		
		
		layoutRoot.AddChild(createOfferWidget);
		//End offer widget
		
        layoutRoot.Show(false);
		
		itemService = new ItemService;
		itemService.AddTradeableItemsToWidget(tradeableItems, "All", "");
		

        return layoutRoot;
    }

    override bool OnClick( Widget w, int x, int y, int button )	{
        bool actionRuns = super.OnClick(w, x, y, button);

        if (actionRuns) {
            return actionRuns;
        } else if (w == cancel){
            DebugMessageP2PTrader("click cancel");
            CloseMenu();
            return true;
        } else if(w == buttonCreateOffer) {
			createOfferWidget.Show(true);
		} else if(w == buttonCloaseCreateOffer) {
			createOfferWidget.Show(false);
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
	}
	
		
	override void OnShow()
	{
		if (isMenuOpen) {
			DebugMessageP2PTrader("Menu is already open");
			return;
		}
		
		super.OnShow();
				
		DebugMessageP2PTrader("show action");
		
		PPEffects.SetBlurMenu(0.5);

		SetFocus( layoutRoot );
		layoutRoot.Show(true);

		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
		GetGame().GetUIManager().ShowUICursor(true);
		GetGame().GetUIManager().ShowCursor(true);
		GetGame().GetInput().ChangeGameFocus( 1 );
		GetGame().GetMission().GetHud().Show( false );
		isMenuOpen = true;
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