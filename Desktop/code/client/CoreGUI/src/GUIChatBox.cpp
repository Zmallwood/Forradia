//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "GUIChatBox.hpp"
#include "Color2DRenderer.hpp"
#include "Engine.hpp"
#include "Image2DRenderer.hpp"
#include "Keyboard/KeyboardInput.hpp"
#include "TextRenderer.hpp"

namespace Forradia {
void GUIChatBox::Initialize() {
  auto maxNumLines{this->GetMaxNumLines()};

  for (auto i = 0; i < maxNumLines; i++) {
    m_renderIDsTextLines.push_back(Hash(fmt::format("RenderIDTextLine{}", i)));
  }
}

int GUIChatBox::GetMaxNumLines() const {
  auto bounds{this->GetBounds()};
  return CInt(bounds.height / k_lineHeight - 1);
}

void GUIChatBox::UpdateDerived() {
  GUIPanel::UpdateDerived();

  m_input = _<KeyboardInput>().GetTextInput();
}

void GUIChatBox::RenderDerived() const {
  GUIPanel::RenderDerived();

  auto bounds{this->GetBounds()};
  auto maxNumLines{this->GetMaxNumLines()};
  auto y{bounds.y + k_margin};

  // Loop through the text lines.
  for (auto i = 0; i < maxNumLines; i++) {
    auto index{m_lines.size() - maxNumLines + i};

    if (index < 0 || index >= m_lines.size()) {
      continue;
    }

    auto textLine = m_lines.at(index);

    _<TextRenderer>().DrawString(m_renderIDsTextLines.at(i), textLine, bounds.x + k_margin, y,
                                 FontSizes::_20, false, true);

    y += k_lineHeight;
  }

  auto separatorX{bounds.x + k_margin};
  auto separatorY{bounds.y + bounds.height - k_lineHeight};
  auto separatorWidth{bounds.width - 2 * k_margin};
  auto sepratorHeight{k_separatorHeight};

  _<Color2DRenderer>().DrawLine(k_renderIDSeparator, Palette::GetColor<Hash("Black")>(), separatorX,
                                separatorY, separatorX + separatorWidth, separatorY, sepratorHeight,
                                true);

  if (m_inputActive) {
    // TODO: Calculate the cursor x-coordinate based on the text input.

    auto cursorX{bounds.x};
    auto cursorY{bounds.y + bounds.height - k_lineHeight};
    auto cursorWidth{0.01f};
    auto cursorHeight{k_lineHeight};

    _<Image2DRenderer>().DrawImageByName(k_renderIDInputCursor, "GUIInputCursor", cursorX, cursorY,
                                         cursorWidth, cursorHeight);

    _<TextRenderer>().DrawString(k_renderIDInputText, m_input, cursorX, cursorY, FontSizes::_20,
                                 false, true);
  }
}

void GUIChatBox::Print(StringView text) {
  m_lines.push_back(text.data());
}

void GUIChatBox::EnableInput() {
  _<KeyboardInput>().StartTextInput();

  m_inputActive = true;
}

void GUIChatBox::SubmitInput() {
  // TODO: Act on the typed input.

  if (m_input == "/quit") {
    _<Engine>().Stop();
  }

  _<KeyboardInput>().StopTextInput();

  m_inputActive = false;
  m_input = "";
}
}