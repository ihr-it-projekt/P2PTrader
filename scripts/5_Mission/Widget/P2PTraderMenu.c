class P2PTraderMenu extends UIScriptedMenu
{
	private DayZPlayer player;
    private ButtonWidget cancel;
	private P2PTraderConfig config;
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
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(cancel,  this, "OnClick");

        layoutRoot.Show(false);

        return layoutRoot;
    }

    override bool OnClick( Widget w, int x, int y, int button )	{
        bool actionRuns = super.OnClick(w, x, y, button);

        if (actionRuns) {
            return actionRuns;
        }

        if (w == cancel){
            DebugMessageP2PTrader("click cancel");
            CloseMenu();
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