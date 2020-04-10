class P2PTraderKeyCodeMatch
{
    ref map<int, string> keyCodes;

    void P2PTraderKeyCodeMatch() {
        keyCodes = new map<int, string>;


        keyCodes.Set(KeyCode.KC_MINUS,"MINUS");   ///< - on main keyboard
        keyCodes.Set(KeyCode.KC_EQUALS,"EQUALS");
        keyCodes.Set(KeyCode.KC_BACK,"BACK");    ///< backspace
        keyCodes.Set(KeyCode.KC_TAB,"TAB");
        keyCodes.Set(KeyCode.KC_Q,"Q");
        keyCodes.Set(KeyCode.KC_W,"W");
        keyCodes.Set(KeyCode.KC_E,"E");
        keyCodes.Set(KeyCode.KC_R,"R");
        keyCodes.Set(KeyCode.KC_T,"T");
        keyCodes.Set(KeyCode.KC_Y,"Y");
        keyCodes.Set(KeyCode.KC_U,"U");
        keyCodes.Set(KeyCode.KC_I,"I");
        keyCodes.Set(KeyCode.KC_O,"O");
        keyCodes.Set(KeyCode.KC_P,"P");
        keyCodes.Set(KeyCode.KC_LBRACKET,"LBRACKET");
        keyCodes.Set(KeyCode.KC_RBRACKET,"RBRACKET");
        keyCodes.Set(KeyCode.KC_RETURN,"RETURN");   ///< Enter on main keyboard
        keyCodes.Set(KeyCode.KC_LCONTROL,"LCONTROL");
        keyCodes.Set(KeyCode.KC_A,"A");
        keyCodes.Set(KeyCode.KC_S,"S");
        keyCodes.Set(KeyCode.KC_D,"D");
        keyCodes.Set(KeyCode.KC_F,"F");
        keyCodes.Set(KeyCode.KC_G,"G");
        keyCodes.Set(KeyCode.KC_H,"H");
        keyCodes.Set(KeyCode.KC_J,"J");
        keyCodes.Set(KeyCode.KC_K,"K");
        keyCodes.Set(KeyCode.KC_L,"L");
        keyCodes.Set(KeyCode.KC_SEMICOLON,";");
        keyCodes.Set(KeyCode.KC_APOSTROPHE,"´");
        keyCodes.Set(KeyCode.KC_GRAVE,"`");    ///< accent grave
        keyCodes.Set(KeyCode.KC_LSHIFT,"LSHIFT");
        keyCodes.Set(KeyCode.KC_BACKSLASH,"BACKSLACH");
        keyCodes.Set(KeyCode.KC_Z,"z");
        keyCodes.Set(KeyCode.KC_X,"X");
        keyCodes.Set(KeyCode.KC_C,"C");
        keyCodes.Set(KeyCode.KC_V,"V");
        keyCodes.Set(KeyCode.KC_B,"B");
        keyCodes.Set(KeyCode.KC_N,"N");
        keyCodes.Set(KeyCode.KC_M,"M");
        keyCodes.Set(KeyCode.KC_COMMA,"COMMA");
        keyCodes.Set(KeyCode.KC_PERIOD,"PERIOD");   ///< . on main keyboard
        keyCodes.Set(KeyCode.KC_SLASH,"SLASH");    ///< / on main keyboard
        keyCodes.Set(KeyCode.KC_RSHIFT,"RSHIFT");
        keyCodes.Set(KeyCode.KC_MULTIPLY,"MULTIPLY");    ///< * on numeric keypad
        keyCodes.Set(KeyCode.KC_LMENU,"LMENU");    ///< left Alt
        keyCodes.Set(KeyCode.KC_SPACE,"SPACE");
        keyCodes.Set(KeyCode.KC_CAPITAL,"CAPITAL");
        keyCodes.Set(KeyCode.KC_F1,"F1");
        keyCodes.Set(KeyCode.KC_F2,"F2");
        keyCodes.Set(KeyCode.KC_F3,"F3");
        keyCodes.Set(KeyCode.KC_F4,"F4");
        keyCodes.Set(KeyCode.KC_F5,"F5");
        keyCodes.Set(KeyCode.KC_F6,"F6");
        keyCodes.Set(KeyCode.KC_F7,"F7");
        keyCodes.Set(KeyCode.KC_F8,"F8");
        keyCodes.Set(KeyCode.KC_F9,"F9");
        keyCodes.Set(KeyCode.KC_F10,"F10");
        keyCodes.Set(KeyCode.KC_NUMLOCK,"NUMLOCK");
        keyCodes.Set(KeyCode.KC_SCROLL,"SCROLL");    ///< Scroll Lock
        keyCodes.Set(KeyCode.KC_NUMPAD7,"NUMPAD7");
        keyCodes.Set(KeyCode.KC_NUMPAD8,"NUMPAD8");
        keyCodes.Set(KeyCode.KC_NUMPAD9,"NUMPAD9");
        keyCodes.Set(KeyCode.KC_SUBTRACT,"SUBTRACT");    ///< - on numeric keypad
        keyCodes.Set(KeyCode.KC_NUMPAD4,"NUMPAD4");
        keyCodes.Set(KeyCode.KC_NUMPAD5,"NUMPAD5");
        keyCodes.Set(KeyCode.KC_NUMPAD6,"NUMPAD6");
        keyCodes.Set(KeyCode.KC_ADD,"ADD");    ///< + on numeric keypad
        keyCodes.Set(KeyCode.KC_NUMPAD1,"NUMPAD1");
        keyCodes.Set(KeyCode.KC_NUMPAD2,"NUMPAD2");
        keyCodes.Set(KeyCode.KC_NUMPAD3,"NUMPAD3");
        keyCodes.Set(KeyCode.KC_NUMPAD0,"NUMPAD0");
        keyCodes.Set(KeyCode.KC_DECIMAL,"DECIMAL");   ///< . on numeric keypad
        keyCodes.Set(KeyCode.KC_OEM_102,"OEM_102");    ///< < > | on UK/Germany keyboards
        keyCodes.Set(KeyCode.KC_F11,"F11");
        keyCodes.Set(KeyCode.KC_F12,"F12");
        keyCodes.Set(KeyCode.KC_NUMPADEQUALS,"NUMPADEQUALS");    ///< = on numeric keypad (NEC PC98)
        keyCodes.Set(KeyCode.KC_PREVTRACK,"PREVTRACK");    ///< Previous Track (DIKC_CIRCUMFLEX on Japanese keyboard)
        keyCodes.Set(KeyCode.KC_AT,"AT");    ///<                     (NEC PC98)
        keyCodes.Set(KeyCode.KC_COLON,"COLON");    ///<                     (NEC PC98)
        keyCodes.Set(KeyCode.KC_UNDERLINE,"UNDERLINE");    ///<                     (NEC PC98)
        keyCodes.Set(KeyCode.KC_STOP,"STOP");    ///<                     (NEC PC98)
        keyCodes.Set(KeyCode.KC_AX,"AX");    ///<                     (Japan AX)
        keyCodes.Set(KeyCode.KC_UNLABELED,"UNLABELED");    ///<                        (J3100)
        keyCodes.Set(KeyCode.KC_NEXTTRACK,"NEXTTRACK");    ///< Next Track
        keyCodes.Set(KeyCode.KC_NUMPADENTER,"NUMPADENTER");    ///< Enter on numeric keypad
        keyCodes.Set(KeyCode.KC_RCONTROL,"RCONTROL");
        keyCodes.Set(KeyCode.KC_MUTE,"MUTE");    ///< Mute
        keyCodes.Set(KeyCode.KC_CALCULATOR,"CALCULATOR");    ///< Calculator
        keyCodes.Set(KeyCode.KC_NUMPADCOMMA,"NUMPADCOMMA");    ///< , on numeric keypad (NEC PC98)
        keyCodes.Set(KeyCode.KC_DIVIDE,"DIVIDE");    ///< / on numeric keypad
        keyCodes.Set(KeyCode.KC_SYSRQ,"SYSRQ");
        keyCodes.Set(KeyCode.KC_RMENU,"RMENU");    ///< right Alt
        keyCodes.Set(KeyCode.KC_PAUSE,"PAUSE");    ///< Pause
        keyCodes.Set(KeyCode.KC_HOME,"HOME");    ///< Home on arrow keypad
        keyCodes.Set(KeyCode.KC_UP,"UP");    ///< UpArrow on arrow keypad
        keyCodes.Set(KeyCode.KC_PRIOR,"PRIOR");    ///< PgUp on arrow keypad
        keyCodes.Set(KeyCode.KC_LEFT,"LEFT");    ///< LeftArrow on arrow keypad
        keyCodes.Set(KeyCode.KC_RIGHT,"RIGHT");    ///< RightArrow on arrow keypad
        keyCodes.Set(KeyCode.KC_END,"END");    ///< End on arrow keypad
        keyCodes.Set(KeyCode.KC_DOWN,"DOWN");    ///< DownArrow on arrow keypad
        keyCodes.Set(KeyCode.KC_NEXT,"NEXT");    ///< PgDn on arrow keypad
        keyCodes.Set(KeyCode.KC_INSERT,"INSERT");    ///< Insert on arrow keypad
        keyCodes.Set(KeyCode.KC_DELETE,"DELETE");    ///< Delete on arrow keypad
    }
}
