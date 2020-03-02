let xmlParser = require("xml2json");

let fs = require('fs');
let xmlString = fs.readFileSync('types.xml', 'utf8');
let objects = JSON.parse(xmlParser.toJson(xmlString));
let types = [];
objects.types.type.forEach(type => {
  if (type.name.includes("ZmbM_") || type.name.includes("ZmbF")) {
    return;
  }
  types.push(type.name);
});

let json = JSON.stringify({items:types});
fs.writeFileSync('P2PTraderItemsConfig.json', json);
