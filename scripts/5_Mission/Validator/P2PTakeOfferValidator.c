class P2PTakeOfferValidator extends P2PBaseValidator {
    private ref P2PTraderPlayerMarketOffer playerMarketOffer;
    private ref P2PTraderPlayerPlayerOffer playerPlayerOffer;
    private string playerId;

    void P2PTakeOfferValidator(P2PTraderPlayerMarketOffer _playerMarketOffer, P2PTraderPlayerPlayerOffer _playerPlayerOffer, string _playerId) {
        this.playerMarketOffer = _playerMarketOffer;
        this.playerPlayerOffer = _playerPlayerOffer;
        this.playerId = _playerId;
    }

    protected override bool DoValidate() {
        if(playerMarketOffer == null) {
            errorMessage = "#offer_not_exists";
            return false;
        } else if(playerPlayerOffer == null) {
            errorMessage = "#player_offer_not_exists";
            return false;
        } else if(playerMarketOffer.GetOwnerId() != playerId) {
            errorMessage = "#you_can_only_use_your_own_order";
            return false;
        } else if(playerPlayerOffer.GetOwnerId() == playerId) {
            errorMessage = "#you_can_not_accept_your_own_order";
            return false;
        }

        return true;
    }
}