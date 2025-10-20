/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "scripts.hpp"
#include "core.hpp"
#include "gui.hpp"
#include "gui_spec.hpp"
#include "render.hpp"
#include "update.hpp"
#include "world_grator.hpp"
#include "world_view.hpp"

_NS_START_
namespace Theme0
{
    namespace Scripting
    {
        class i_scene_publ : public Core::engine::ScenesCore::i_scene
        {
          public:
            using i_scene::gui;
        };

        namespace py = pybind11;

        PYBIND11_EMBEDDED_MODULE(embedded, m)
        {
            py::class_<color>(m, "color")
                .def(py::init<float, float, float, float>());
            py::class_<engine>(m, "engine").def("stop", &engine::stop);
            py::class_<GUIComponentsLibrary::gui_comp,
                       s_ptr<GUIComponentsLibrary::gui_comp>>(m, "gui_comp");
            py::class_<
                Core::engine::ScenesCore::i_scene::ScenesGUI::gui_root,
                s_ptr<Core::engine::ScenesCore::i_scene::ScenesGUI::gui_root>>(
                m, "gui")
                .def("add_child_comp",
                     [](Core::engine::ScenesCore::i_scene::ScenesGUI::gui_root
                            &self,
                        s_ptr<GUIComponentsLibrary::gui_comp> comp)
                         -> s_ptr<GUIComponentsLibrary::gui_comp>
                     { return self.add_child_comp(comp); });
            py::class_<GUIComponentsLibrary::gui_label,
                       s_ptr<GUIComponentsLibrary::gui_label>,
                       GUIComponentsLibrary::gui_comp>(m, "gui_label")
                .def(py::init<float, float, float, float, str_view, bool,
                              color>(),
                     py::arg("x"), py::arg("y"), py::arg("w"), py::arg("h"),
                     py::arg("text") = "", py::arg("cent_align") = false,
                     py::arg("color") = colors::wheat_transp)
                .def("set_text", &GUIComponentsLibrary::gui_label::set_text)
                .def("set_visible",
                     &GUIComponentsLibrary::gui_comp::set_visible);
            py::class_<GUIComponentsLibrary::gui_panel,
                       s_ptr<GUIComponentsLibrary::gui_panel>,
                       GUIComponentsLibrary::gui_comp>(m, "gui_panel");
            py::class_<GUIComponentsLibrary::gui_button,
                       s_ptr<GUIComponentsLibrary::gui_button>,
                       GUIComponentsLibrary::gui_comp>(m, "gui_button");
            py::class_<GUIComponentsLibrary::gui_fps_panel,
                       s_ptr<GUIComponentsLibrary::gui_fps_panel>,
                       GUIComponentsLibrary::gui_comp>(m, "gui_fps_panel");
            py::class_<Core::engine::ScenesCore::i_scene>(m, "i_scene")
                .def(py::init<>())
                .def("init", &Core::engine::ScenesCore::i_scene::init)
                .def("gui", &i_scene_publ::gui)
                .def("set_init_derived",
                     [](Core::engine::ScenesCore::i_scene &self, py::function f)
                     { self.set_init_derived([=] { f(); }); })
                .def("set_on_enter_derived",
                     [](Core::engine::ScenesCore::i_scene &self, py::function f)
                     { self.set_on_enter_derived([=] { f(); }); })
                .def("set_update_derived",
                     [](Core::engine::ScenesCore::i_scene &self, py::function f)
                     { self.set_update_derived([=] { f(); }); })
                .def("set_render_derived",
                     [](Core::engine::ScenesCore::i_scene &self, py::function f)
                     { self.set_render_derived([=] { f(); }); });
            py::class_<Core::engine::ScenesCore::scene_mngr>(m, "scene_mngr")
                .def(py::init<>())
                .def("add_scene",
                     &Core::engine::ScenesCore::scene_mngr::add_scene)
                .def("go_to_scene",
                     &Core::engine::ScenesCore::scene_mngr::go_to_scene);
            py::class_<engine::cursor>(m, "cursor")
                .def(py::init<>())
                .def("set_curs_style", &engine::cursor::set_curs_style);
            py::enum_<engine::cursor::curs_styles>(m, "curs_styles")
                .value("normal", engine::cursor::curs_styles::normal)
                .value("hovering_clickable_gui",
                       engine::cursor::curs_styles::hovering_clickable_gui)
                .value("hovering_creature",
                       engine::cursor::curs_styles::hovering_creature);
            py::class_<GUIComponentsLibrary::gui_chat_box,
                       s_ptr<GUIComponentsLibrary::gui_chat_box>,
                       GUIComponentsLibrary::gui_comp>(m, "gui_chat_box")
                .def(py::init<>())
                .def("print", &GUIComponentsLibrary::gui_chat_box::print);
            py::class_<Theme0::WorldGeneration::world_grator>(m, "world_grator")
                .def(py::init<>())
                .def("gen_new_world",
                     &Theme0::WorldGeneration::world_grator::gen_new_world);
            py::class_<Core::engine::Input::kb_inp>(m, "kb_inp")
                .def("any_key_pressed_pick_res",
                     &Core::engine::Input::kb_inp::any_key_pressed_pick_res);
            py::class_<Core::engine::Input::mouse_inp>(m, "mouse_inp")
                .def("any_mouse_btn_pressed_pick_res",
                     &Core::engine::Input::mouse_inp::
                         any_mouse_btn_pressed_pick_res);
            py::class_<engine::Renderers::img_2d_rend>(m, "img_2d_rend")
                .def("draw_img",
                     [](engine::Renderers::img_2d_rend &self,
                        str_view image_name, float x, float y, float w, float h)
                     { self.draw_img(image_name, x, y, w, h); })
                .def("draw_img",
                     [](engine::Renderers::img_2d_rend &self,
                        int image_name_hash, float x, float y, float w, float h)
                     { self.draw_img(image_name_hash, x, y, w, h); })
                .def("draw_img_auto_h",
                     [](engine::Renderers::img_2d_rend &self, str_view img_name,
                        float x, float y, float w)
                     { self.draw_img_auto_h(img_name, x, y, w); });
            py::class_<Theme0::gui_player_status_box,
                       s_ptr<Theme0::gui_player_status_box>,
                       GUIComponentsLibrary::gui_comp>(m,
                                                       "gui_player_status_box");
            py::class_<Theme0::gui_player_body_win,
                       s_ptr<Theme0::gui_player_body_win>,
                       GUIComponentsLibrary::gui_comp>(m, "gui_player_body_win")
                .def("toggle_visible",
                     &GUIComponentsLibrary::gui_comp::toggle_visible);
            py::class_<Theme0::gui_inventory_win,
                       s_ptr<Theme0::gui_inventory_win>,
                       GUIComponentsLibrary::gui_comp>(m, "gui_inventory_win")
                .def("toggle_visible",
                     &GUIComponentsLibrary::gui_comp::toggle_visible);
            py::class_<Theme0::gui_sys_menu, s_ptr<Theme0::gui_sys_menu>,
                       GUIComponentsLibrary::gui_comp>(m, "gui_sys_menu")
                .def("toggle_visible",
                     &GUIComponentsLibrary::gui_comp::toggle_visible);
            py::class_<Theme0::gui_interact_menu,
                       s_ptr<Theme0::gui_interact_menu>,
                       GUIComponentsLibrary::gui_comp>(m, "gui_interact_menu");
            py::class_<tl_hovering>(m, "tl_hovering")
                .def("update", &tl_hovering::update);
            py::class_<world_view>(m, "world_view")
                .def("render", &world_view::render)
                .def("render_new", &world_view::render_new);
            m.def("ticks", [] { return ticks(); });
            m.def("conv_w_to_h", [](float w)
                  { return conv_w_to_h(w, _<engine::sdl_device>().win()); });
            m.def("make_shared_fps_panel",
                  []
                  {
                      return std::make_shared<
                          GUIComponentsLibrary::gui_fps_panel>();
                  });
            m.def("make_shared_gui_label",
                  [](float x, float y, float w, float h, str_view text,
                     bool cent_align)
                  {
                      return std::make_shared<GUIComponentsLibrary::gui_label>(
                          x, y, w, h, text, cent_align, colors::wheat_transp);
                  });
            m.def("make_shared_gui_panel",
                  [](float x, float y, float w, float h)
                  {
                      return std::make_shared<GUIComponentsLibrary::gui_panel>(
                          x, y, w, h);
                  });
            m.def("make_shared_gui_button",
                  [](float x, float y, float w, float h, str_view text,
                     py::function action)
                  {
                      return std::make_shared<GUIComponentsLibrary::gui_button>(
                          x, y, w, h, text, action);
                  });
            m.def("make_shared_gui_button",
                  [](float x, float y, float w, float h, str_view text,
                     py::function action, str_view bg_img,
                     str_view hovered_bg_img)
                  {
                      return std::make_shared<GUIComponentsLibrary::gui_button>(
                          x, y, w, h, text, action, bg_img, hovered_bg_img);
                  });
            m.def("get_gui_interact_menu_ptr",
                  []() -> s_ptr<Theme0::gui_interact_menu>
                  { return __<Theme0::gui_interact_menu>(); });
            m.def("get_gui_player_body_win_ptr",
                  []() -> s_ptr<Theme0::gui_player_body_win>
                  { return __<Theme0::gui_player_body_win>(); });
            m.def("get_gui_inventory_win_ptr",
                  []() -> s_ptr<Theme0::gui_inventory_win>
                  { return __<Theme0::gui_inventory_win>(); });
            m.def("get_gui_sys_menu_ptr", []() -> s_ptr<Theme0::gui_sys_menu>
                  { return __<Theme0::gui_sys_menu>(); });
            m.def(
                "make_shared_gui_player_status_box", []()
                { return std::make_shared<Theme0::gui_player_status_box>(); });
            m.def(
                "get_engine", []() -> engine & { return _<engine>(); },
                py::return_value_policy::reference);
            m.def(
                "get_scene_mngr", []() -> Core::engine::ScenesCore::scene_mngr &
                { return _<Core::engine::ScenesCore::scene_mngr>(); },
                py::return_value_policy::reference);
            m.def(
                "get_img_2d_rend", []() -> engine::Renderers::img_2d_rend &
                { return _<engine::Renderers::img_2d_rend>(); },
                py::return_value_policy::reference);
            m.def(
                "get_gui_chat_box", []() -> GUIComponentsLibrary::gui_chat_box &
                { return _<GUIComponentsLibrary::gui_chat_box>(); },
                py::return_value_policy::reference);
            m.def("get_gui_chat_box_ptr",
                  []() -> s_ptr<GUIComponentsLibrary::gui_chat_box>
                  { return __<GUIComponentsLibrary::gui_chat_box>(); });
            m.def(
                "get_cursor",
                []() -> engine::cursor & { return _<engine::cursor>(); },
                py::return_value_policy::reference);
            m.def(
                "get_kb_inp", []() -> Core::engine::Input::kb_inp &
                { return _<Core::engine::Input::kb_inp>(); },
                py::return_value_policy::reference);
            m.def(
                "get_mouse_inp", []() -> Core::engine::Input::mouse_inp &
                { return _<Core::engine::Input::mouse_inp>(); },
                py::return_value_policy::reference);
            m.def(
                "get_world_grator",
                []() -> Theme0::WorldGeneration::world_grator &
                { return _<Theme0::WorldGeneration::world_grator>(); },
                py::return_value_policy::reference);
            m.def(
                "get_tl_hovering",
                []() -> tl_hovering & { return _<tl_hovering>(); },
                py::return_value_policy::reference);
            m.def(
                "get_world_view",
                []() -> world_view & { return _<world_view>(); },
                py::return_value_policy::reference);
            m.def("update_kb_actions", &update_kb_actions);
            m.def("update_mouse_actions", &update_mouse_actions);
            m.def("update_npcs", &update_npcs);
            m.def("update_crea_movem", &update_crea_movem);
            m.def("update_mouse_movem", &update_mouse_movem);
            m.def("update_kb_movem", &update_kb_movem);
            m.def("setup_scenes",
                  []
                  {
                      py::eval_file("res/theme_0_scripts/scenes.py");
                      py::eval("setup_scenes()");
                  });
        }

        void script_engine::init()
        {
            static pybind11::scoped_interpreter guard{};
        }

        void script_engine::load_scripts()
        {
            auto embedded = py::module::import("embedded");
            embedded.attr("setup_scenes")();
        }
    }
}
_NS_END_