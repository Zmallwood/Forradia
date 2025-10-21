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
#include "world_gen.hpp"
#include "world_view.hpp"

_NS_START_
namespace Theme0
{
    namespace Scripting
    {
        class i_scene_publ : public Core::Engine::ScenesCore::IScene
        {
          public:
            using IScene::gui;
        };

        namespace py = pybind11;

        PYBIND11_EMBEDDED_MODULE(embedded, m)
        {
            py::class_<Color>(m, "Color")
                .def(py::init<float, float, float, float>());

            py::class_<Engine>(m, "Engine").def("stop", &Engine::stop);

            py::class_<GUIComponentsLibrary::GUIComponent,
                       SharedPtr<GUIComponentsLibrary::GUIComponent>>(m, "GUIComponent");

            py::class_<
                Core::Engine::ScenesCore::IScene::ScenesGUI::GUIRoot,
                SharedPtr<Core::Engine::ScenesCore::IScene::ScenesGUI::GUIRoot>>(
                m, "GUIRoot")
                .def("add_child_comp",
                     [](Core::Engine::ScenesCore::IScene::ScenesGUI::GUIRoot
                            &self,
                        SharedPtr<GUIComponentsLibrary::GUIComponent> comp)
                         -> SharedPtr<GUIComponentsLibrary::GUIComponent>
                     { return self.add_child_comp(comp); });

            py::class_<GUIComponentsLibrary::GUILabel,
                       SharedPtr<GUIComponentsLibrary::GUILabel>,
                       GUIComponentsLibrary::GUIComponent>(m, "GUILabel")
                .def(py::init<float, float, float, float, StringView, bool,
                              Color>(),
                     py::arg("x"), py::arg("y"), py::arg("w"), py::arg("h"),
                     py::arg("text") = "", py::arg("cent_align") = false,
                     py::arg("color") = Colors::wheat_transp)
                .def("set_text", &GUIComponentsLibrary::GUILabel::set_text)
                .def("set_visible",
                     &GUIComponentsLibrary::GUIComponent::set_visible);

            py::class_<GUIComponentsLibrary::GUIPanel,
                       SharedPtr<GUIComponentsLibrary::GUIPanel>,
                       GUIComponentsLibrary::GUIComponent>(m, "GUIPanel");

            py::class_<GUIComponentsLibrary::GUIButton,
                       SharedPtr<GUIComponentsLibrary::GUIButton>,
                       GUIComponentsLibrary::GUIComponent>(m, "gui_button");

            py::class_<GUIComponentsLibrary::GUIFPSPanel,
                       SharedPtr<GUIComponentsLibrary::GUIFPSPanel>,
                       GUIComponentsLibrary::GUIComponent>(m, "gui_fps_panel");

            py::class_<Core::Engine::ScenesCore::IScene>(m, "IScene")
                .def(py::init<>())
                .def("init", &Core::Engine::ScenesCore::IScene::init)
                .def("gui", &i_scene_publ::gui)
                .def("set_init_derived",
                     [](Core::Engine::ScenesCore::IScene &self, py::function f)
                     { self.set_init_derived([=] { f(); }); })
                .def("set_on_enter_derived",
                     [](Core::Engine::ScenesCore::IScene &self, py::function f)
                     { self.set_on_enter_derived([=] { f(); }); })
                .def("set_update_derived",
                     [](Core::Engine::ScenesCore::IScene &self, py::function f)
                     { self.set_update_derived([=] { f(); }); })
                .def("set_render_derived",
                     [](Core::Engine::ScenesCore::IScene &self, py::function f)
                     { self.set_render_derived([=] { f(); }); });

            py::class_<Core::Engine::ScenesCore::SceneManager>(m, "SceneManager")
                .def(py::init<>())
                .def("add_scene",
                     &Core::Engine::ScenesCore::SceneManager::add_scene)
                .def("go_to_scene",
                     &Core::Engine::ScenesCore::SceneManager::go_to_scene);

            py::class_<Engine::Cursor>(m, "Cursor")
                .def(py::init<>())
                .def("set_curs_style", &Engine::Cursor::set_curs_style);

            py::enum_<Engine::Cursor::CursorStyles>(m, "CursorStyles")
                .value("normal", Engine::Cursor::CursorStyles::normal)
                .value("hovering_clickable_gui",
                       Engine::Cursor::CursorStyles::hovering_clickable_gui)
                .value("hovering_creature",
                       Engine::Cursor::CursorStyles::hovering_creature);

            py::class_<GUIComponentsLibrary::GUIChatBox,
                       SharedPtr<GUIComponentsLibrary::GUIChatBox>,
                       GUIComponentsLibrary::GUIComponent>(m, "GUIChatBox")
                .def(py::init<>())
                .def("print", &GUIComponentsLibrary::GUIChatBox::print);

            py::class_<Theme0::WorldGeneration::WorldGenerator>(m, "WorldGenerator")
                .def(py::init<>())
                .def("gen_new_world",
                     &Theme0::WorldGeneration::WorldGenerator::gen_new_world);

            py::class_<Core::Engine::Input::KeyboardInput>(m, "KeyboardInput")
                .def("any_key_pressed_pick_res",
                     &Core::Engine::Input::KeyboardInput::any_key_pressed_pick_res);

            py::class_<Core::Engine::Input::MouseInput>(m, "MouseInput")
                .def("any_mouse_btn_pressed_pick_res",
                     &Core::Engine::Input::MouseInput::
                         any_mouse_btn_pressed_pick_res);

            py::class_<Engine::Renderers::Image2DRenderer>(m, "Image2DRenderer")
                .def("draw_img",
                     [](Engine::Renderers::Image2DRenderer &self,
                        StringView image_name, float x, float y, float w, float h)
                     { self.draw_img(image_name, x, y, w, h); })
                .def("draw_img",
                     [](Engine::Renderers::Image2DRenderer &self,
                        int image_name_hash, float x, float y, float w, float h)
                     { self.draw_img(image_name_hash, x, y, w, h); })
                .def("draw_img_auto_h",
                     [](Engine::Renderers::Image2DRenderer &self, StringView img_name,
                        float x, float y, float w)
                     { self.draw_img_auto_h(img_name, x, y, w); });

            py::class_<Theme0::GUIPlayerStatusBox,
                       SharedPtr<Theme0::GUIPlayerStatusBox>,
                       GUIComponentsLibrary::GUIComponent>(m,
                                                       "GUIPlayerStatusBox");

            py::class_<Theme0::GUIPlayerBodyWindow,
                       SharedPtr<Theme0::GUIPlayerBodyWindow>,
                       GUIComponentsLibrary::GUIComponent>(m, "GUIPlayerBodyWindow")
                .def("toggle_visible",
                     &GUIComponentsLibrary::GUIComponent::toggle_visible);

            py::class_<Theme0::GUIInventoryWindow,
                       SharedPtr<Theme0::GUIInventoryWindow>,
                       GUIComponentsLibrary::GUIComponent>(m, "GUIInventoryWindow")
                .def("toggle_visible",
                     &GUIComponentsLibrary::GUIComponent::toggle_visible);

            py::class_<Theme0::GUISystemMenu, SharedPtr<Theme0::GUISystemMenu>,
                       GUIComponentsLibrary::GUIComponent>(m, "GUISystemMenu")
                .def("toggle_visible",
                     &GUIComponentsLibrary::GUIComponent::toggle_visible);

            py::class_<Theme0::GUIInteractionMenu,
                       SharedPtr<Theme0::GUIInteractionMenu>,
                       GUIComponentsLibrary::GUIComponent>(m, "GUIInteractionMenu");

            py::class_<Theme0::GameplayCore::TileHovering>(m, "TileHovering")
                .def("update", &Theme0::GameplayCore::TileHovering::update);

            py::class_<Theme0::GameplayCore::WorldView>(m, "WorldView")
                .def("render",
                     &Theme0::GameplayCore::WorldView::render);

            m.def("ticks", [] { return ticks(); });

            m.def("conv_w_to_h", [](float w)
                  { return conv_w_to_h(w, _<Engine::SDLDevice>().win()); });

            m.def("make_shared_fps_panel",
                  []
                  {
                      return std::make_shared<
                          GUIComponentsLibrary::GUIFPSPanel>();
                  });

            m.def("make_shared_gui_label",
                  [](float x, float y, float w, float h, StringView text,
                     bool cent_align)
                  {
                      return std::make_shared<GUIComponentsLibrary::GUILabel>(
                          x, y, w, h, text, cent_align, Colors::wheat_transp);
                  });

            m.def("make_shared_gui_panel",
                  [](float x, float y, float w, float h)
                  {
                      return std::make_shared<GUIComponentsLibrary::GUIPanel>(
                          x, y, w, h);
                  });

            m.def("make_shared_gui_button",
                  [](float x, float y, float w, float h, StringView text,
                     py::function action)
                  {
                      return std::make_shared<GUIComponentsLibrary::GUIButton>(
                          x, y, w, h, text, action);
                  });

            m.def("make_shared_gui_button",
                  [](float x, float y, float w, float h, StringView text,
                     py::function action, StringView bg_img,
                     StringView hovered_bg_img)
                  {
                      return std::make_shared<GUIComponentsLibrary::GUIButton>(
                          x, y, w, h, text, action, bg_img, hovered_bg_img);
                  });

            m.def("get_gui_interact_menu_ptr",
                  []() -> SharedPtr<Theme0::GUIInteractionMenu>
                  { return __<Theme0::GUIInteractionMenu>(); });

            m.def("get_gui_player_body_win_ptr",
                  []() -> SharedPtr<Theme0::GUIPlayerBodyWindow>
                  { return __<Theme0::GUIPlayerBodyWindow>(); });

            m.def("get_gui_inventory_win_ptr",
                  []() -> SharedPtr<Theme0::GUIInventoryWindow>
                  { return __<Theme0::GUIInventoryWindow>(); });

            m.def("get_gui_sys_menu_ptr", []() -> SharedPtr<Theme0::GUISystemMenu>
                  { return __<Theme0::GUISystemMenu>(); });

            m.def(
                "make_shared_gui_player_status_box", []()
                { return std::make_shared<Theme0::GUIPlayerStatusBox>(); });

            m.def(
                "get_engine", []() -> Engine & { return _<Engine>(); },
                py::return_value_policy::reference);

            m.def(
                "get_scene_mngr", []() -> Core::Engine::ScenesCore::SceneManager &
                { return _<Core::Engine::ScenesCore::SceneManager>(); },
                py::return_value_policy::reference);

            m.def(
                "get_img_2d_rend", []() -> Engine::Renderers::Image2DRenderer &
                { return _<Engine::Renderers::Image2DRenderer>(); },
                py::return_value_policy::reference);

            m.def(
                "get_gui_chat_box", []() -> GUIComponentsLibrary::GUIChatBox &
                { return _<GUIComponentsLibrary::GUIChatBox>(); },
                py::return_value_policy::reference);

            m.def("get_gui_chat_box_ptr",
                  []() -> SharedPtr<GUIComponentsLibrary::GUIChatBox>
                  { return __<GUIComponentsLibrary::GUIChatBox>(); });

            m.def(
                "get_cursor",
                []() -> Engine::Cursor & { return _<Engine::Cursor>(); },
                py::return_value_policy::reference);

            m.def(
                "get_kb_inp", []() -> Core::Engine::Input::KeyboardInput &
                { return _<Core::Engine::Input::KeyboardInput>(); },
                py::return_value_policy::reference);

            m.def(
                "get_mouse_inp", []() -> Core::Engine::Input::MouseInput &
                { return _<Core::Engine::Input::MouseInput>(); },
                py::return_value_policy::reference);

            m.def(
                "get_world_grator",
                []() -> Theme0::WorldGeneration::WorldGenerator &
                { return _<Theme0::WorldGeneration::WorldGenerator>(); },
                py::return_value_policy::reference);

            m.def(
                "get_tl_hovering", []() -> Theme0::GameplayCore::TileHovering &
                { return _<Theme0::GameplayCore::TileHovering>(); },
                py::return_value_policy::reference);

            m.def(
                "get_world_view", []() -> Theme0::GameplayCore::WorldView &
                { return _<Theme0::GameplayCore::WorldView>(); },
                py::return_value_policy::reference);

            m.def("update_kb_actions",
                  &Theme0::GameplayCore::update_kb_actions);

            m.def("update_mouse_actions",
                  &Theme0::GameplayCore::update_mouse_actions);

            m.def("update_npcs", &Theme0::GameplayCore::update_npcs);

            m.def("update_crea_movem",
                  &Theme0::GameplayCore::update_crea_movem);

            m.def("update_mouse_movem",
                  &Theme0::GameplayCore::update_mouse_movem);

            m.def("update_kb_movem", &Theme0::GameplayCore::update_kb_movem);

            m.def("setup_scenes",
                  []
                  {
                      py::eval_file("res/theme_0_scripts/scenes.py");
                      py::eval("setup_scenes()");
                  });
        }

        void ScriptEngine::init()
        {
            static pybind11::scoped_interpreter guard{};
        }

        void ScriptEngine::load_scripts()
        {
            auto embedded = py::module::import("embedded");

            embedded.attr("setup_scenes")();
        }
    }
}
_NS_END_