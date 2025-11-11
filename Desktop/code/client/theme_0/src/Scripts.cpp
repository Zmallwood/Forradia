//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Scripts.hpp"

#include "Engine.hpp"

#include "CustomGUI/GUIPlayerStatusBox.hpp"

#include "CustomGUI/GUIPlayerBodyWindow.hpp"

#include "CustomGUI/GUIInventoryWindow.hpp"

#include "CustomGUI/GUISystemMenu.hpp"

#include "CustomGUI/GUIInteractionMenu/GUIInteractionMenu.hpp"

#include "SDLDevice.hpp"

#include "Cursor.hpp"

#include "WorldGenerator.hpp"

#include "WorldView.hpp"

#include "IScene.hpp"

#include "SceneManager.hpp"

#include "Keyboard/KeyboardInput.hpp"

#include "Mouse/MouseInput.hpp"

#include "GUILabel.hpp"

#include "GUIButton.hpp"

#include "GUIFPSPanel.hpp"

#include "GUIChatBox.hpp"

#include "Image2DRenderer.hpp"

#include "Update/TileHovering.hpp"

#include "Update/BattleSystem.hpp"

#include "Update/UpdateKeyboardActions.hpp"

#include "Update/UpdateMouseActions.hpp"

#include "Update/UpdateCreaturesMovement.hpp"

#include "Update/UpdateMouseMovement.hpp"

#include "Update/UpdateKeyboardMovement.hpp"

#include "Update/UpdateRobotsMovement.hpp"

#include "Update/UpdateCameraZoom.hpp"

#include "Update/CameraRotator.hpp"

#include "CustomGUI/GUIInteractionMenu/Actions.hpp"

#include "CustomGUI/GUIEnergyStatisticsPanel.hpp"

#include "GUI.hpp"

namespace Forradia::Theme0
{
    class IScenePublic : public IScene
    {
      public:
        using IScene::GetGUI;
    };

    namespace py = pybind11;

