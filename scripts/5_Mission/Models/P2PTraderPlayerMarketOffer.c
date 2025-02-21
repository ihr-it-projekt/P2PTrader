class P2PTraderPlayerMarketOffer extends P2PTraderBaseOffer {
    static string TYPE_ALL = "all";
    static string TYPE_INSTANT_BUY = "instant_buy";
    static string TYPE_AUCTION = "auction";

    private string offerMessage;
    private ref array <ref P2PTraderStockItem> wantedItems;
    private ref array <int> otherPlayerOffersIds;
    private string offerType;


    void P2PTraderPlayerMarketOffer(DayZPlayer owner, string _offerType, string _offerMessage = "") {
        ownerId = owner.GetIdentity().GetId();
        ownerName = owner.GetIdentity().GetName();
        offerMessage = _offerMessage;
        offerItems = new array<ref P2PTraderStockItem>;
        wantedItems = new array<ref P2PTraderStockItem>;
        this.otherPlayerOffersIds = new array<int>;
        this.SetCreationDate();
        this.offerType = _offerType;

    }

    string GetOfferType() {
        return this.offerType;
    }

    bool IsOfferType(string _offerType) {
        if(!this.offerType || this.offerType == "") {
            this.offerType = this.TYPE_AUCTION;
        }

        return this.offerType == _offerType;
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

    void AddWantedItem(P2PTraderStockItem item) {
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

    bool HasPlayerOfferId(int _id) {
        int index = otherPlayerOffersIds.Find(_id);

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