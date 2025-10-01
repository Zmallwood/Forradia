/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "add_main_menu_scene_gui_buttons.hpp"
#include "core/engine/engine.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_button.hpp"
#include "core/scenes_core/scene_manager.hpp"

namespace forr {
  void AddMainMenuSceneGUIButtons(SharedPtr<GUI> mainMenuSceneGUI) {
    mainMenuSceneGUI->AddChildComponent(
        std::make_shared<GUIButton>(0.45f, 0.36f, 0.1f, 0.04f, "New game", [] {
          GetSingleton<SceneManager>().GoToScene("WorldGenerationScene");
        }));

    mainMenuSceneGUI->AddChildComponent(
        std::make_shared<GUIButton>(0.45f, 0.44f, 0.1f, 0.04f, "Quit",
                                    [] { GetSingleton<Engine>().Stop(); }));
  }
}