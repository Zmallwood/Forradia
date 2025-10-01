/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "main_menu_scene.hpp"
#include "core/rendering/images/image_renderer.hpp"
#include "sub/add_main_menu_scene_gui_components/add_main_menu_scene_gui_components.hpp"

namespace forr {
  void MainMenuScene::InitializeDerived() {
    AddMainMenuSceneGUIComponents(GetGUI());
  }

  void MainMenuScene::UpdateDerived() {}

  void MainMenuScene::RenderDerived() const {
    GetSingleton<ImageRenderer>().DrawImage("DefaultSceneBackground", 0.0f,
                                            0.0f, 1.0f, 1.0f);
    GetSingleton<ImageRenderer>().DrawImageWithAutoHeight("ForradiaLogo", 0.35f,
                                                          0.1f, 0.3f);
  }
}
