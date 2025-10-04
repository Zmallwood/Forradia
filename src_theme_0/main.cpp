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

namespace py = pybind11;

void asd() { std::cout << "asd\n"; }

class CppClass {
 public:
  CppClass() { std::cout << "CppClass constructor" << std::endl; }

  void print() { std::cout << "CppClass print" << std::endl; }
};

PYBIND11_EMBEDDED_MODULE(embedded, m) {

  py::class_<CppClass>(m, "CppClass")
      .def(py::init<>())
      .def("print", &CppClass::print);

  m.def("my_function",
        []() { std::cout << "Executing my_function" << std::endl; });

  m.def("func2", &asd);

  m.def("func3", [] {
    py::exec(R"(

      print('Executing func3')
      print('zxc')

      from embedded import CppClass

      ccc = CppClass()
      ccc.print()

    )");
  });

  m.def("test_fn", [] {
    py::eval_file("res/theme_0_scripts/scenes.py");
    py::eval("test_fn()");
  });
}

int main(int argc, char **argv) {
  using namespace forr;

  py::scoped_interpreter guard{}; // start interpreter, dies when out of scope

  auto embedded = py::module::import("embedded");
  embedded.attr("my_function")();
  embedded.attr("func2")();
  embedded.attr("func3")();
  embedded.attr("test_fn")();

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
