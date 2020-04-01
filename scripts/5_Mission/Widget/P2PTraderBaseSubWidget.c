class P2PTraderBaseSubWidget extends P2PTraderScriptedMenu
{
    protected MultilineTextWidget message;
    protected DayZPlayer player;
    protected P2PTraderItemListenerManger itemListenerManager;

    void SetInitDependencies(DayZPlayer player, P2PTraderItemListenerManger itemListenerManager, P2PItemService itemService, MultilineTextWidget message) {
        this.player = player;
        this.itemListenerManager = itemListenerManager;
        this.itemService = itemService;
        this.message = message;
    }
}