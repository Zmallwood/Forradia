/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIPlayerStatusPanel.hpp"
#include "core/rendering/text/TextRenderer.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/Player.hpp"

namespace Forradia {
  void GUIPlayerStatusPanel::RenderDerived() const {
    GUIPanel::RenderDerived();

    auto bounds{GetBounds()};

    GetSingleton<TextRenderer>().DrawString(GetSingleton<Player>().GetName(),
                                            bounds.x + 0.01f, bounds.y + 0.01f,
                                            FontSizes::_26);
  }
}