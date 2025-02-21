class P2PTraderBaseSubWidget extends P2PTraderScriptedMenu {
    protected MultilineTextWidget message;
    protected DayZPlayer player;
    protected P2PTraderItemListenerManger itemListenerManager;
    protected P2PTraderConfig config;

    void SetInitDependencies(DayZPlayer _player, P2PTraderItemListenerManger _itemListenerManager, P2PItemService _itemService, MultilineTextWidget _message, P2PTraderConfig _config) {
        this.player = _player;
        this.itemListenerManager = _itemListenerManager;
        this.itemService = _itemService;
        this.message = _message;
        this.config = _config;
    }
}