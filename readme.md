[h1]Welcome to Player To Player Trader (P2PTrader)[/h1]

This traders does not need any money. Here players can create offers to other players. 

[h2]How it works:[/h2]

There are tow kinds of offer. 

[h3]Auction:[/h3]

1. Player One create a market offer. The offered items will removed from player inventory. All attachments that are attached to that item will also removed from player. All this will be stored in the market.
2. all other players can now make bids to this offer, same here. The bid items will removed from players and stored into trader.
3. Player One can no take one of this bids, the items inclusive attached items will now created in his inventory. All other offers will now marked as inactive.
4. All players can administrate his own bids/market offers and can take it every time back from market.

[h3]Instant buy: [/h3]

1. A player create a offer from type "Instant buy". 
2. One other player has now to bet to the offer the wanted items. If all wanted items are in the bet then the transaction happen instantly. 
3. The player who created the "Instant buy" will find the items that he has searched in "my bid" -> "accepted" menu.

[h2]Donate:[/h2]
I investigate a lot of time in modding of DayZ. If you want to support me, write a review of the mod and give me positive rating. You can also donate some money via paypal https://www.paypal.com/pools/c/8idQvmteIO .

In case the link above does not work, you can also use: https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=75EW5TD8HJ6YU&source=url

[h2]Special thanks:[/h2]

Many thanks to Sense². He helped me to make my first steps in mod development and took time to give me feedback.

Thanks to the community of https://rasselbande-gaming.com . Here I was able to publish and test my mods.

[h2]Discord[/h2]
TheBuster#5301

[h1]Admin Infos:[/h1]

It is not allowed to publish the mod in any other way without my permission.

This mod works also in Levonia. As server admin you have to configure only the new location for trader.

Hint: Use NOT the default Notepad Editor to make any changes in files. I recommend to use editors like Notepad++.

This mod is complete independent. The CF mod is used that player can change the key to open the trader. In moment there is NO safe zone implemented. 

Ho to configure:

1. Copy the mod to your server
2. Copy from mod "@P2PTrader\Keys" folder the key into "DayZServer\keys"
3. start your server first time
4. if server is ready, shout down your server
5. Enter into your server profiles folder. There is a new folder named: "P2PTrader" 
6. Enter "P2PTrader" folder
7. There are three generated files
7.1 P2PTraderConfigParams.json content:
DO NOT COPY THIS. IT WILL AUTOMATICALLY CREATED AT FIRST SERVER START
[code]{
    "maxMarketOffersPerPlayer": 3, //Count how many market offers can create a player
    "maxBidsPerPlayer": 3, // Count how many bids a player can make to market offers
    "maxDistanceToTrader": 3, // Max distance to trader position to be able to open the Trader menu.
    "traderCanOpenFromEveryware": 1, // Trader Menu can be opened from everywhere this can help that players can take a look from everywhere into trader 0 = off 1 = on
    "playerCanTradeFromEveryware": 1, // Player can from everywhere trade in trader. Attention can be used to teleport items and option traderCanOpenFromEveryware must be 1; 0 = off 1 = on
	"exceededTimeCheckInterval": 5, //How often in minutes a check happens for exceeded offers
    "isEnabledExceededCheck": 0,// Check for exceeded offers is enabled 0 = off 1 = on
    "spawnExceededToGround": 0,// Exceeded offers should spawn on ground, if this is off the offers will only deleted and the items get lost.  0 = off 1 = on
    "offerWillExpireAfterDays": 30, // Offer expired after days. Default is 30 Days
    "spawnPositionExceededOffers": [ // The spawn position of offers when the offer is exceeded and the spawnExceededToGround is 1
        [
            6575,
            6,
            2450
        ]
    ],
    "traderPositions": [ // here you configure multiple locations for trader. Default location is in Cherno in near of Major Hall at the first advertisement pillar
        {
            "position": [
                6575,
                6,
                2450
            ],
            "orientation": [
                49,
                0,
                0
            ],
            "gameObjectType": "not_spawn" // no spawn means no object for trader will be spawned but you can open the trader menu without object, you can replace the string with other building types like "bldr_Misc_AdvertColumn"
        }
    ],
    "useItemsConfigForPlayerInventory": 0, // Use the P2PTraderItemsConfig that player can only create offers for types that mention in the config. 0 = off 1 = on
	"defaultKey": 48, // The number of Key. You will find the matching numbers in possibleKeyBindingsMap. Will used only when useServerKeyBind is active.
    "useServerKeyBind": 0, //Option to define the key to open the trader from server side. Attention: When you use this option you have to define the default key. User can override it, but he has to do for every server join.  0 = off 1 = on
	"enabledOfferTypes": [ // Here you can setup what kind of market offers can be created. Remove that one you don`t want to have.
        "instant_buy",
        "auction"
    ]
    "possibleKeyBindingsMap": {
		"48": "B"
		...// A list of all possible key combination
	}
    "configVersion": "2" //Internal version check. NEVER CHANGE THIS VALUE!!!!
}[/code]

7.2 P2PTraderItemsConfig.json
This file contain the items that can be used in "create offer" view that a player want to have. The file is empty when you start the server. You can replace this file with the P2PTraderItemsConfig.json or you can generate one from your types.xml with the online converter: https://dayz-p2ptrader.com/types-xml-converter

7.3 P2PTraderStock.json
This file works as a database. Here are stored any market offers and bids. I don´t recommend to edit this file manually. It can happen that you destroy the file.

