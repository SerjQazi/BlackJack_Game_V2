#pragma once

class Key
{
public:
    enum class Code
    {
        Unknown,
        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        Escape, Return, Backspace, Tab, Space,
        Minus, Equals, LeftBracket, RightBracket,
        Backslash, NonUSHash, Semicolon, Apostrophe, Grave,
        Comma, Period, Slash, CapsLock,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        PrintScreen, ScrollLock, Pause, Insert,
        Home, PageUp, Delete, End, PageDown,
        Right, Left, Down, Up,
        NumLockClear, KeypadDivide, KeypadMultiply, KeypadMinus, KeypadPlus,
        KeypadEnter, Keypad1, Keypad2, Keypad3, Keypad4,
        Keypad5, Keypad6, Keypad7, Keypad8, Keypad9, Keypad0,
        KeypadPeriod,
        NonUSBackslash, Application, Power,
        KeypadEquals, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
        Execute, Help, Menu, Select, Stop, Again, Undo, Cut, Copy, Paste, Find, Mute,
        VolumeUp, VolumeDown, LockingCapsLock, LockingNumLock, LockingScrollLock,
        KeypadComma, KeypadEqualsAS400,
        International1, International2, International3, International4, International5, International6,
        International7, International8, International9,
        AltErase, SysReq, Cancel, Clear, Prior, Return2,
        Separator, Out, Oper, ClearAgain, CrSel, ExSel,
        Keypad00, Keypad000, ThousandsSeparator,
        DecimalSeparator, CurrencyUnit, CurrencySubUnit,
        KeypadLeftParen, KeypadRightParen, KeypadLeftBrace, KeypadRightBrace,
        KeypadTab, KeypadBackspace, KeypadA, KeypadB, KeypadC, KeypadD, KeypadE, KeypadF,
        KeypadXor, KeypadPower, KeypadPercent, KeypadLess, KeypadGreater,
        KeypadAmpersand, KeypadDblAmpersand, KeypadVerticalBar, KeypadDblVerticalBar,
        KeypadColon, KeypadHash, KeypadSpace, KeypadAt, KeypadExclam,
        KeypadMemStore, KeypadMemRecall, KeypadMemClear, KeypadMemAdd, KeypadMemSubtract,
        KeypadMemMultiply, KeypadMemDivide, KeypadPlusMinus, KeypadClear, KeypadClearEntry,
        KeypadBinary, KeypadOctal, KeypadDecimal, KeypadHexadecimal,
        LCtrl, LShift, LAlt, LGUI, RCtrl, RShift, RAlt, RGUI,
        Mode
    };

    Key();
    explicit Key(SDL_Scancode scancode);

    bool operator==(const Key& other) const;

    Code code;
    SDL_Keycode sym;

private:
    static const std::unordered_map<SDL_Scancode, Code> scancodeMap;
};