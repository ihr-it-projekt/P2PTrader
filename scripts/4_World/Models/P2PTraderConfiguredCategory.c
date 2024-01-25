class P2PTraderConfiguredCategory {
    private const static string	SETTINGSFILE = "P2PTraderConfiguredCategory.json";
    ref array<string> categoryNames;

    void P2PTraderConfiguredCategory() {
        if(IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGS_FOLDER_P2P + SETTINGSFILE)) {
            JsonFileLoader<P2PTraderConfiguredCategory>.JsonLoadFile(CONFIGS_FOLDER_P2P + SETTINGSFILE, this);
        } else {
            categoryNames = new array<string>;
            categoryNames.Insert("#no_category");
            SaveFile();
        }
    }

    private void SaveFile() {
        if(IsServerAndMultiplayerP2PTrader()) {
            if(!FileExist(CONFIGS_FOLDER_P2P)) {
                MakeDirectory(CONFIGS_FOLDER_P2P);
            }
            JsonFileLoader<P2PTraderConfiguredCategory>.JsonSaveFile(CONFIGS_FOLDER_P2P + SETTINGSFILE, this);
        }
    }
}
