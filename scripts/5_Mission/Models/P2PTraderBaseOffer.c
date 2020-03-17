class P2PTraderBaseOffer
{
	ref P2PTraderDate creationDate;
	
	protected void SetCreationDate() {
       	creationDate = new P2PTraderDate();
		creationDate.SetDate();
		creationDate.SetInSeconds();
	}
	
	bool IsExceeded(P2PTraderExpiredDate date) {
		if (!creationDate || creationDate.year == 0) {
			creationDate = new P2PTraderDate();
			creationDate.SetDate();
			creationDate.SetInSeconds();
			
			DebugMessageP2PTrader("setDate: " + creationDate.ToMySqlDate());
			false;
		}
		
		if (date.year > creationDate.year) {
			DebugMessageP2PTrader("exeedet: " + creationDate.ToMySqlDate());
			return true;
		}
		
	    if (date.inSeconds > creationDate.inSeconds) {
			DebugMessageP2PTrader("exeedet: " + creationDate.ToMySqlDate());
			return true;
		}
		DebugMessageP2PTrader("not exeedet: " + creationDate.ToMySqlDate());
        return false;
	}
}