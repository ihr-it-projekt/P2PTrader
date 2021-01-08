class P2PTraderDate
{
	static const int YEAR_IN_SECONDS = 31556952;
	static const int MONTH_IN_SECONDS = 2419200;
	static const int DAY_IN_SECONDS = 86400;
	static const int HOUR_IN_SECONDS = 3600;
	static const int MINUTE_IN_SECONDS = 60;
	
	int year;
    int month;
    int day;
	int hour;
    int minute;
    int second;
	int inSeconds;
	
	void SetDate() {
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecondUTC(hour, minute, second);
	}

	bool IsAfter(P2PTraderDate expiredDate) {
	    if (expiredDate.year > year) {
	        return false;
	    }

	    if (expiredDate.year == year && expiredDate.month > month) {
	        return false;
	    }

	    if (expiredDate.year == year && expiredDate.month == month && expiredDate.day > day) {
	        return false;
	    }

	    if (expiredDate.year == year && expiredDate.month == month && expiredDate.day == day && expiredDate.hour > hour) {
	        return false;
	    }

	    if (expiredDate.year == year && expiredDate.month == month && expiredDate.day == day && expiredDate.hour == hour && expiredDate.minute > minute) {
	        return false;
	    }

	    if (expiredDate.year == year && expiredDate.month == month && expiredDate.day == day && expiredDate.hour == hour && expiredDate.minute == minute && expiredDate.second > second) {
	        return false;
	    }

	    return true;
	}
	
	void SetInSeconds() {
		inSeconds = month * MONTH_IN_SECONDS + day * DAY_IN_SECONDS + hour * HOUR_IN_SECONDS + minute * MINUTE_IN_SECONDS + second;
	}
	
	string ToMySqlDate() {
		return year.ToStringLen(4) + "-" +month.ToStringLen(2) + "-" +day.ToStringLen(2) + " " +hour.ToStringLen(2) + ":" +minute.ToStringLen(2) + ":" + second.ToStringLen(2));
	}
}
