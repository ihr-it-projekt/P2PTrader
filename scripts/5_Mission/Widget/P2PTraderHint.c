class P2PTraderHint extends UIScriptedMenu
{
    private bool isOpen  = false;
    private MultilineTextWidget messageField;
	private P2PTraderConfigParams params;
	private string message;
	
	override Widget Init()
    {
        if (IsServerP2PTrader()){
            return null;
        }

        if (IsInitialized()) {
            return layoutRoot;
        }

        super.Init();

        layoutRoot = GetGame().GetWorkspace().CreateWidgets("P2PTrader/layout/openHint.layout");
		messageField = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("message"));
		message = "#hint_can_open_trader";
		
		if (params.useServerKeyBind) {
			message += " #key_to_open: " + params.possibleKeyBindingsMap.Get(params.defaultKey);
		}
		
		messageField.SetText(message);

        isOpen = false;
        toggleWidget();

        return layoutRoot;
    }

    override void OnHide()
    {
        if (!isOpen) {
            return;
        }

        super.OnHide();

        isOpen = false;
        toggleWidget();
    }


    override void OnShow()
    {
        if (isOpen) {
            return;
        }

        super.OnShow();

        isOpen = true;
        toggleWidget();
    }


    bool IsInitialized() {
        return !!layoutRoot;
    }
	
	void SetConfigParams(P2PTraderConfigParams params) {
		this.params = params;
	}

    private void toggleWidget() {
        DebugMessageP2PTrader("toggle hint " + isOpen);
        layoutRoot.Show(isOpen);
    }
};