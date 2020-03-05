class P2PTraderHint extends UIScriptedMenu
{
    private bool isOpen  = false;
    private MultilineTextWidget message;

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

    private void toggleWidget() {
        DebugMessageP2PTrader("toggle hint " + isOpen);
        layoutRoot.Show(isOpen);
    }
};