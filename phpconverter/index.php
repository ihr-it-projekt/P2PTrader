<?php
$items = null;
$errors = null;
libxml_use_internal_errors(true);

session_start();
$counter_name = "counter.txt";

if (!file_exists($counter_name)) {
    $f = fopen($counter_name, "w");
    fwrite($f,"10");
    fclose($f);
}

$f = fopen($counter_name,"r");
$counterVal = fread($f, filesize($counter_name));
fclose($f);

if (isset($_POST['xml']) && $_POST['xml']) {
    $exclude = explode(',', $_POST['exclude']);
    $xml = simplexml_load_string($_POST['xml']);
    if (false === $xml) {
        echo "Failed loading XML\n";
        foreach (libxml_get_errors() as $error) {
            $errors .= "\t" . $error->message;
        }
    } else {
        $json = json_encode($xml); // convert the XML string to JSON
        $array = json_decode($json, true);
        $output = [];
        $ignoredCount = 0;
        if (is_array($array)) {
            foreach ($array as $types) {
                foreach ($types as $type) {
                    if (array_key_exists("@attributes", $type) && array_key_exists('name', $type["@attributes"])) {
                        $value = $type["@attributes"]['name'];
                        $excludeValue = false;
                        if (is_array($exclude)) {
                            foreach ($exclude as $ex) {
                                if (false !== strpos($value, trim($ex))) {
                                    $excludeValue = true;
                                    $ignoredCount++;
                                }
                            }
                        }

                        if ($excludeValue) {
                            continue;
                        }
                        array_push($output, $value);
                    }
                }
            }
            $items = new stdClass();
            $items->items = $output;
            $counterVal++;
            $f = fopen($counter_name, "w");
            fwrite($f, $counterVal);
            fclose($f);
        }
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>P2PTrader (Player to Player Trader)</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css">
</head>

<body>
<div class="container">
    <div class="row">
        <div class="col">
            <h1>P2PTrader (Player to Player Trader) types.xml converter</h1>
        </div>
    </div>
    <?php if ($errors) { ?>
        <div class="row">
            <div class="col">
                <div class="form-group row">
                    <div class="offset-4 col-8">
                        <div class="alert alert-danger" role="alert">
                            XML Errors
                            <?php echo $errors ?>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    <?php } ?>

    <div class="row">
        <div class="col">
            <form target="_self" method="post">
                <div class="form-group row">
                    <label class="col-4 col-form-label" for="textarea">XML Input</label>
                    <div class="col-8">
                    <textarea id="xml" name="xml" cols="40" rows="5" class="form-control"
                              aria-describedby="textareaHelpBlock" required="required"></textarea>
                        <span id="textareaHelpBlock" class="form-text text-muted">Put your valid XML content in this field and press "convert"</span>
                    </div>
                </div>
                <div class="form-group row">
                    <label for="textarea1" class="col-4 col-form-label">exclude from inport</label>
                    <div class="col-8">
                    <textarea id="exclude" name="exclude" cols="40" rows="5" class="form-control"
                              aria-describedby="textarea1HelpBlock">ZmbM_,ZmbF_</textarea>
                        <span id="textarea1HelpBlock" class="form-text text-muted">Put here comma separated strings in that should not write into the output file. Like "ZmbM_,ZmbF_". Every item that contain that pattern will excluded.</span>
                    </div>
                </div>
                <?php
                if ($items) {
                    ?>
                    <div class="form-group row">
                        <label for="json" class="col-4 col-form-label">JSON output</label>
                        <div class="col-8">
                        <textarea id="json" name="json" cols="40" rows="5" class="form-control"
                                  aria-describedby="jsonHelpBlock"><?php echo json_encode($items) ?></textarea>
                            <span id="jsonHelpBlock" class="form-text text-muted">Copy that output to your P2PTraderItemsConfig.json</span>
                        </div>
                    </div>

                    <div class="form-group row">
                        <div class="offset-4 col-8">
                            <div class="alert alert-success" role="alert">
                                <?php echo $ignoredCount ?> entry´s are ignored.
                            </div>
                        </div>
                    </div>
                <?php } ?>
                <div class="form-group row">
                    <div class="offset-4 col-8">
                        <button name="submit" type="submit" class="btn btn-primary">convert</button>
                    </div>
                </div>
            </form>
        </div>
    </div>
    <div class="row">
        <div class="col">
            <div class="form-group row">
                <div class="offset-4 col-8">
                    <div class="alert alert-success" role="alert">
                        <?php echo $counterVal ?> successful converted types.xml
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class="row">
        <div class="col">
            <h2>Do you see my other mods?</h2>
        </div>
    </div>
    <div class="row">
        <div class="col">
            <div class="card" style="width: 30rem;">
                <img class="card-img-top"
                     src="https://steamuserimages-a.akamaihd.net/ugc/789750822994913619/E405FD93F63CE007FA7258D3F5C26B5A5A00DC1D/"
                     alt="Troll Pointer">
                <div class="card-body">
                    <h5 class="card-title">Troll Pointer</h5>
                    <p class="card-text">This multilingual mod is designed to allow players to report other players who
                        do not follow the server rules .
                    </p>
                    <a href="https://steamcommunity.com/sharedfiles/filedetails/?id=1940465550" target="_blank" class="btn btn-primary">See
                        on Steam</a>
                </div>
            </div>
        </div>
        <div class="col">
            <div class="card" style="width: 30rem;">
                <img class="card-img-top"
                     src="https://steamuserimages-a.akamaihd.net/ugc/789750822994820003/45DBF116952FC883DCC36A04C389F7FFB8216722/"
                     alt="DayZCasinoV2">
                <div class="card-body">
                    <h5 class="card-title">DayZCasinoV2</h5>
                    <p class="card-text">Do you know it? You have been back to the Trader and don't remember where to
                        put your rubles?? ...
                    </p>
                    <a href="https://steamcommunity.com/sharedfiles/filedetails/?id=1940425039" target="_blank" class="btn btn-primary">See
                        on Steam</a>
                </div>
            </div>
        </div>
    </div>
</div>
</body>
</html>