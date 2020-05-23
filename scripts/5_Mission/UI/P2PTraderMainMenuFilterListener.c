class P2PTraderMainMenuFilterListener extends Managed
{
	private ButtonWidget buttonSearchMarket;
	private XComboBoxWidget filterOfferOwner;
	private XComboBoxWidget filterOfferType;
	private XComboBoxWidget filterCategoryType;
	private EditBoxWidget inputSearchMarket;
	private P2PItemService itemService;
	private TextListboxWidget marketOffers;
	private ref array<ref P2PTraderPlayerMarketOffer> marketPlayerItems;
	private ref array<ref P2PTraderPlayerMarketOffer> marketItems;

    void P2PTraderMainMenuFilterListener(Widget layout, P2PItemService itemService, TextListboxWidget marketOffers) {
        this.itemService = itemService;
        this.marketOffers = marketOffers;
        
		buttonSearchMarket = ButtonWidget.Cast(layout.FindAnyWidget("buttonSearchMarket"));
        inputSearchMarket = EditBoxWidget.Cast(layout.FindAnyWidget("inputSearchMarket"));
        filterOfferOwner = XComboBoxWidget.Cast(layout.FindAnyWidget("filterOfferOwner"));
        filterOfferType = XComboBoxWidget.Cast(layout.FindAnyWidget("filterOfferType"));
        filterCategoryType = XComboBoxWidget.Cast(layout.FindAnyWidget("filterCategoryType"));
		filterCategoryType.AddItem("#all");

		filterOfferType.AddItem("#show_all_offers_types");
		filterOfferType.AddItem("#show_only_direct_offers");
		filterOfferType.AddItem("#show_only_bid_offers");

		filterOfferOwner.AddItem("#all_offers");
		filterOfferOwner.AddItem("#my_offers");
		
		array<ref P2PTraderCategory> catItemsInventory = itemService.GetCategoryItemsInventory().GetCategories();
		
		foreach(P2PTraderCategory category: catItemsInventory) {
			filterCategoryType.AddItem(category.GetName());
		}

        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(buttonSearchMarket, this, "OnClickFilterOwner");
    }

    void OnGetStockEvent(array<ref P2PTraderPlayerMarketOffer> marketItems, array<ref P2PTraderPlayerMarketOffer> marketPlayerItems) {
		this.marketItems = marketItems;
        this.marketPlayerItems = marketPlayerItems;
		OnClickFilterOwner();
    }

	bool OnClickFilterOwner() {
	    DebugMessageP2PTrader("click OnClickFilterOwner");
		int current = filterOfferType.GetCurrentItem();
        string offerType = P2PTraderPlayerMarketOffer.TYPE_ALL;

        if (1 == current) {
            offerType = P2PTraderPlayerMarketOffer.TYPE_INSTANT_BUY;
        } else if (2 == current) {
            offerType = P2PTraderPlayerMarketOffer.TYPE_AUCTION;
        }
		
		int catIndex = filterCategoryType.GetCurrentItem() - 1;
		
		if (1 == filterOfferOwner.GetCurrentItem()) {
			itemService.GetMarketItemList(marketOffers, marketPlayerItems, inputSearchMarket.GetText(), offerType, catIndex);
		} else {
			itemService.GetMarketItemList(marketOffers, marketItems, inputSearchMarket.GetText(), offerType, catIndex);
		}
        
        return true;
	}
}