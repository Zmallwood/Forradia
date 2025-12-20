/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "TextRenderer.hpp"

namespace Forradia {
  auto TextRenderer::Initialize() -> void {
    TTF_Init();
    this->AddFonts();
  }

  auto TextRenderer::AddFonts() -> void {
    auto absFontPath{std::string(SDL_GetBasePath()) + k_defaultFontPath.data()};
    auto fontPathUnixStyle{Replace(absFontPath, '\\', '/')};

    // Iterate over all available font sizes.
    for (auto fontSize : {FontSizes::_20, FontSizes::_26}) {
      auto fontSizeN{static_cast<int>(fontSize)};

      // Open the font file with the specified size.
      auto newFont{std::shared_ptr<TTF_Font>(TTF_OpenFont(fontPathUnixStyle.c_str(), fontSizeN),
                                             SDLDeleter())};

      if (!newFont) {
        PrintLine("Error loading font size " + std::to_string(fontSizeN) +
                  " from: " + fontPathUnixStyle);
        continue;
      }

      m_fonts.insert({fontSize, newFont});
    }
  }

  auto TextRenderer::SetupState() const -> void {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  auto TextRenderer::RestoreState() const -> void {
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}
