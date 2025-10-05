/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "engine.hpp"
#include "game_props.hpp"
#include "rend.hpp"
#include "scenes.hpp"
#include "world_struct.hpp"

using namespace forr;
namespace py = pybind11;

void asd() { std::cout << "asd\n"; }

PYBIND11_EMBEDDED_MODULE(embedded, m) {

  py::class_<i_scene>(m, "i_scene")
      .def(py::init<>())
      .def("init", &i_scene::init)
      .def("set_action", &i_scene::set_action)
      .def("set_init_derived",
           [](i_scene &self, py::function f) {
             self.set_init_derived([=] { f(); });
           })
      .def("set_on_enter_derived",
           [](i_scene &self, py::function f) {
             self.set_on_enter_derived([=] { f(); });
           })
      .def("set_update_derived",
           [](i_scene &self, py::function f) {
             self.set_update_derived([=] { f(); });
           })
      .def("set_render_derived",
           [](i_scene &self, py::function f) {
             self.set_render_derived([=] { f(); });
           })
      .def("set_action2", [](i_scene &self, py::function f) {
        self.set_action([=] { f(); });
      });
  //.def("set_action", &py_i_scene::set_action)
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

  py::class_<img_rend>(m, "img_rend")
      .def("draw_img",
           [](img_rend &self, str_view image_name, float x, float y, float w,
              float h) { self.draw_img(image_name, x, y, w, h); })
      .def("draw_img",
           [](img_rend &self, int image_name_hash, float x, float y, float w,
              float h) { self.draw_img(image_name_hash, x, y, w, h); })
      .def("draw_img_auto_h", &img_rend::draw_img_auto_h);

  m.def(
      "get_scene_mngr", []() -> scene_mngr & { return _<scene_mngr>(); },
      py::return_value_policy::reference);

  m.def(
      "get_img_rend", []() -> img_rend & { return _<img_rend>(); },
      py::return_value_policy::reference);

  m.def("my_function",
        []() { std::cout << "Executing my_function" << std::endl; });

  m.def("func2", &asd);

  m.def("func3", [] {
    py::exec(R"(

      print('Executing func3')
      print('zxc')


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
  //_<scene_mngr>().add_scene("intro_scene", _<intro_scene>());
  //_<scene_mngr>().add_scene("main_menu_scene", _<main_menu_scene>());
  //_<scene_mngr>().add_scene("world_gen_scene", _<world_gen_scene>());
  //_<scene_mngr>().add_scene("main_scene", _<main_scene>());
  //_<scene_mngr>().go_to_scene("intro_scene");
  embedded.attr("setup_scenes")();
  // return 0;

  _<world>().init(_<game_props>().k_w_area_sz, _<game_props>().k_world_scaling);
  _<engine>().run();
  return 0;
}

// auto scenes = embedded.attr("get_scenes")().cast<vec<i_scene>>();
//_<scene_mngr>().add_scene("intro_scene_TEST", scenes.at(0));
