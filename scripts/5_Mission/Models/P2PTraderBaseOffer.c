class P2PTraderBaseOffer
{
	static int creationYear;
	static int creationMonth;
	static int creationDay;
	static int creationHour;
	static int creationMinute;
	static int creationSecond;
	
	protected void SetCreationDate() {
        GetHourMinuteSecondUTC(creationHour, creationMinute, creationSecond);
        GetYearMonthDay(creationYear, creationMonth, creationDay);
	}
	
	bool IsExceeded(P2PTraderExpiredDate date) {
	    if (!creationYear) {
	        return false;
	    }

        if (date.year > creationYear) {
            return true;
        }
        if (date.month > creationMonth) {
            return true;
        }
        if (date.day > creationDay) {
            return true;
        }

        if (date.hour > creationHour) {
            return true;
        }
        if (date.minute > creationMinute) {
            return true;
        }
        if (date.second > creationSecond) {
            return true;
        }

        return false;
	}
}