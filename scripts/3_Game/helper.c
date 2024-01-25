static void DebugMessageP2PTrader(string message) {
    if(P2P_TRADER_DEBUG) {
        int hour;
        int minute;
        int second;
        int inSeconds;

        GetHourMinuteSecondUTC(hour, minute, second);
        Print("[P2PTrader DEBUG] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
        GetGame().AdminLog("[P2PTrader DEBUG] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
    }
}

static void P2PLog(string message) {
    int hour;
    int minute;
    int second;
    int inSeconds;

    GetHourMinuteSecondUTC(hour, minute, second);
    Print("[P2PTrader] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
    GetGame().AdminLog("[P2PTrader] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
}

static bool IsServerP2PTrader() {
    return GetGame().IsServer();
}

static bool IsMultiplayerP2PTrader() {
    return GetGame().IsMultiplayer();
}

static bool IsServerAndMultiplayerP2PTrader() {
    return IsMultiplayerP2PTrader() && IsServerP2PTrader();
}

static bool IsClientOrNotMultiplayerP2PTrader() {
    return !IsMultiplayerP2PTrader() || GetGame().IsClient();
}