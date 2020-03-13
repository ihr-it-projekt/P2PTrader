class P2PStockChecker extends Managed
{
    private P2PTraderStock stock;
	private ref P2PTraderPlayerInventory inventory;
	private P2PTraderConfigParams config;

    void P2PStockChecker(P2PTraderStock stock, P2PTraderConfigParams config) {
        this.stock = stock;
		this.inventory = new P2PTraderPlayerInventory;
		this.config = config;
    }

    void CheckForExpiredItems() {
		P2PTraderExpiredDate date = new P2PTraderExpiredDate(config.offerWillExpireAfterDays);
		
		
		array<ref P2PTraderPlayerMarketOffer> offers = stock.GetStock();
		
		foreach(P2PTraderPlayerMarketOffer offer: offers) {
			if (offer.IsExceeded(date)) {
				if (config.spawnExceededToGround) {
					Spawn(offer.GetOfferItems());
					
				}
				
				stock.RemovePlayerToMarketOffer(offer);
			}
		}
		
		array<ref P2PTraderPlayerPlayerOffer> pOffers = stock.GetOffersFromAllPlayer();
		
		foreach(P2PTraderPlayerPlayerOffer pOffer: pOffers) {
			if (pOffer.IsExceeded(date)) {
				if (config.spawnExceededToGround) {
					Spawn(pOffer.GetOfferItems());
					
				}
				
				stock.RemovePlayerToPlayerOffer(pOffer);
			}
		}
		
		array<ref P2PTraderPlayerPlayerOffer> iOffers = stock.GetInactiveOffersFromAllPlayer();
		
		foreach(P2PTraderPlayerPlayerOffer iOffer: iOffers) {
			if (iOffer.IsExceeded(date)) {
				if (config.spawnExceededToGround) {
					Spawn(iOffer.GetOfferItems());
					
				}
				
				stock.RemovePlayerToPlayerOffer(iOffer);
			}
		}
		
		array<ref P2PTraderPlayerPlayerOffer> aOffers = stock.GetAcceptedOffersFromAllPlayer();
		
		foreach(P2PTraderPlayerPlayerOffer aOffer: aOffers) {
			if (aOffer.IsExceeded(date)) {
				if (config.spawnExceededToGround) {
					Spawn(aOffer.GetOfferItems());
					
				}
				
				stock.RemovePlayerToPlayerOffer(aOffer);
			}
		}
    }
	
	private void Spawn(array <ref P2PTraderStockItem> items) {
		foreach(P2PTraderStockItem item: items) {
			EntityAI itemObject = EntityAI.Cast(GetGame().CreateObject(item.GetType(), config.spawnPositionExceededOffers.GetRandomElement()));
			inventory.SpawnOnGround(item, null, itemObject);
			Spawn(item.GetAttached());
		}
	}
}