    PYBIND11_EMBEDDED_MODULE(embedded, m)
    {
        py::class_<Color>(m, "Color").def(py::init<float, float, float, float>());

        py::class_<Engine>(m, "Engine").def("stop", &Engine::Stop);

        py::class_<GUIComponent, SharedPtr<GUIComponent>>(m, "GUIComponent");

        py::class_<GUI, SharedPtr<GUI>>(m, "GUI").def(
            "add_child_comp",
            [](GUI &self, SharedPtr<GUIComponent> comp) -> SharedPtr<

                                                            GUIComponent>
            { return self.AddChildComponent(comp); });

        py::class_<GUILabel, SharedPtr<GUILabel>, GUIComponent>(m, "GUILabel")
            .def(py::init<StringView, float, float, float, float, StringView, bool, Color>(),
                 py::arg("uniqueName"), py::arg("x"), py::arg("y"), py::arg("w"), py::arg("h"),
                 py::arg("text") = "", py::arg("cent_align") = false,
                 py::arg("color") = Palette::GetColor<Hash("YellowTransparent")>())
            .def("set_text", &GUILabel::SetText)
            .def("set_visible", &GUIComponent::SetVisible);

        py::class_<GUIPanel, SharedPtr<GUIPanel>, GUIComponent>(m, "GUIPanel");

        py::class_<GUIButton, SharedPtr<GUIButton>, GUIComponent>(m, "gui_button");

        py::class_<GUIFPSPanel, SharedPtr<GUIFPSPanel>, GUIComponent>(m, "gui_fps_panel");

        py::class_<GUIEnergyStatisticsPanel, SharedPtr<GUIEnergyStatisticsPanel>, GUIComponent>(
            m, "gui_energy_statistics_panel");

        py::class_<IScene>(m, "IScene")
            .def(py::init<>())
            .def("init", &IScene::Initialize)
            .def("gui", &IScenePublic::GetGUI)
            .def("set_init_derived",
                 [](IScene &self, py::function f) { self.SetInitializeDerived([=] { f(); }); })
            .def("set_on_enter_derived",
                 [](IScene &self, py::function f) { self.SetOnEnterDerived([=] { f(); }); })
            .def("set_update_derived",
                 [](IScene &self, py::function f) { self.SetUpdateDerived([=] { f(); }); })
            .def("set_render_derived",
                 [](IScene &self, py::function f) { self.SetRenderDerived([=] { f(); }); });

        py::class_<SceneManager>(m, "SceneManager")
            .def(py::init<>())
            .def("add_scene", &SceneManager::AddScene)
            .def("go_to_scene", &SceneManager::GoToScene);

        py::class_<Cursor>(m, "Cursor")
            .def(py::init<>())
            .def("set_curs_style", &Cursor::SetCursorStyle);

        py::enum_<CursorStyles>(m, "CursorStyles")
            .value("normal", CursorStyles::Normal)
            .value("hovering_clickable_gui", CursorStyles::HoveringClickableGUI)
            .value("hovering_creature", CursorStyles::HoveringCreature);

        py::class_<GUIChatBox, SharedPtr<GUIChatBox>, GUIComponent>(m, "GUIChatBox")
            .def(py::init<>())
            .def("print", &GUIChatBox::Print);

        py::class_<Theme0::WorldGenerator>(m, "WorldGenerator")
            .def(py::init<>())
            .def("gen_new_world", &Theme0::WorldGenerator::GenerateNewWorld);

        py::class_<KeyboardInput>(m, "KeyboardInput")
            .def("any_key_pressed_pick_res", &KeyboardInput::AnyKeyIsPressedPickResult);

        py::class_<MouseInput>(m, "MouseInput")
            .def("any_mouse_btn_pressed_pick_res", &MouseInput::AnyMouseButtonIsPressedPickResult);

        py::class_<Image2DRenderer>(m, "Image2DRenderer")
            .def("draw_img", [](Image2DRenderer &self, int uniqueRenderID, StringView image_name,
                                float x, float y, float w, float h)
                 { self.DrawImageByName(uniqueRenderID, image_name, x, y, w, h); })
            .def("draw_img", [](Image2DRenderer &self, int uniqueRenderID, int image_name_hash,
                                float x, float y, float w, float h)
                 { self.DrawImageByHash(uniqueRenderID, image_name_hash, x, y, w, h); })
            .def("draw_img_auto_h", [](Image2DRenderer &self, int uniqueRenderID,
                                       StringView img_name, float x, float y, float w)
                 { self.DrawImageAutoHeight(uniqueRenderID, img_name, x, y, w); });

        py::class_<Theme0::GUIPlayerStatusBox, SharedPtr<Theme0::GUIPlayerStatusBox>, GUIComponent>(
            m, "GUIPlayerStatusBox");

        py::class_<Theme0::GUIPlayerBodyWindow, SharedPtr<Theme0::GUIPlayerBodyWindow>,
                   GUIComponent>(m, "GUIPlayerBodyWindow")
            .def("toggle_visible", &GUIComponent::ToggleVisibility);

        py::class_<Theme0::GUIInventoryWindow, SharedPtr<Theme0::GUIInventoryWindow>, GUIComponent>(
            m, "GUIInventoryWindow")
            .def("toggle_visible", &GUIComponent::ToggleVisibility);

        py::class_<Theme0::GUISystemMenu, SharedPtr<Theme0::GUISystemMenu>, GUIComponent>(
            m, "GUISystemMenu")
            .def("toggle_visible", &GUIComponent::ToggleVisibility);

        py::class_<Theme0::GUIInteractionMenu, SharedPtr<Theme0::GUIInteractionMenu>, GUIComponent>(
            m, "GUIInteractionMenu");

        py::class_<Theme0::GameplayCore::TileHovering>(m, "TileHovering")
            .def("update", &Theme0::GameplayCore::TileHovering::Update);

        py::class_<Theme0::GameplayCore::BattleSystem>(m, "BattleSystem")
            .def("update", &Theme0::GameplayCore::BattleSystem::Update);

        py::class_<Theme0::GameplayCore::CameraRotator>(m, "CameraRotator")
            .def("update", &Theme0::GameplayCore::CameraRotator::Update);

        py::class_<Theme0::GameplayCore::WorldView>(m, "WorldView")
            .def("render", &Theme0::GameplayCore::WorldView::Render);

        m.def("get_hash", [](StringView str) { return Hash(str); });

        m.def("ticks", [] { return GetTicks(); });

        m.def("conv_w_to_h",
              [](float w) { return ConvertWidthToHeight(w, _<SDLDevice>().GetWindow()); });

        m.def("make_shared_fps_panel",
              []
              {
                  return std::make_shared<

                      GUIFPSPanel>();
              });

        m.def("make_shared_energy_statistics_panel",
              []
              {
                  return std::make_shared<

                      GUIEnergyStatisticsPanel>();
              });

        m.def("make_shared_gui_label",
              [](StringView uniqueName, float x, float y, float w, float h, StringView text,
                 bool cent_align)
              {
                  return std::make_shared<GUILabel>(uniqueName, x, y, w, h, text, cent_align,
                                                    Palette::GetColor<Hash("YellowTransparent")>());
              });

        m.def("make_shared_gui_panel", [](StringView uniqueName, float x, float y, float w, float h)
              { return std::make_shared<GUIPanel>(uniqueName, x, y, w, h); });

        m.def("make_shared_gui_button",
              [](StringView uniqueName, float x, float y, float w, float h, StringView text,
                 py::function action)
              {
                  return std::make_shared<

                      GUIButton>(uniqueName, x, y, w, h, text, action);
              });

        m.def("make_shared_gui_button",
              [](StringView uniqueName, float x, float y, float w, float h, StringView text,
                 py::function action, StringView bg_img, StringView hovered_bg_img)
              {
                  return std::make_shared<GUIButton>(uniqueName, x, y, w, h, text, action, bg_img,
                                                     hovered_bg_img);
              });

        m.def("get_gui_interact_menu_ptr", []() -> SharedPtr<Theme0::GUIInteractionMenu>
              { return __<Theme0::GUIInteractionMenu>(); });

        m.def("get_gui_player_body_win_ptr", []() -> SharedPtr<Theme0::GUIPlayerBodyWindow>
              { return __<Theme0::GUIPlayerBodyWindow>(); });

        m.def("get_gui_inventory_win_ptr", []() -> SharedPtr<Theme0::GUIInventoryWindow>
              { return __<Theme0::GUIInventoryWindow>(); });

        m.def("get_gui_sys_menu_ptr",
              []() -> SharedPtr<Theme0::GUISystemMenu> { return __<Theme0::GUISystemMenu>(); });

        m.def("make_shared_gui_player_status_box",
              []() { return std::make_shared<Theme0::GUIPlayerStatusBox>(); });

        m.def(
            "get_engine", []() -> Engine & { return _<Engine>(); },
            py::return_value_policy::reference);

        m.def(
            "get_scene_mngr", []() -> SceneManager & { return _<SceneManager>(); },
            py::return_value_policy::reference);

        m.def(
            "get_img_2d_rend", []() -> Image2DRenderer & { return _<Image2DRenderer>(); },
            py::return_value_policy::reference);

        m.def(
            "get_gui_chat_box", []() -> GUIChatBox & { return _<GUIChatBox>(); },
            py::return_value_policy::reference);

        m.def("get_gui_chat_box_ptr", []() -> SharedPtr<GUIChatBox> { return __<GUIChatBox>(); });

        m.def(
            "get_cursor", []() -> Cursor & { return _<Cursor>(); },
            py::return_value_policy::reference);

        m.def(
            "get_kb_inp", []() -> KeyboardInput & { return _<KeyboardInput>(); },
            py::return_value_policy::reference);

        m.def(
            "get_mouse_inp", []() -> MouseInput & { return _<MouseInput>(); },
            py::return_value_policy::reference);

        m.def(
            "get_world_grator", []() -> Theme0::WorldGenerator &
            { return _<Theme0::WorldGenerator>(); }, py::return_value_policy::reference);

        m.def(
            "get_tl_hovering", []() -> Theme0::GameplayCore::TileHovering &
            { return _<Theme0::GameplayCore::TileHovering>(); },
            py::return_value_policy::reference);

        m.def(
            "get_battle_system", []() -> Theme0::GameplayCore::BattleSystem &
            { return _<Theme0::GameplayCore::BattleSystem>(); },
            py::return_value_policy::reference);

        m.def(
            "get_camera_rotator", []() -> Theme0::GameplayCore::CameraRotator &
            { return _<Theme0::GameplayCore::CameraRotator>(); },
            py::return_value_policy::reference);

        m.def(
            "get_world_view", []() -> Theme0::GameplayCore::WorldView &
            { return _<Theme0::GameplayCore::WorldView>(); }, py::return_value_policy::reference);

        m.def("update_kb_actions", &Theme0::GameplayCore::UpdateKeyboardActions);

        m.def("update_mouse_actions", &Theme0::GameplayCore::UpdateMouseActions);

        m.def("update_crea_movem", &Theme0::GameplayCore::UpdateCreaturesMovement);

        m.def("update_robots_movem", &Theme0::GameplayCore::UpdateRobotsMovement);

        m.def("update_camera_zoom", &Theme0::GameplayCore::UpdateCameraZoom);

        m.def("update_mouse_movem", &Theme0::GameplayCore::UpdateMouseMovement);

        m.def("update_kb_movem", &Theme0::GameplayCore::UpdateKeyboardMovement);

        m.def("update_actions", &Theme0::UpdateActions);

        m.def("setup_scenes",
              []
              {
                  py::eval_file("Resources/Theme0Scripts/"
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
        auto embedded = py::module::import("embedded");

        embedded.attr("setup_scenes")();
    }
}