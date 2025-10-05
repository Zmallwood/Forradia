/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "engine.hpp"
#include "game_props.hpp"
#include "gui.hpp"
#include "input.hpp"
#include "rend.hpp"
#include "scenes.hpp"
#include "world_struct.hpp"

using namespace forr;
namespace py = pybind11;

class i_scene_publ : public i_scene {
 public:
  using i_scene::gui;
};

PYBIND11_EMBEDDED_MODULE(embedded, m) {

  py::class_<color>(m, "color").def(py::init<float, float, float, float>());

  py::class_<gui_comp, s_ptr<gui_comp>>(m, "gui_comp");

  py::class_<gui, s_ptr<gui>>(m, "gui").def(
      "add_child_comp", [](gui &self, s_ptr<gui_comp> comp) -> s_ptr<gui_comp> {
        return self.add_child_comp(comp);
      });

  py::class_<gui_label, s_ptr<gui_label>, gui_comp>(m, "gui_label")
      .def(py::init<float, float, float, float, str_view, bool, color>(),
           py::arg("x"), py::arg("y"), py::arg("w"), py::arg("h"),
           py::arg("text") = "", py::arg("cent_align") = false,
           py::arg("color") = colors::wheat_transp)
      .def("set_text", &gui_label::set_text)
      .def("set_visible", &gui_comp::set_visible);

  m.def("ticks", [] { return ticks(); });

  m.def("make_shared_gui_label",
        [](float x, float y, float w, float h, str_view text, bool cent_align) {
          return std::make_shared<gui_label>(x, y, w, h, text, cent_align,
                                             colors::wheat_transp);
        });

  py::class_<i_scene>(m, "i_scene")
      .def(py::init<>())
      .def("init", &i_scene::init)
      .def("gui", &i_scene_publ::gui)
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
      .def("set_render_derived", [](i_scene &self, py::function f) {
        self.set_render_derived([=] { f(); });
      });

  py::class_<scene_mngr>(m, "scene_mngr")
      .def(py::init<>())
      .def("add_scene", &scene_mngr::add_scene)
      .def("go_to_scene", &scene_mngr::go_to_scene);

  py::class_<cursor>(m, "cursor")
      .def(py::init<>())
      .def("set_curs_style", &cursor::set_curs_style);

  py::enum_<curs_styles>(m, "curs_styles")
      .value("normal", curs_styles::normal)
      .value("hovering_clickable_gui", curs_styles::hovering_clickable_gui)
      .value("hovering_creature", curs_styles::hovering_creature);

  py::class_<gui_chat_box>(m, "gui_chat_box")
      .def(py::init<>())
      .def("print", &gui_chat_box::print);

  py::class_<kb_inp>(m, "kb_inp")
      .def("any_key_pressed_pick_res", &kb_inp::any_key_pressed_pick_res);

  py::class_<mouse_inp>(m, "mouse_inp")
      .def("any_mouse_btn_pressed_pick_res",
           &mouse_inp::any_mouse_btn_pressed_pick_res);

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

  m.def(
      "get_gui_chat_box", []() -> gui_chat_box & { return _<gui_chat_box>(); },
      py::return_value_policy::reference);

  m.def(
      "get_cursor", []() -> cursor & { return _<cursor>(); },
      py::return_value_policy::reference);

  m.def(
      "get_kb_inp", []() -> kb_inp & { return _<kb_inp>(); },
      py::return_value_policy::reference);

  m.def(
      "get_mouse_inp", []() -> mouse_inp & { return _<mouse_inp>(); },
      py::return_value_policy::reference);

  m.def("my_function",
        []() { std::cout << "Executing my_function" << std::endl; });

  m.def("func3", [] {
    py::exec(R"(

      print('Executing func3')
      print('zxc')


    )");
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
  embedded.attr("func3")();

  _<engine>().init(_<game_props>().k_game_win_title,
                   _<game_props>().k_clear_color);
  //_<scene_mngr>().add_scene("intro_scene", _<intro_scene>());
  //_<scene_mngr>().add_scene("main_menu_scene", _<main_menu_scene>());
  //_<scene_mngr>().add_scene("world_gen_scene", _<world_gen_scene>());
  //_<scene_mngr>().add_scene("main_scene", _<main_scene>());
  //_<scene_mngr>().go_to_scene("intro_scene");
  embedded.attr("setup_scenes")();

  _<world>().init(_<game_props>().k_w_area_sz, _<game_props>().k_world_scaling);
  _<engine>().run();
  return 0;
}
