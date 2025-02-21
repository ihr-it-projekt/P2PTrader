class P2PTraderItemMoveListener extends Managed {
    ButtonWidget buttonSourceToTarget;
    ButtonWidget buttonTargetToSource;
    TextListboxWidget source;
    TextListboxWidget target;
    EditBoxWidget minQuantity;
    EditBoxWidget minHealth;
    ref P2PTraderPreviewWindow previewWindow;
    bool move;
    bool addTypeToTranslation;

    void P2PTraderItemMoveListener(ButtonWidget _buttonSourceToTarget, ButtonWidget _buttonTargetToSource, TextListboxWidget _source, TextListboxWidget _target, bool _move, ItemPreviewWidget _peviewWidget, MultilineTextWidget _description, P2PItemService itemService, EditBoxWidget _minQuantity = null, EditBoxWidget _minHealth = null) {
        this.buttonSourceToTarget = _buttonSourceToTarget;
        this.buttonTargetToSource = _buttonTargetToSource;
        this.source = _source;
        this.target = _target;
        this.move = _move;
        this.minQuantity = _minQuantity;
        this.minHealth = _minHealth;
        this.addTypeToTranslation = itemService.configParams.enableOrigenItemsNameInView;
        previewWindow = new P2PTraderPreviewWindow(_peviewWidget, _description, itemService);
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonSourceToTarget, this, "MoveSourceToTarget");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(buttonTargetToSource, this, "MoveTargetToSource");

        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(source, this, "GetSourceItem");
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(target, this, "GetTargetItem");
    }

    bool MoveSourceToTarget(Widget w, int x, int y, int button) {
        MoveItemFromListWidgetToListWidget(source, target, buttonSourceToTarget, move, addTypeToTranslation);

        return false;
    }

    bool MoveTargetToSource(Widget w, int x, int y, int button) {
        MoveItemFromListWidgetToListWidget(target, source, buttonTargetToSource, true, addTypeToTranslation);

        return false;
    }

    bool GetSourceItem(Widget w, int x, int y, int button) {
        P2PTraderItem item = CheckButton(source, buttonSourceToTarget);
        previewWindow.UpdatePreview(item);

        return false;
    }

    bool GetTargetItem(Widget w, int x, int y, int button) {
        P2PTraderItem item = CheckButton(target, buttonTargetToSource);
        previewWindow.UpdatePreview(item);
        return false;
    }

    private P2PTraderItem CheckButton(TextListboxWidget widget, ButtonWidget button) {
        int pos = widget.GetSelectedRow();

        if(pos == -1) {
            return null;
        }
        P2PTraderItem item;
        widget.GetItemData(pos, 0, item);


        button.Show(false);
        if(item) {
            button.Show(true);
            return item;
        }

        return null;
    }

    private void MoveItemFromListWidgetToListWidget(TextListboxWidget sourceWidget, TextListboxWidget targetWidget, ButtonWidget button, bool mustMove, bool _addTypeToTranslation) {
        int pos = sourceWidget.GetSelectedRow();
        if(pos == -1) {
            return;
        }
        P2PTraderItem item;
        sourceWidget.GetItemData(pos, 0, item);

        if(item) {
            if(!mustMove && minHealth) {
                item.GetItem().health = minHealth.GetText().ToFloat();
            }
            if(!mustMove && minQuantity) {
                item.GetItem().quantity = minQuantity.GetText().ToFloat();
            }

            item.UpdateTranslation(_addTypeToTranslation);

            if(targetWidget) {
                targetWidget.AddItem(item.GetTranslation(), item, 0);
            }

            if(mustMove) {
                sourceWidget.RemoveRow(pos);

                int countItems = sourceWidget.GetNumItems();

                int newItemNumber = pos;
                if(countItems == 0) {
                    newItemNumber = -1;
                    button.Show(false);
                } else if(newItemNumber >= countItems) {
                    newItemNumber = countItems - 1;
                } else if(countItems == 1) {
                    newItemNumber = 0;
                }

                sourceWidget.SelectRow(newItemNumber);

                if(-1 != newItemNumber) {
                    item = CheckButton(sourceWidget, button);
                    previewWindow.UpdatePreview(item);
                }
            }
        } else {
            button.Show(false);
        }

    }
}
