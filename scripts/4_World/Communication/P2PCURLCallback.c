class P2PCURLCallback extends CURLCallback
{

	JsonSerializer json
	
	void P2PCURLCallback(notnull JsonSerializer json) {
		this.json = json;
	}
	
	override void OnSuccess(string data, int dataSize )
	{
		string error;
		DebugMessageP2PTrader("Response data: " + data);
		json.ReadFromString("", data, error);
		
		DebugMessageP2PTrader("Response Error: " + error);
		
		
	};
}