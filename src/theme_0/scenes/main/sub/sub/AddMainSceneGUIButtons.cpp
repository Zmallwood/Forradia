/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainSceneGUIButtons.hpp"
#include "sub/AddMainSceneInventoryWindowButton.hpp"
#include "sub/AddMainScenePlayerBodyWindowButton.hpp"
#include "sub/AddMainSceneSystemWindowButton.hpp"

namespace Forradia {
  void AddMainSceneGUIButtons(SharedPtr<GUI> mainSceneGUI) {
    AddMainScenePlayerBodyWindowButton(mainSceneGUI);

    AddMainSceneInventoryWindowButton(mainSceneGUI);

    AddMainSceneSystemWindowButton(mainSceneGUI);
  }
}