/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_generation_scene.hpp"
#include "core/gui.hpp"
#include "theme_0/func/world_gen/gen_new_world.hpp"

namespace forr {
  void world_generation_scene::on_enter_derived() {
    get_ston<gui_text_console>().print("Generating new world...");
    gen_new_world();
    get_ston<gui_text_console>().print("World generation completed.");
    get_ston<scene_manager>().go_to_scene("MainScene");
  }
}
