class P2PTraderExpiredDate extends P2PTraderDate
{

	void P2PTraderExpiredDate(int maxDays) {
		SetDate();
		
		if (maxDays > 364) {
			int yearAdd = Math.Floor(maxDays / 365);
			year = year - yearAdd;
			maxDays = maxDays - yearAdd * 365;
		}
		
		if (maxDays > 29) {
			int monthsAdd = Math.Floor(maxDays / 30);
			
			month = month - monthsAdd;
			
			if (month < 1) {
				month = month + 12;
				year = year - 1;
			}
			
			maxDays = maxDays - monthsAdd * 30;
		}
		
		day = day - maxDays;
		
		if (day < 1) {
			day = day + 30;
			month = month - 1;
			
			if (month < 1) {
				month = month + 12;
				year = year - 1;
			}
		}
		SetInSeconds();
		DebugMessageP2PTrader("Expire date is: " + ToMySqlDate());
	}

}