class P2PStockChecker extends Managed {
    private P2PTraderStock stock;
    private ref P2PTraderPlayerInventory inventory;
    private P2PTraderConfigParams config;

    void P2PStockChecker(P2PTraderStock _stock, P2PTraderConfigParams _config) {
        stock = _stock;
        inventory = new P2PTraderPlayerInventory;
        config = _config;
    }

    void CheckForExpiredItems() {
        P2PTraderDate date = new P2PTraderDate();
        date.SetDate();

        array<ref P2PTraderPlayerMarketOffer> offers = stock.GetStock();

        foreach(P2PTraderPlayerMarketOffer offer: offers) {
            if(offer && offer.IsExceeded(date, config.offerWillExpireAfterDays)) {
                if(config.spawnExceededToGround) {
                    Spawn(offer.GetOfferItems());

                }

                stock.RemovePlayerToMarketOffer(offer);
            }
        }

        array<ref P2PTraderPlayerPlayerOffer> pOffers = stock.GetOffersFromAllPlayer();

        foreach(P2PTraderPlayerPlayerOffer pOffer: pOffers) {
            if(pOffer && pOffer.IsExceeded(date, config.offerWillExpireAfterDays)) {
                if(config.spawnExceededToGround) {
                    Spawn(pOffer.GetOfferItems());

                }

                stock.RemovePlayerToPlayerOffer(pOffer);
            }
        }

        array<ref P2PTraderPlayerPlayerOffer> iOffers = stock.GetInactiveOffersFromAllPlayer();

        foreach(P2PTraderPlayerPlayerOffer iOffer: iOffers) {
            if(iOffer && iOffer.IsExceeded(date, config.offerWillExpireAfterDays)) {
                if(config.spawnExceededToGround) {
                    Spawn(iOffer.GetOfferItems());

                }

                stock.RemovePlayerToPlayerOffer(iOffer);
            }
        }

        array<ref P2PTraderPlayerPlayerOffer> aOffers = stock.GetAcceptedOffersFromAllPlayer();

        foreach(P2PTraderPlayerPlayerOffer aOffer: aOffers) {
            if(aOffer && aOffer.IsExceeded(date, config.offerWillExpireAfterDays)) {
                if(config.spawnExceededToGround) {
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
