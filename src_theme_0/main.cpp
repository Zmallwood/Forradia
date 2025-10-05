/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "engine.hpp"
#include "game_props.hpp"
#include "scenes.hpp"
#include "world_struct.hpp"

using namespace forr;
namespace py = pybind11;

void asd() { std::cout << "asd\n"; }

class CppClass {
 public:
  CppClass() { std::cout << "CppClass constructor" << std::endl; }

  void print() { std::cout << "CppClass print" << std::endl; }
};

class i_scene_publicist : public i_scene {
 public:
  using i_scene::init_derived;
  using i_scene::on_enter_derived;
  using i_scene::render_derived;
  using i_scene::update_derived;
};

class py_i_scene : public i_scene {
 public:
  using i_scene::on_enter_derived;
  using i_scene::render_derived;
  using i_scene::update_derived;
  void init_derived() override {
    PYBIND11_OVERRIDE(
        void,         /* Return type */
        i_scene,      /* Parent class */
        init_derived, /* Name of function in C++ (must match Python name) */
                      /* Argument(s) */
    );
  }
};

PYBIND11_EMBEDDED_MODULE(embedded, m) {

  py::class_<CppClass>(m, "CppClass")
      .def(py::init<>())
      .def("print", &CppClass::print);

  py::class_<i_scene, py_i_scene>(m, "py_i_scene")
      .def(py::init<>())
      .def("init", &i_scene::init)
      .def("set_action", &i_scene::set_action)
      .def("set_action2", [](py_i_scene &self,
                            py::function f) { self.set_action([=] { f(); }); })
      //.def("set_action", &py_i_scene::set_action)
      .def("init_derived", &i_scene_publicist::init_derived);
  //.def("update", &py_i_scene::update)
  //.def("render", &py_i_scene::render)
  //.def("on_enter", &py_i_scene::on_enter)
  //.def("init_derived", &py_i_scene::init_derived);
  //      .def("on_enter_derived", &py_i_scene::on_enter_derived)
  //      .def("update_derived", &py_i_scene::update_derived)
  //      .def("render_derived", &py_i_scene::render_derived);
  //.def("gui", &i_scene_publicist::gui);
  //      .def("update", &i_scene::update)
  //      .def("render", &i_scene::render)
  //      .def("update_derived", &i_scene_publicist::update_derived)
  //      .def("render_derived", &i_scene_publicist::render_derived);

  py::class_<scene_mngr>(m, "scene_mngr")
      .def(py::init<>())
      .def("add_scene", &scene_mngr::add_scene)
      .def("go_to_scene", &scene_mngr::go_to_scene);
  //.def("update_curr_scene", &scene_mngr::update_curr_scene);

  m.def(
      "get_scene_mngr", []() -> scene_mngr & { return _<scene_mngr>(); },
      py::return_value_policy::reference);

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

  m.def("setup_scenes", [] {
    py::eval_file("res/theme_0_scripts/scenes.py");
    py::eval("setup_scenes()");
  });

  m.def("get_scenes", [] {
    py::eval_file("res/theme_0_scripts/scenes.py");
    return py::eval("get_scenes()");
  });
}

int main(int argc, char **argv) {
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
  auto scenes = embedded.attr("get_scenes")().cast<vec<i_scene>>();
  _<scene_mngr>().add_scene("intro_scene_TEST", scenes.at(0));
  // embedded.attr("setup_scenes")();
  return 0;
  //
  //  _<scene_mngr>().go_to_scene("intro_scene_TEST");

  _<world>().init(_<game_props>().k_w_area_sz, _<game_props>().k_world_scaling);
  _<engine>().run();
  return 0;
}
