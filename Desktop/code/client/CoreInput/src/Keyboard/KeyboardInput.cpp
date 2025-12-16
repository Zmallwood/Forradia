//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "KeyboardInput.hpp"

namespace Forradia {
void KeyboardInput::Reset() {
  m_pressed.clear();
}

void KeyboardInput::RegisterKeyPress(SDL_Keycode key) {
  m_pressed.insert(key);
}

void KeyboardInput::RegisterKeyRelease(SDL_Keycode key) {
  m_pressed.erase(key);
}

void KeyboardInput::StartTextInput() {
  SDL_StartTextInput();
}

void KeyboardInput::StopTextInput() {
  SDL_StopTextInput();
  m_textInput.clear();
}

void KeyboardInput::AddTextInput(StringView text) {
  m_textInput += text;
}
}