/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "KeyboardInput.hpp"

namespace Forradia {
    auto KeyboardInput::KeyIsPressed(SDL_Keycode key) const -> bool {
        return m_pressed.contains(key);
    }

    auto KeyboardInput::KeyIsPressedPickResult(SDL_Keycode key) -> bool {
        auto result{m_pressed.contains(key)};
        m_pressed.erase(key);
        return result;
    }

    auto KeyboardInput::AnyKeyIsPressedPickResult() -> bool {
        auto result{m_pressed.size() > 0};
        m_pressed.clear();
        return result;
    }
}
