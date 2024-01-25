class P2PTraderExpiredDate extends P2PTraderDate {

    void P2PTraderExpiredDate(P2PTraderDate date, int maxDays) {
        this.year = date.year;
        this.month = date.month;
        this.day = date.day;
        this.hour = date.hour;
        this.minute = date.minute;
        this.second = date.second;

        if(maxDays > 364) {
            int yearAdd = Math.Floor(maxDays / 365);
            year += yearAdd;
            maxDays -= yearAdd * 365;
        }

        if(maxDays > 29) {
            int monthsAdd = Math.Floor(maxDays / 30);

            month += monthsAdd;

            if(month > 12) {
                month -= 12;
                year += 1;
            }

            maxDays -= monthsAdd * 30;
        }

        day -= maxDays;

        if(day < 1) {
            day = day + 30;
            month -= 1;

            if(month < 1) {
                month += 12;
                year -= 1;
            }
        }
        SetInSeconds();
    }
}
