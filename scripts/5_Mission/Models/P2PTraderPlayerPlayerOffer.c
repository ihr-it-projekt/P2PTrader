class P2PTraderPlayerPlayerOffer extends P2PTraderBaseOffer {
    private int playerToMarketOfferId;
    private string message;

    void P2PTraderPlayerPlayerOffer(string _ownerId, string _ownerName, int _playerToMarketOfferId, string _message = "") {
        this.playerToMarketOfferId = _playerToMarketOfferId;
        this.ownerId = _ownerId;
        this.ownerName = _ownerName;
        this.offerItems = new array<ref P2PTraderStockItem>;
        this.message = _message;
        this.SetCreationDate();
    }

    int GetPlayerToMarketOfferId() {
        return playerToMarketOfferId;
    }

    void SetPlayerMarketOfferInactive() {
        playerToMarketOfferId = 0;
    }

    bool IsPlayerMarketOfferActive() {
        return 0 != playerToMarketOfferId;
    }

    bool IsEmpty() {
        return offerItems.Count() == 0;
    }

    void SetOfferItems(array <ref P2PTraderStockItem> _offerItems) {
        this.offerItems = _offerItems;
    }

    string GetMessage() {
        return message;
    }

    array <P2PTraderStockItem> GetAllItems() {
        array<P2PTraderStockItem> allItems = new array<P2PTraderStockItem>;

        if(offerItems.Count() > 0) {
            foreach(P2PTraderStockItem item: offerItems) {
                allItems.Insert(item);
                array<ref P2PTraderStockItem> attachedItems = item.GetAttached();
                if(attachedItems.Count() > 0) {
                    foreach(P2PTraderStockItem aItem: attachedItems) {
                        allItems.Insert(aItem);
                    }
                }
            }
        }

        return allItems;
    }

    void ResetTranslation() {
        foreach(P2PTraderStockItem offerItem: offerItems) {
            offerItem.ResetTranslation();
        }
    }

}