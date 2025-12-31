/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUICraftingWindow.hpp"
#include "ForradiaEngine/GUICore/GUIScrollableArea.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUICraftingWindow::initialize() -> void
    {
        m_scrollableArea = std::make_shared<GUIScrollableArea>("GUICraftingWindowScrollableArea", 0.0F, 0.0F, 1.0F, 1.0F);
    }
}
