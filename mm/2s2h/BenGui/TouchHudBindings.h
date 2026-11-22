#pragma once
#include <array>
#include <cstdint>
#include <string>

// Touch button assignments for the Android integrated touch overlay. Kept in sync with the Java TouchBindings
// class (same action numbers, same key order). These are game actions, not SDL controller bindings: changing
// them never edits the control deck mappings.
namespace TouchHud {
enum Action {
    Disabled,
    ActionA,
    SwordB,
    Target,
    Shield,
    Navi, // Tatl in Majora's Mask
    ItemLeft,
    ItemDown,
    ItemRight,
    ExtraL,
    FirstPerson,
    Pause,
    DpadUp,
    DpadDown,
    DpadLeft,
    DpadRight,
    ToggleMap,
    ManualJump,
    Modifier1,
    Modifier2,
    ActionCount
};

constexpr int BindingCount = 16;

inline constexpr std::array<const char*, BindingCount> Keys = { "a",  "b",  "cl", "cd", "cr", "cu", "z",     "l",
                                                                "r",  "du", "dd", "dl", "dr", "start", "fairy", "map" };

inline constexpr std::array<int, BindingCount> DefaultActions = { ActionA,   SwordB,    ItemLeft, ItemDown,
                                                                  ItemRight, Navi,      Target,   ExtraL,
                                                                  Shield,    DpadUp,    DpadDown, DpadLeft,
                                                                  DpadRight, Pause,     Disabled, Disabled };

// style: 1 = N64, 2 = GameCube, 3 = Modern. The Map action stays off by default until the game side can answer it.
inline int DefaultAction(int style, int index) {
    if (style == 2) {
        if (index == 5 || index == 7) {
            return Disabled;
        }
        if (index == 14) {
            return Navi;
        }
    }
    return DefaultActions.at(index);
}

inline const char* BindingCvar(int style, int index) {
    static const auto paths = [] {
        std::array<std::array<std::string, BindingCount>, 4> result;
        for (int s = 0; s < 4; ++s) {
            for (int i = 0; i < BindingCount; ++i) {
                result[s][i] = "gSettings.TouchControls.Bindings." + std::to_string(s) + "." + Keys[i];
            }
        }
        return result;
    }();
    return paths.at(style).at(index).c_str();
}
} // namespace TouchHud
