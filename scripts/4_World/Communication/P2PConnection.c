class P2PConnection {
	
	private string apiKey;
	private ref CURLCore curl;
	
	void P2PConnection(string apiKey) {
		this.apiKey = apiKey;
		curl = CreateCURLCore();
	}
	
	void SendData(string jsonString, string urlSuffix, P2PCURLCallback callbackExt) {
		curl.EnableDebug(P2P_TRADER_DEBUG);
		CURLContext context = curl.GetCURLContext(API_SERVER_URL);
		string dataUrl = urlSuffix + "api-key=" + this.apiKey;
		context.POST(callbackExt, dataUrl, jsonString);
	}

	string SendDataNow(string jsonString, string urlSuffix) {
		curl.EnableDebug(P2P_TRADER_DEBUG);
		CURLContext context = curl.GetCURLContext(API_SERVER_URL);
		string dataUrl = urlSuffix + "api-key=" + this.apiKey;
		return context.POST_now(callbackExt, dataUrl, jsonString);
	}
	
	string GetData(string urlSuffix) {
		curl.EnableDebug(P2P_TRADER_DEBUG);
		CURLContext context = curl.GetCURLContext(API_SERVER_URL);
		string dataUrl = urlSuffix + "apikey=" + this.apiKey;
		return context.GET_now(dataUrl);
	}
	
}