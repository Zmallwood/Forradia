"""
Copyright 2025 Andreas Åkerberg
This code is licensed under MIT license (see LICENSE for details)
"""

from embedded import (
    IScene,
    get_engine,
    get_scene_mngr,
    make_shared_gui_label,
    make_shared_gui_panel,
    make_shared_gui_button,
    get_gui_chat_box,
    get_gui_chat_box_ptr,
    ticks,
    get_cursor,
    CursorStyles,
    get_kb_inp,
    get_mouse_inp,
    get_world_grator,
    make_shared_gui_player_status_box,
    get_gui_player_body_win_ptr,
    get_gui_inventory_win_ptr,
    get_gui_sys_menu_ptr,
    conv_w_to_h,
    make_shared_fps_panel,
    get_gui_interact_menu_ptr,
    update_kb_actions,
    update_mouse_actions,
    update_crea_movem,
    update_mouse_movem,
    update_kb_movem,
    update_actions,
    update_robots_movem,
    get_tl_hovering,
    get_world_view,
    get_img_2d_rend,
)


class IntroScene(IScene):
    def __init__(self):
        IScene.__init__(self)

        self.start_text_comp = None

        def init_derived():
            lbl = make_shared_gui_label(0.45, 0.5, 0.1, 0.04, "Press to start", True)

            self.start_text_comp = self.gui().add_child_comp(lbl)

        def on_enter_derived():
            get_gui_chat_box().print("Game started.")

        def update_derived():
            self.start_text_comp.set_visible(ticks() % 800 < 400)

            get_cursor().set_curs_style(CursorStyles.hovering_clickable_gui)

            if (
                get_kb_inp().any_key_pressed_pick_res()
                or get_mouse_inp().any_mouse_btn_pressed_pick_res()
            ):
                get_scene_mngr().go_to_scene("main_menu_scene")

        def render_derived():
            get_img_2d_rend().draw_img("DefaultSceneBackground", 0.0, 0.0, 1.0, 1.0)

            get_img_2d_rend().draw_img_auto_h("ForradiaLogo", 0.25, 0.2, 0.5)

        self.set_init_derived(init_derived)
        self.set_on_enter_derived(on_enter_derived)
        self.set_update_derived(update_derived)
        self.set_render_derived(render_derived)


class MainMenuScene(IScene):
    def __init__(self):
        IScene.__init__(self)

        def init_derived():
            pnl = make_shared_gui_panel(0.4, 0.32, 0.2, 0.2)

            self.gui().add_child_comp(pnl)

            btn_play = make_shared_gui_button(
                0.45,
                0.36,
                0.1,
                0.04,
                "Play",
                lambda: get_scene_mngr().go_to_scene("play_scene"),
            )

            self.gui().add_child_comp(btn_play)

            btn_quit = make_shared_gui_button(
                0.45, 0.44, 0.1, 0.04, "Quit", lambda: get_engine().stop()
            )

            self.gui().add_child_comp(btn_quit)

            self.gui().add_child_comp(get_gui_chat_box_ptr())

        def render_derived():
            get_img_2d_rend().draw_img("DefaultSceneBackground", 0.0, 0.0, 1.0, 1.0)

            get_img_2d_rend().draw_img_auto_h("ForradiaLogo", 0.35, 0.1, 0.3)

        self.set_init_derived(init_derived)
        self.set_render_derived(render_derived)


class PlayScene(IScene):
    def __init__(self):
        IScene.__init__(self)

        def init_derived():
            pnl = make_shared_gui_panel(0.4, 0.32, 0.2, 0.32)

            self.gui().add_child_comp(pnl)

            btn_new_game = make_shared_gui_button(
                0.45,
                0.36,
                0.1,
                0.04,
                "New game",
                lambda: get_scene_mngr().go_to_scene("world_gen_scene"),
            )

            self.gui().add_child_comp(btn_new_game)

            btn_load_game = make_shared_gui_button(
                0.45, 0.44, 0.1, 0.04, "Load game", lambda: ...
            )

            self.gui().add_child_comp(btn_load_game)

            btn_quit = make_shared_gui_button(
                0.45,
                0.56,
                0.1,
                0.04,
                "Back",
                lambda: get_scene_mngr().go_to_scene("main_menu_scene"),
            )

            self.gui().add_child_comp(btn_quit)

            self.gui().add_child_comp(get_gui_chat_box_ptr())

        def render_derived():
            get_img_2d_rend().draw_img("DefaultSceneBackground", 0.0, 0.0, 1.0, 1.0)

            get_img_2d_rend().draw_img_auto_h("ForradiaLogo", 0.35, 0.1, 0.3)

        self.set_init_derived(init_derived)
        self.set_render_derived(render_derived)


