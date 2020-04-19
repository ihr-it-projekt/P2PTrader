class P2PTraderHint extends UIScriptedMenu
{
    private bool isOpen  = false;
    private MultilineTextWidget messageField;
	private string message = "#hint_can_open_trader";
	
	
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
		messageField.SetText(message);

        isOpen = false;
		layoutRoot.Show(isOpen);
        
		return layoutRoot;
    }

    override void OnHide()
    {
        if (!isOpen) {
            return;
        }

        super.OnHide();

        isOpen = false;
        layoutRoot.Show(isOpen);
    }


    override void OnShow()
    {
        if (isOpen) {
            return;
        }

        super.OnShow();
		isOpen = true;
		layoutRoot.Show(isOpen);
    }


    bool IsInitialized() {
        return !!layoutRoot;
    }
	
	void SetMessage(string keyName) {
		if (keyName) {
			message = "#hint_can_open_trader" + " #key_to_open: " + keyName;
			messageField.SetText(message);
		}
	}
};