/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "engine.hpp"
#include "game_props.hpp"
#include "scenes.hpp"
#include "world_struct.hpp"
#include <pybind11/embed.h> // python interpreter
#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // type conversion

int main(int argc, char **argv) {
  using namespace forr;
  namespace py = pybind11;

  py::scoped_interpreter guard{}; // start interpreter, dies when out of scope

  py::function test_fn =
      py::reinterpret_borrow<py::function>( // cast from 'object' to 'function -
                                            // use `borrow` (copy) or `steal`
                                            // (move)
          py::module::import("res.theme_0_scripts.scenes")
              .attr("test_fn") // import method "min_rosen" from python "module"
      );

  test_fn();

  _<engine>().init(_<game_props>().k_game_win_title,
                   _<game_props>().k_clear_color);
  _<scene_mngr>().add_scene("intro_scene", _<intro_scene>());
  _<scene_mngr>().add_scene("main_menu_scene", _<main_menu_scene>());
  _<scene_mngr>().add_scene("world_gen_scene", _<world_gen_scene>());
  _<scene_mngr>().add_scene("main_scene", _<main_scene>());
  _<scene_mngr>().go_to_scene("intro_scene");
  _<world>().init(_<game_props>().k_w_area_sz, _<game_props>().k_world_scaling);
  _<engine>().run();
  return 0;
}
