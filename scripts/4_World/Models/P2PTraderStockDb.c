class P2PTraderStockDb
{
	P2PTraderConfig config;
	ref P2PConnection connection;
	private ref JsonSerializer json;
	
    void P2PTraderStockDb(P2PTraderConfig config)
    {
		this.config = config;
		json = new JsonSerializer;
		connection = P2PConnection("rNXMc3Z9kpJWrNGdWyuFZ2MVeNuBJ3mDqDL0GbiWWao");
    }

	void AddPlayerToMarketOffer(ref P2PTraderPlayerMarketOffer newOffer) {
        string jsonText;
        json.WriteToString(newOffer, P2P_TRADER_DEBUG, jsonText);
        DebugMessageP2PTrader("encoded json: " + jsonText);
		P2PCURLCallback callback = new P2PCURLCallback(json);
		connection.SendData(jsonText, "stock/player-market-offer/create?", callback);
	}
	
	void AddPlayerToPlayerOffer(P2PTraderPlayerPlayerOffer newOffer) {
		string jsonText;
        json.WriteToString(newOffer, P2P_TRADER_DEBUG, jsonText);
        DebugMessageP2PTrader("encoded json: " + jsonText);
        P2PCURLCallback callback = new P2PCURLCallback(json);
        connection.SendData(jsonText, "stock/player-player-offer/create?", callback);
	}

    P2PTraderPlayerMarketOffer GetPlayerToMarketOfferById(int id) {
		string responseRaw = connection.GetData("stock/player-market-offer/" + id.ToString() + "?");
		DebugMessageP2PTrader("response: " + responseRaw);
		P2PTraderPlayerMarketOffer offer;
		json.ReadFromString(offer, responseRaw, error);

		return offer;
    }

    P2PTraderPlayerPlayerOffer GetPlayerOfferById(int id) {
        string responseRaw = connection.GetData("stock/player-player-offer/" + id.ToString() + "?");
        DebugMessageP2PTrader("response: " + responseRaw);
        P2PTraderPlayerPlayerOffer offer;
        json.ReadFromString(offer, responseRaw, error);

        return offer;
    }

	void RemovePlayerToMarketOffer(P2PTraderPlayerMarketOffer offerToRemove) {
        P2PCURLCallback callback = new P2PCURLCallback(json);
        connection.SendData("{}", "stock/player-market-offer/delete/" + offerToRemove.id.ToString() + "?", callback);
	}

	void RemovePlayerToPlayerOffer(P2PTraderPlayerPlayerOffer offerToRemove, bool dontSave = false) {
        P2PCURLCallback callback = new P2PCURLCallback(json);
        connection.SendData("{}", "stock/player-player-offer/delete/" + offerToRemove.id.ToString() + "?", callback);
    }

	void AcceptPlayerToPlayerOffer(P2PTraderPlayerMarketOffer marketOffer, P2PTraderPlayerPlayerOffer playerOffer) {
        P2PCURLCallback callback = new P2PCURLCallback(json);
        connection.SendData("{}", "stock/player-player-offer/accept/" + playerOffer.id.ToString() + "/" + marketOffer.id.ToString() + "?", callback);
	}

	void AcceptPlayerToMarketOffer(P2PTraderPlayerMarketOffer marketOffer, P2PTraderPlayerPlayerOffer playerOffer) {
        P2PCURLCallback callback = new P2PCURLCallback(json);
        connection.SendData("{}", "stock/player-market-offer/accept/" + marketOffer.id.ToString() + "/" + playerOffer.id.ToString() + "?", callback);
	}
	
	array<ref P2PTraderPlayerMarketOffer> GetStock() {
        string responseRaw = connection.GetData("player-market-offer/server/1/100?");
        DebugMessageP2PTrader("response: " + responseRaw);
        P2PPlayerMarketOfferCollection collection;
        json.ReadFromString(collection, responseRaw, error);

        return collection.GetItems();
	}
	
	ref array<P2PTraderPlayerMarketOffer> GetMarketOffersFromPlayer(DayZPlayer player) {
	    string playerId = player.GetIdentity().GetId();
        string responseRaw = connection.GetData("player-market-offer/server/"+ playerId +"/1/100?");
        DebugMessageP2PTrader("response: " + responseRaw);
        P2PPlayerMarketOfferCollection collection;
        json.ReadFromString(collection, responseRaw, error);

        return collection.GetItems();
	}
	
	array<ref P2PTraderPlayerPlayerOffer> GetOffersFromAllPlayer() {
        string responseRaw = connection.GetData("player-player-offer/server/1/100?");
        DebugMessageP2PTrader("response: " + responseRaw);
        P2PPlayerPlayerOfferCollection collection;
        json.ReadFromString(collection, responseRaw, error);

        return collection.GetItems();
	}
	array<ref P2PTraderPlayerPlayerOffer> GetAcceptedOffersFromAllPlayer() {

	}
	array<ref P2PTraderPlayerPlayerOffer> GetInactiveOffersFromAllPlayer() {

	}
	
	ref array<ref P2PTraderPlayerPlayerOffer> GetOffersFromPlayer(PlayerIdentity player, string offerType) {

	}
	
	int GetCountPlayerOffers(DayZPlayer player) {

	}
	

	
	array<ref P2PTraderPlayerPlayerOffer> GetInactiveOffersFromPlayer(PlayerIdentity player) {

	}
	
	array<ref P2PTraderPlayerPlayerOffer> GetAcceptedOffersFromPlayer(PlayerIdentity player) {

	}*/
	
}