class P2PTraderPosition {

    vector position;
    vector orientation;
    string gameObjectType

    void P2PTraderPosition(vector posParam, vector orientationParam, string gameObjectTypeParam) {
        position = posParam;
        orientation = orientationParam;
        gameObjectType = gameObjectTypeParam;
    }

}