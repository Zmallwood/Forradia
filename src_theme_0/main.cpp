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
  //  py::class_<CppClass>(m, "CppClass")
  //      //.def("__init__")
  //      .def("print", &CppClass::print);
  //.def_static("create", &CppClass::create);

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

  //  py::function test_fn = py::reinterpret_borrow<py::function>(
  //      py::module::import("res.theme_0_scripts.scenes").attr("test_fn"));
  //              .attr("test_fn") // import method "min_rosen" from python
  //             [](py::object obj) {
  //               CppClass cppObj;
  //               cppObj.print();
  //               return obj.attr("__dict__").attr("test_fn")(cppObj);
  //             })
  //        .attr("test_fn"));
}

int main(int argc, char **argv) {
  using namespace forr;

  py::scoped_interpreter guard{}; // start interpreter, dies when out of scope

  auto embedded = py::module::import("embedded");
  embedded.attr("my_function")(); // call my_function();
  embedded.attr("func2")();       // call my_function();
  embedded.attr("func3")();       // call my_function();

  // py::function test_fn =
  //     py::reinterpret_borrow<py::function>(py::module::("test_fn", &asd));

  //     test_fn();

  // py::module my_module = py::module_::import("my_module");
  // auto module = py::reinterpret_borrow<py::object>(my_module);
  // auto myFunc = module.attr("my_function");
  // myFunc();

  //  py::function test_fn = py::reinterpret_borrow<py::function>(
  //      py::module::import("my_module").attr("my_function"));

  //  py::function test_fn =
  //      py::reinterpret_borrow<py::function>( // cast from 'object' to
  //      'function
  //                                            // - use `borrow` (copy) or
  //                                            // `steal` (move)
  //          py::module::import("res.theme_0_scripts.scenes")
  //              .attr("test_fn") // import method "min_rosen" from python
  //              "module"
  //          //        pybind11::class_<CppClass>(m, "CppClass")
  //          //        .def("__init__")
  //          //        .def("print")
  //          //        .def_static("create", &CppClass::create);
  //      );

  // test_fn();

  // my_module::test_fn();
  // pybind11::module my_module = py::module_::import("my_module");
  // my_module.attr("test_fn")();

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
