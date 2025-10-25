//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Scripts.hpp"
#include "Core.hpp"
#include "GUI.hpp"
#include "GUISpec.hpp"
#include "Render.hpp"
#include "Update.hpp"
#include "WorldGen.hpp"
#include "WorldView.hpp"

namespace Forradia
{
    namespace Theme0
    {
        namespace Scripting
        {
            class IScenePublic
                : public Engine::ScenesCore::IScene
            {
              public:
                using IScene::GetGUI;
            };

            namespace py = pybind11;

            PYBIND11_EMBEDDED_MODULE(embedded, m)
            {
                py::class_<Color>(m, "Color")
                    .def(py::init<float, float, float,
                                  float>());

                py::class_<Engine>(m, "Engine")
                    .def("stop", &Engine::Stop);

                py::class_<
                    GUIComponentsLibrary::GUIComponent,
                    SharedPtr<GUIComponentsLibrary::
                                  GUIComponent>>(
                    m, "GUIComponent");

                py::class_<
                    Engine::ScenesCore::IScene::
                        ScenesGUI::GUIRoot,
                    SharedPtr<
                        Engine::ScenesCore::IScene::
                            ScenesGUI::GUIRoot>>(m,
                                                 "GUIRoot")
                    .def("add_child_comp",
                         [](Engine::ScenesCore::
                                IScene::ScenesGUI::GUIRoot
                                    &self,
                            SharedPtr<GUIComponentsLibrary::
                                          GUIComponent>
                                comp)
                             -> SharedPtr<
                                 GUIComponentsLibrary::
                                     GUIComponent>
                         {
                             return self.AddChildComponent(
                                 comp);
                         });

                py::class_<
                    GUIComponentsLibrary::GUILabel,
                    SharedPtr<
                        GUIComponentsLibrary::GUILabel>,
                    GUIComponentsLibrary::GUIComponent>(
                    m, "GUILabel")
                    .def(
                        py::init<float, float, float, float,
                                 StringView, bool, Color>(),
                        py::arg("x"), py::arg("y"),
                        py::arg("w"), py::arg("h"),
                        py::arg("text") = "",
                        py::arg("cent_align") = false,
                        py::arg("color") =
                            Colors::WheatTransparent)
                    .def("set_text", &GUIComponentsLibrary::
                                         GUILabel::SetText)
                    .def("set_visible",
                         &GUIComponentsLibrary::
                             GUIComponent::SetVisible);

                py::class_<
                    GUIComponentsLibrary::GUIPanel,
                    SharedPtr<
                        GUIComponentsLibrary::GUIPanel>,
                    GUIComponentsLibrary::GUIComponent>(
                    m, "GUIPanel");

                py::class_<
                    GUIComponentsLibrary::GUIButton,
                    SharedPtr<
                        GUIComponentsLibrary::GUIButton>,
                    GUIComponentsLibrary::GUIComponent>(
                    m, "gui_button");

                py::class_<
                    GUIComponentsLibrary::GUIFPSPanel,
                    SharedPtr<
                        GUIComponentsLibrary::GUIFPSPanel>,
                    GUIComponentsLibrary::GUIComponent>(
                    m, "gui_fps_panel");

                py::class_<
                    Engine::ScenesCore::IScene>(
                    m, "IScene")
                    .def(py::init<>())
                    .def("init", &Engine::ScenesCore::
                                     IScene::Initialize)
                    .def("gui", &IScenePublic::GetGUI)
                    .def("set_init_derived",
                         [](Engine::ScenesCore::IScene
                                &self,
                            py::function f)
                         {
                             self.SetInitializeDerived(
                                 [=] { f(); });
                         })
                    .def("set_on_enter_derived",
                         [](Engine::ScenesCore::IScene
                                &self,
                            py::function f)
                         {
                             self.SetOnEnterDerived(
                                 [=] { f(); });
                         })
                    .def("set_update_derived",
                         [](Engine::ScenesCore::IScene
                                &self,
                            py::function f)
                         {
                             self.SetUpdateDerived(
                                 [=] { f(); });
                         })
                    .def("set_render_derived",
                         [](Engine::ScenesCore::IScene
                                &self,
                            py::function f)
                         {
                             self.SetRenderDerived(
                                 [=] { f(); });
                         });

                py::class_<
                    Engine::ScenesCore::SceneManager>(
                    m, "SceneManager")
                    .def(py::init<>())
                    .def("add_scene",
                         &Engine::ScenesCore::
                             SceneManager::AddScene)
                    .def("go_to_scene",
                         &Engine::ScenesCore::
                             SceneManager::GoToScene);

                py::class_<Engine::Cursor>(m, "Cursor")
                    .def(py::init<>())
                    .def("set_curs_style",
                         &Engine::Cursor::SetCursorStyle);

                py::enum_<Engine::Cursor::CursorStyles>(
                    m, "CursorStyles")
                    .value("normal",
                           Engine::Cursor::CursorStyles::
                               Normal)
                    .value("hovering_clickable_gui",
                           Engine::Cursor::CursorStyles::
                               HoveringClickableGUI)
                    .value("hovering_creature",
                           Engine::Cursor::CursorStyles::
                               HoveringCreature);

                py::class_<
                    GUIComponentsLibrary::GUIChatBox,
                    SharedPtr<
                        GUIComponentsLibrary::GUIChatBox>,
                    GUIComponentsLibrary::GUIComponent>(
                    m, "GUIChatBox")
                    .def(py::init<>())
                    .def("print", &GUIComponentsLibrary::
                                      GUIChatBox::Print);

                py::class_<Theme0::WorldGeneration::
                               WorldGenerator>(
                    m, "WorldGenerator")
                    .def(py::init<>())
                    .def("gen_new_world",
                         &Theme0::WorldGeneration::
                             WorldGenerator::
                                 GenerateNewWorld);

                py::class_<
                    Engine::Input::KeyboardInput>(
                    m, "KeyboardInput")
                    .def("any_key_pressed_pick_res",
                         &Engine::Input::
                             KeyboardInput::
                                 AnyKeyIsPressedPickResult);

                py::class_<Engine::Input::MouseInput>(
                    m, "MouseInput")
                    .def(
                        "any_mouse_btn_pressed_pick_res",
                        &Engine::Input::MouseInput::
                            AnyMouseButtonIsPressedPickResult);

                py::class_<
                    Engine::Renderers::Image2DRenderer>(
                    m, "Image2DRenderer")
                    .def("draw_img",
                         [](Engine::Renderers::
                                Image2DRenderer &self,
                            StringView image_name, float x,
                            float y, float w, float h)
                         {
                             self.DrawImage(image_name, x,
                                            y, w, h);
                         })
                    .def("draw_img",
                         [](Engine::Renderers::
                                Image2DRenderer &self,
                            int image_name_hash, float x,
                            float y, float w, float h)
                         {
                             self.DrawImage(image_name_hash,
                                            x, y, w, h);
                         })
                    .def("draw_img_auto_h",
                         [](Engine::Renderers::
                                Image2DRenderer &self,
                            StringView img_name, float x,
                            float y, float w)
                         {
                             self.DrawImageAutoHeight(
                                 img_name, x, y, w);
                         });

                py::class_<
                    Theme0::GUIPlayerStatusBox,
                    SharedPtr<Theme0::GUIPlayerStatusBox>,
                    GUIComponentsLibrary::GUIComponent>(
                    m, "GUIPlayerStatusBox");

                py::class_<
                    Theme0::GUIPlayerBodyWindow,
                    SharedPtr<Theme0::GUIPlayerBodyWindow>,
                    GUIComponentsLibrary::GUIComponent>(
                    m, "GUIPlayerBodyWindow")
                    .def(
                        "toggle_visible",
                        &GUIComponentsLibrary::
                            GUIComponent::ToggleVisibility);

                py::class_<
                    Theme0::GUIInventoryWindow,
                    SharedPtr<Theme0::GUIInventoryWindow>,
                    GUIComponentsLibrary::GUIComponent>(
                    m, "GUIInventoryWindow")
                    .def(
                        "toggle_visible",
                        &GUIComponentsLibrary::
                            GUIComponent::ToggleVisibility);

                py::class_<
                    Theme0::GUISystemMenu,
                    SharedPtr<Theme0::GUISystemMenu>,
                    GUIComponentsLibrary::GUIComponent>(
                    m, "GUISystemMenu")
                    .def(
                        "toggle_visible",
                        &GUIComponentsLibrary::
                            GUIComponent::ToggleVisibility);

                py::class_<
                    Theme0::GUIInteractionMenu,
                    SharedPtr<Theme0::GUIInteractionMenu>,
                    GUIComponentsLibrary::GUIComponent>(
                    m, "GUIInteractionMenu");

                py::class_<
                    Theme0::GameplayCore::TileHovering>(
                    m, "TileHovering")
                    .def("update",
                         &Theme0::GameplayCore::
                             TileHovering::Update);

                py::class_<Theme0::GameplayCore::WorldView>(
                    m, "WorldView")
                    .def("render", &Theme0::GameplayCore::
                                       WorldView::Render);

                m.def("ticks", [] { return GetTicks(); });

                m.def("conv_w_to_h",
                      [](float w)
                      {
                          return ConvertWidthToHeight(
                              w, _<Engine::SDLDevice>()
                                     .GetWindow());
                      });

                m.def("make_shared_fps_panel",
                      []
                      {
                          return std::make_shared<
                              GUIComponentsLibrary::
                                  GUIFPSPanel>();
                      });

                m.def(
                    "make_shared_gui_label",
                    [](float x, float y, float w, float h,
                       StringView text, bool cent_align)
                    {
                        return std::make_shared<
                            GUIComponentsLibrary::GUILabel>(
                            x, y, w, h, text, cent_align,
                            Colors::WheatTransparent);
                    });

                m.def(
                    "make_shared_gui_panel",
                    [](float x, float y, float w, float h)
                    {
                        return std::make_shared<
                            GUIComponentsLibrary::GUIPanel>(
                            x, y, w, h);
                    });

                m.def("make_shared_gui_button",
                      [](float x, float y, float w, float h,
                         StringView text,
                         py::function action)
                      {
                          return std::make_shared<
                              GUIComponentsLibrary::
                                  GUIButton>(x, y, w, h,
                                             text, action);
                      });

                m.def(
                    "make_shared_gui_button",
                    [](float x, float y, float w, float h,
                       StringView text, py::function action,
                       StringView bg_img,
                       StringView hovered_bg_img)
                    {
                        return std::make_shared<
                            GUIComponentsLibrary::
                                GUIButton>(x, y, w, h, text,
                                           action, bg_img,
                                           hovered_bg_img);
                    });

                m.def("get_gui_interact_menu_ptr",
                      []() -> SharedPtr<
                               Theme0::GUIInteractionMenu>
                      {
                          return __<
                              Theme0::GUIInteractionMenu>();
                      });

                m.def(
                    "get_gui_player_body_win_ptr",
                    []() -> SharedPtr<
                             Theme0::GUIPlayerBodyWindow>
                    {
                        return __<
                            Theme0::GUIPlayerBodyWindow>();
                    });

                m.def("get_gui_inventory_win_ptr",
                      []() -> SharedPtr<
                               Theme0::GUIInventoryWindow>
                      {
                          return __<
                              Theme0::GUIInventoryWindow>();
                      });

                m.def(
                    "get_gui_sys_menu_ptr",
                    []() -> SharedPtr<Theme0::GUISystemMenu>
                    {
                        return __<Theme0::GUISystemMenu>();
                    });

                m.def("make_shared_gui_player_status_box",
                      []()
                      {
                          return std::make_shared<
                              Theme0::GUIPlayerStatusBox>();
                      });

                m.def(
                    "get_engine", []() -> Engine &
                    { return _<Engine>(); },
                    py::return_value_policy::reference);

                m.def(
                    "get_scene_mngr",
                    []() -> Engine::ScenesCore::
                             SceneManager &
                    {
                        return _<Engine::ScenesCore::
                                     SceneManager>();
                    },
                    py::return_value_policy::reference);

                m.def(
                    "get_img_2d_rend",
                    []() -> Engine::Renderers::
                             Image2DRenderer &
                    {
                        return _<Engine::Renderers::
                                     Image2DRenderer>();
                    },
                    py::return_value_policy::reference);

                m.def(
                    "get_gui_chat_box",
                    []() -> GUIComponentsLibrary::GUIChatBox
                             &
                    {
                        return _<GUIComponentsLibrary::
                                     GUIChatBox>();
                    },
                    py::return_value_policy::reference);

                m.def(
                    "get_gui_chat_box_ptr",
                    []() -> SharedPtr<GUIComponentsLibrary::
                                          GUIChatBox>
                    {
                        return __<GUIComponentsLibrary::
                                      GUIChatBox>();
                    });

                m.def(
                    "get_cursor", []() -> Engine::Cursor &
                    { return _<Engine::Cursor>(); },
                    py::return_value_policy::reference);

                m.def(
                    "get_kb_inp",
                    []() -> Engine::Input::
                             KeyboardInput &
                    {
                        return _<Engine::Input::
                                     KeyboardInput>();
                    },
                    py::return_value_policy::reference);

                m.def(
                    "get_mouse_inp",
                    []()
                        -> Engine::Input::MouseInput &
                    {
                        return _<Engine::Input::
                                     MouseInput>();
                    },
                    py::return_value_policy::reference);

                m.def(
                    "get_world_grator",
                    []() -> Theme0::WorldGeneration::
                             WorldGenerator &
                    {
                        return _<Theme0::WorldGeneration::
                                     WorldGenerator>();
                    },
                    py::return_value_policy::reference);

                m.def(
                    "get_tl_hovering",
                    []() -> Theme0::GameplayCore::
                             TileHovering &
                    {
                        return _<Theme0::GameplayCore::
                                     TileHovering>();
                    },
                    py::return_value_policy::reference);

                m.def(
                    "get_world_view",
                    []()
                        -> Theme0::GameplayCore::WorldView &
                    {
                        return _<Theme0::GameplayCore::
                                     WorldView>();
                    },
                    py::return_value_policy::reference);

                m.def("update_kb_actions",
                      &Theme0::GameplayCore::
                          UpdateKeyboardActions);

                m.def("update_mouse_actions",
                      &Theme0::GameplayCore::
                          UpdateMouseActions);

                m.def("update_npcs",
                      &Theme0::GameplayCore::UpdateNPCs);

                m.def("update_crea_movem",
                      &Theme0::GameplayCore::
                          UpdateCreaturesMovement);

                m.def("update_mouse_movem",
                      &Theme0::GameplayCore::
                          UpdateMouseMovement);

                m.def("update_kb_movem",
                      &Theme0::GameplayCore::
                          UpdateKeyboardMovement);

                m.def("setup_scenes",
                      []
                      {
                          py::eval_file(
                              "res/theme_0_scripts/"
                              "scenes.py");
                          py::eval("setup_scenes()");
                      });
            }

            void ScriptEngine::Initialize()
            {
                static pybind11::scoped_interpreter guard{};
            }

            void ScriptEngine::LoadScripts()
            {
                auto embedded =
                    py::module::import("embedded");

                embedded.attr("setup_scenes")();
            }
        }
    }
}