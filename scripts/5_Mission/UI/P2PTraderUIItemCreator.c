class P2PTraderUIItemCreator {

	Widget layoutRoot;
	
    void P2PTraderUIItemCreator(string layoutRootPath) {
		this.layoutRoot = GetGame().GetWorkspace().CreateWidgets(layoutRootPath);
	}

	Widget GetLayoutRoot() {
	    return this.layoutRoot;
	}

    TextListboxWidget GetTextListboxWidget(string name, Managed eventHandler = null, string functionName = "") {
        TextListboxWidget widget = TextListboxWidget.Cast(layoutRoot.FindAnyWidget(name));

        if (eventHandler && functionName != "") {
            WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(widget, eventHandler, functionName);
        }

        return widget;
    }

    XComboBoxWidget GetXComboBoxWidget(string name) {
        return XComboBoxWidget.Cast(layoutRoot.FindAnyWidget(name));
    }

    EditBoxWidget GetEditBoxWidget(string name) {
        return EditBoxWidget.Cast(layoutRoot.FindAnyWidget(name));
    }

    ItemPreviewWidget GetItemPreviewWidget(string name) {
        return ItemPreviewWidget.Cast(layoutRoot.FindAnyWidget(name));
    }

    MultilineTextWidget GetMultilineTextWidget(string name) {
        return MultilineTextWidget.Cast(layoutRoot.FindAnyWidget(name));
    }

    TextWidget GetTextWidget(string name) {
        return TextWidget.Cast(layoutRoot.FindAnyWidget(name));
    }

    ButtonWidget GetButtonWidget(string name, Managed eventHandler = null, string functionName = "") {
        ButtonWidget button =  ButtonWidget.Cast(layoutRoot.FindAnyWidget(name));

        if (eventHandler && functionName != "") {
            WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(button, eventHandler, functionName);
        }

        return button;
    }
}