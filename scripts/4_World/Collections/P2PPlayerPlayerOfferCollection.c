class P2PPlayerPlayerOfferCollection
{
    private int page;
    private int limit;
    private int pages;
    private int total;
    private array<ref P2PTraderPlayerMarketOffer> items;

    array<ref P2PTraderPlayerPlayerOffer> GetItems() {
        return items;
    }
}