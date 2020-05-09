class P2PTraderBaseSubWidget extends P2PTraderScriptedMenu
{
    protected MultilineTextWidget message;
    protected DayZPlayer player;
    protected P2PTraderItemListenerManger itemListenerManager;
	protected P2PTraderConfig config;

    void SetInitDependencies(DayZPlayer player, P2PTraderItemListenerManger itemListenerManager, P2PItemService itemService, MultilineTextWidget message, P2PTraderConfig config) {
        this.player = player;
        this.itemListenerManager = itemListenerManager;
        this.itemService = itemService;
        this.message = message;
        this.config = config;
    }
}