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
            categoryNames.Insert("#transmitter");
            categoryNames.Insert("#clothes");
            categoryNames.Insert("#pelt");
            categoryNames.Insert("#ammo");
            categoryNames.Insert("#lights");
            categoryNames.Insert("#mag",;
            categoryNames.Insert("#navigation");
            categoryNames.Insert("#weapon");
            categoryNames.Insert("#build_items");
            categoryNames.Insert("#car",;
            categoryNames.Insert("#store_items");
            categoryNames.Insert("#medicine");
            categoryNames.Insert("#transport");
            categoryNames.Insert("#food");
            categoryNames.Insert("#tent");
            categoryNames.Insert("#fireplace");
            categoryNames.Insert("#weapon_part");
            categoryNames.Insert("#meleeWeapon");
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