class WorldGenScene(IScene):
    def __init__(self):
        IScene.__init__(self)

        def on_enter_derived():
            get_gui_chat_box().print("Generating world...")

            get_world_grator().gen_new_world()

            get_gui_chat_box().print("World generation completed.")

            get_scene_mngr().go_to_scene("main_scene")

        self.set_on_enter_derived(on_enter_derived)


class MainScene(IScene):
    def __init__(self):
        IScene.__init__(self)

        def init_derived():
            self.gui().add_child_comp(make_shared_gui_player_status_box())

            self.gui().add_child_comp(get_gui_chat_box_ptr())

            btn_gui_player_body_win = make_shared_gui_button(
                0.78,
                0.9,
                0.05,
                conv_w_to_h(0.05),
                "",
                lambda: get_gui_player_body_win_ptr().toggle_visible(),
                "GUIButtonPlayerBodyBackground",
                "GUIButtonPlayerBodyHoveredBackground",
            )

            self.gui().add_child_comp(btn_gui_player_body_win)

            btn_gui_inventory_win = make_shared_gui_button(
                0.85,
                0.9,
                0.05,
                conv_w_to_h(0.05),
                "",
                lambda: get_gui_inventory_win_ptr().toggle_visible(),
                "GUIButtonInventoryBackground",
                "GUIButtonInventoryHoveredBackground",
            )

            self.gui().add_child_comp(btn_gui_inventory_win)

            btn_gui_sys_menu = make_shared_gui_button(
                0.92,
                0.9,
                0.05,
                conv_w_to_h(0.05),
                "",
                lambda: get_gui_sys_menu_ptr().toggle_visible(),
                "GUIButtonSystemMenuBackground",
                "GUIButtonSystemMenuHoveredBackground",
            )

            self.gui().add_child_comp(btn_gui_sys_menu)
            self.gui().add_child_comp(get_gui_player_body_win_ptr())
            self.gui().add_child_comp(get_gui_inventory_win_ptr())
            self.gui().add_child_comp(get_gui_sys_menu_ptr())
            self.gui().add_child_comp(make_shared_fps_panel())
            self.gui().add_child_comp(get_gui_interact_menu_ptr())

        def on_enter_derived():
            get_gui_chat_box().print("You have entered the world.")

        def update_derived():
            update_kb_actions()

            update_mouse_actions()

            update_crea_movem()

            update_robots_movem()

            update_mouse_movem()

            update_kb_movem()

            get_tl_hovering().update()

            update_actions()

        def render_derived():
            get_world_view().render()

        self.set_init_derived(init_derived)
        self.set_on_enter_derived(on_enter_derived)
        self.set_update_derived(update_derived)
        self.set_render_derived(render_derived)


intro_scene = IntroScene()
main_menu_scene = MainMenuScene()
play_scene = PlayScene()
world_gen_scene = WorldGenScene()
main_scene = MainScene()


def setup_scenes():
    global intro_scene
    global main_menu_scene
    global play_scene
    global world_gen_scene
    global main_scene

    scene_mngr = get_scene_mngr()

    scene_mngr.add_scene("intro_scene", intro_scene)
    scene_mngr.add_scene("main_menu_scene", main_menu_scene)
    scene_mngr.add_scene("play_scene", play_scene)
    scene_mngr.add_scene("world_gen_scene", world_gen_scene)
    scene_mngr.add_scene("main_scene", main_scene)

    scene_mngr.go_to_scene("intro_scene")
