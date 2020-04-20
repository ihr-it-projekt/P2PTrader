class CfgPatches
{
	class P2PTrader
	{
		units[]={};
        weapons[]={};
        requiredVersion=1.0;
        requiredAddons[]={
            "DZ_Data",
            "DZ_Scripts",
            "JM_CF_Scripts"
        };
	};
};

class CfgAddons
{
	class PreloadBanks {};
	class PreloadAddons
	{
		class dayz
		{
			list[] ={};
		};
	};
};

class CfgMods
{
	class P2PTrader
	{
	    dir = "P2PTrader";
        picture = "";
        action = "";
        hideName = 0;
		inputs = "P2PTrader\inputs.xml";
		name = "P2PTrader";
		credits = "TheBuster";
		creditsJson = "P2PTrader/Scripts/Data/Credits.json";
		versionPath = "P2PTrader/scripts/Data/Version.hpp";
		author = "TheBuster";
		authorID = "76561198196317725";
		version = "1.0.33";
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game", "World", "Mission"};

		class defs
		{
            class gameScriptModule
            {
                value="";
                files[]=
                {
                    "P2PTrader/scripts/3_Game"
                };
            };
            class worldScriptModule
            {
                value="";
                files[]=
                {
                    "P2PTrader/scripts/4_World"
                };
            };
			class missionScriptModule
			{
				value = "";
				files[] = {
				        "P2PTrader/scripts/5_Mission"
				};
			};
		};
	};
};
