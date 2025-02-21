class P2PTraderBaseSubWidget extends P2PTraderScriptedMenu {
    protected MultilineTextWidget message;
    protected DayZPlayer player;
    protected P2PTraderItemListenerManger itemListenerManager;
    protected P2PTraderConfig config;

    void SetInitDependencies(DayZPlayer _player, P2PTraderItemListenerManger _itemListenerManager, P2PItemService _itemService, MultilineTextWidget _message, P2PTraderConfig _config) {
        player = _player;
        itemListenerManager = _itemListenerManager;
        itemService = _itemService;
        message = _message;
        config = _config;
    }
}