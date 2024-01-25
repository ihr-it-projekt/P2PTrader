class P2PTraderPlayerMarketOffer extends P2PTraderBaseOffer {
    static string TYPE_ALL = "all";
    static string TYPE_INSTANT_BUY = "instant_buy";
    static string TYPE_AUCTION = "auction";

    private string offerMessage;
    private ref array <ref P2PTraderStockItem> wantedItems;
    private ref array <int> otherPlayerOffersIds;
    private string offerType;


    void P2PTraderPlayerMarketOffer(DayZPlayer owner, string offerType, string offerMessage = "") {
        this.ownerId = owner.GetIdentity().GetId();
        this.ownerName = owner.GetIdentity().GetName();
        this.offerMessage = offerMessage;
        this.offerItems = new array<ref P2PTraderStockItem>;
        this.wantedItems = new array<ref P2PTraderStockItem>;
        this.otherPlayerOffersIds = new array<int>;
        this.SetCreationDate();
        this.offerType = offerType;

    }

    string GetOfferType() {
        return this.offerType;
    }

    bool IsOfferType(string offerType) {
        if(!this.offerType || this.offerType == "") {
            this.offerType = this.TYPE_AUCTION;
        }

        return this.offerType == offerType;
    }


    bool IsCategory(int categoryIndex) {
        foreach(P2PTraderStockItem item: offerItems) {
            if(item.GetCategory() == categoryIndex) {
                return true;
            }

            array<ref P2PTraderStockItem> attacheds = item.GetAttached();
            foreach(P2PTraderStockItem attached: attacheds) {
                if(attached.GetCategory() == categoryIndex) {
                    return true;
                }
            }
        }

        return false;
    }

    void AddWantedItem(ref P2PTraderStockItem item) {
        wantedItems.Insert(item);
    }

    void AddPlayerOffer(P2PTraderPlayerPlayerOffer offer) {
        otherPlayerOffersIds.Insert(offer.GetId());
    }

    void RemovePlayerOffer(P2PTraderPlayerPlayerOffer offer) {
        foreach(int index, int offerId: otherPlayerOffersIds) {
            if(offerId == offer.GetId()) {
                otherPlayerOffersIds.Remove(index);
            }
        }
    }

    bool HasPlayerOfferId(int id) {
        int index = otherPlayerOffersIds.Find(id);

        return -1 != index;
    }

    bool IsEmpty() {
        return offerItems.Count() == 0 && wantedItems.Count() == 0;
    }

    bool Contains(string search) {
        foreach(P2PTraderStockItem item: offerItems) {
            if(item.Contains(search)) {
                return true;
            }
        }

        return false;
    }

    void ResetTranslation() {
        foreach(P2PTraderStockItem offerItem: offerItems) {
            offerItem.ResetTranslation();
        }
        foreach(P2PTraderStockItem wantedItem: wantedItems) {
            wantedItem.ResetTranslation();
        }
    }

    array <ref P2PTraderStockItem> GetWantedItems() {
        return wantedItems;
    }

    string GetOfferMessage() {
        return offerMessage;
    }
}