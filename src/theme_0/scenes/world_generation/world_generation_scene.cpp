/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_generation_scene.hpp"
#include "core/gui_core/gui_text_console.hpp"
#include "core/scenes_core/scene_manager.hpp"
#include "theme_0/theme_0_mechanics/world_generation/generate_new_world.hpp"

namespace forr {
  void world_generation_scene::on_enter_derived() {
    GetSingleton<gui_text_console>().print("Generating new world...");
    GenerateNewWorld();
    GetSingleton<gui_text_console>().print("World generation completed.");
    GetSingleton<scene_manager>().go_to_scene("MainScene");
  }
}
