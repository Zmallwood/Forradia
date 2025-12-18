/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "KeyboardInput.hpp"
#include "StdAfx.hpp"

namespace Forradia {
  auto KeyboardInput::Reset() -> void {
    m_pressed.clear();
  }

  auto KeyboardInput::RegisterKeyPress(SDL_Keycode key) -> void {
    m_pressed.insert(key);
  }

  auto KeyboardInput::RegisterKeyRelease(SDL_Keycode key) -> void {
    m_pressed.erase(key);
  }

  auto KeyboardInput::StartTextInput() -> void {
    SDL_StartTextInput();
  }

  auto KeyboardInput::StopTextInput() -> void {
    SDL_StopTextInput();
    m_textInput.clear();
  }

  auto KeyboardInput::AddTextInput(StringView text) -> void {
    m_textInput += text;
  }
}
