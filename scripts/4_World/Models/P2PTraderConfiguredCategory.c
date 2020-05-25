class P2PTraderConfiguredCategory
{
	private const static string	SETTINGSFILE = "P2PTraderConfiguredCategory.json";
	ref array<string> categoryNames;
	
	void P2PTraderConfiguredCategory() {
		if (IsServerAndMultiplayerP2PTrader() && FileExist(CONFIGS_FOLDER_P2P + SETTINGSFILE)) {
            DebugMessageP2PTrader("load file" + SETTINGSFILE);
			JsonFileLoader<P2PTraderConfiguredCategory>.JsonLoadFile(CONFIGS_FOLDER_P2P + SETTINGSFILE, this);
			DebugMessageP2PTrader("Has category items loaded count: " + categoryNames.Count());
        } else {
			categoryNames = new array<string>;
            categoryNames.Insert("#no_category");
			SaveFile();
		}
	}
	
	private void SaveFile(){
        if (IsServerAndMultiplayerP2PTrader()) {
            if (!FileExist(CONFIGS_FOLDER_P2P)) {
                MakeDirectory(CONFIGS_FOLDER_P2P);
                DebugMessageP2PTrader("create folder");
            }
            DebugMessageP2PTrader("save file: " + SETTINGSFILE);
            JsonFileLoader<P2PTraderConfiguredCategory>.JsonSaveFile(CONFIGS_FOLDER_P2P + SETTINGSFILE, this);
        }
    }
}