/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainSceneGUIComponents.hpp"
#include "core/gui_core/GUI.hpp"
#include "core/gui_core/GUIFPSPanel.hpp"
#include "core/gui_core/GUITextConsole.hpp"
#include "core/gui_core/windows/GUIWindow.hpp"
#include "sub/AddMainSceneGUIButtons.hpp"
#include "theme_0/theme_0_mechanics/gui/GUIInventoryWindow.hpp"
#include "theme_0/theme_0_mechanics/gui/GUIPlayerBodyWindow.hpp"
#include "theme_0/theme_0_mechanics/gui/GUIPlayerStatusPanel.hpp"
#include "theme_0/theme_0_mechanics/gui/GUISystemMenu.hpp"

namespace Forradia {
  void AddMainSceneGUIComponents(std::shared_ptr<GUI> mainSceneGUI) {
    mainSceneGUI->AddChildComponent(std::make_shared<GUIPlayerStatusPanel>());

    mainSceneGUI->AddChildComponent(GetSingletonPtr<GUITextConsole>());

    AddMainSceneGUIButtons(mainSceneGUI);

    mainSceneGUI->AddChildComponent(GetSingletonPtr<GUISystemMenu>());

    mainSceneGUI->AddChildComponent(GetSingletonPtr<GUIInventoryWindow>());

    mainSceneGUI->AddChildComponent(GetSingletonPtr<GUIPlayerBodyWindow>());

    mainSceneGUI->AddChildComponent(std::make_shared<GUIFPSPanel>());
  }
}