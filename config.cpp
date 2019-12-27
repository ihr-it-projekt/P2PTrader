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
		inputs = "P2PTrader\inputs.xml";
		dir = "P2PTrader";
		name = "P2PTrader";
		credits = "TheBuster";
		author = "TheBuster";
		authorID = "0";
		version = "0.1";
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
