class P2PBaseValidator
{
    protected string errorMessage = "";
    private bool wasValidated = false;
    private bool isValid = false;

    string GetErrorMessage() {
		return errorMessage;
	}

	protected bool DoValidate() {
        return false;
	}

	bool IsValid() {
	    if (!wasValidated) {
	        isValid = DoValidate();
	    }
	    wasValidated = true;

	    return isValid;
	}
}