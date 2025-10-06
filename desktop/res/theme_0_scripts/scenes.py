from embedded import (
    i_scene,
    get_engine,
    get_scene_mngr,
    get_img_rend,
    gui,
    gui_label,
    make_shared_gui_label,
    make_shared_gui_panel,
    make_shared_gui_button,
    get_gui_chat_box,
    get_gui_chat_box_ptr,
    ticks,
    get_cursor,
    curs_styles,
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
    update_npcs,
    update_crea_movem,
    update_mouse_movem,
    update_kb_movem,
    get_tl_hovering,
    get_world_view,
    get_img_2d_rend
)


class IntroScene(i_scene):
    def __init__(self):
        i_scene.__init__(self)

        self.start_text_comp = None

        def init_derived():
            g = self.gui()
            lbl = make_shared_gui_label(0.45, 0.5, 0.1, 0.04, "Press to start", True)
            self.start_text_comp = g.add_child_comp(lbl)

        def on_enter_derived():
            chat_box = get_gui_chat_box()
            chat_box.print("Game started.")

        def update_derived():
            self.start_text_comp.set_visible(ticks() % 800 < 400)

            curs = get_cursor()
            curs.set_curs_style(curs_styles.hovering_clickable_gui)

            kb_inp = get_kb_inp()
            mouse_inp = get_mouse_inp()
            scene_mngr = get_scene_mngr()

            if kb_inp.any_key_pressed_pick_res() or mouse_inp.any_mouse_btn_pressed_pick_res():
                scene_mngr.go_to_scene("main_menu_scene")

        def render_derived():
            img_rend = get_img_rend()
            img_rend.draw_img("default_scene_bg", 0.0, 0.0, 1.0, 1.0)
            img_rend.draw_img_auto_h("forradia_logo", 0.25, 0.2, 0.5)
            img_2d_rend = get_img_2d_rend()
            img_2d_rend.draw_img("default_scene_bg", 0.0, 0.0, 1.0, 1.0)
            img_2d_rend.draw_img_auto_h("forradia_logo", 0.25, 0.2, 0.5)

        self.set_init_derived(init_derived)
        self.set_on_enter_derived(on_enter_derived)
        self.set_update_derived(update_derived)
        self.set_render_derived(render_derived)


class MainMenuScene(i_scene):
    def __init__(self):
        i_scene.__init__(self)

        def init_derived():
            g = self.gui()
            pnl = make_shared_gui_panel(0.4, 0.32, 0.2, 0.2)
            g.add_child_comp(pnl)

            def test():
                pass

            btn_new_game = make_shared_gui_button(0.45, 0.36, 0.1, 0.04, "New game", lambda: get_scene_mngr().go_to_scene("world_gen_scene"))
            g.add_child_comp(btn_new_game)

            btn_quit = make_shared_gui_button(0.45, 0.44, 0.1, 0.04, "Quit", lambda: get_engine().stop())
            g.add_child_comp(btn_quit)


            gui_chat_box_ptr = get_gui_chat_box_ptr()
            g.add_child_comp(gui_chat_box_ptr)

        def render_derived():
            img_rend = get_img_rend()
            img_2d_rend = get_img_2d_rend()
            img_2d_rend.draw_img("default_scene_bg", 0.0, 0.0, 1.0, 1.0)
            img_2d_rend.draw_img_auto_h("forradia_logo", 0.35, 0.1, 0.3)

        self.set_init_derived(init_derived)
        self.set_render_derived(render_derived)
    

class WorldGenScene(i_scene):
    def __init__(self):
        i_scene.__init__(self)

        def on_enter_derived():
            chat_box = get_gui_chat_box()
            chat_box.print("Generating world...")
            world_grator = get_world_grator()
            world_grator.gen_new_world()
            chat_box.print("World generation completed.")
            scene_mngr = get_scene_mngr()
            scene_mngr.go_to_scene("main_scene")

        self.set_on_enter_derived(on_enter_derived)

class MainScene(i_scene):
    def __init__(self):
        i_scene.__init__(self)

        def init_derived():
            g = self.gui()
            g.add_child_comp(make_shared_gui_player_status_box())

            gui_chat_box_ptr = get_gui_chat_box_ptr()
            g.add_child_comp(gui_chat_box_ptr)

            btn_gui_player_body_win = make_shared_gui_button(0.78, 0.9, 0.05, conv_w_to_h(0.05), "",
                lambda: get_gui_player_body_win_ptr().toggle_visible(),
                "gui_button_player_body_bg", "gui_button_player_body_hovered_bg")

            g.add_child_comp(btn_gui_player_body_win)

            btn_gui_inventory_win = make_shared_gui_button(0.85, 0.9, 0.05, conv_w_to_h(0.05), "",
                lambda: get_gui_inventory_win_ptr().toggle_visible(),
                "gui_button_inventory_bg", "gui_button_inventory_hovered_bg")

            g.add_child_comp(btn_gui_inventory_win)


            btn_gui_sys_menu = make_shared_gui_button(0.92, 0.9, 0.05, conv_w_to_h(0.05), "",
                lambda: get_gui_sys_menu_ptr().toggle_visible(),
                "gui_button_system_menu_bg", "gui_button_system_menu_hovered_bg")

            g.add_child_comp(btn_gui_sys_menu)


            g.add_child_comp(get_gui_player_body_win_ptr())
            g.add_child_comp(get_gui_inventory_win_ptr())
            g.add_child_comp(get_gui_sys_menu_ptr())
            g.add_child_comp(make_shared_fps_panel())
            g.add_child_comp(get_gui_interact_menu_ptr())

#      gui()->add_child_comp(std::make_shared<gui_button>(
#          0.78f, 0.9f, 0.05f, conv_w_to_h(0.05f, _<sdl_device>().win()), "",
#          [] { _<gui_player_body_win>().toggle_visible(); },
#          "gui_button_player_body_bg", "gui_button_player_body_hovered_bg"));
#
#      gui()->add_child_comp(std::make_shared<gui_button>(
#          0.85f, 0.9f, 0.05f, conv_w_to_h(0.05f, _<sdl_device>().win()), "",
#          [] { _<gui_inventory_win>().toggle_visible(); },
#          "gui_button_inventory_bg", "gui_button_inventory_hovered_bg"));
#
#      gui()->add_child_comp(std::make_shared<gui_button>(
#          0.92f, 0.9f, 0.05f, conv_w_to_h(0.05f, _<sdl_device>().win()), "",
#          [] { _<gui_sys_menu>().toggle_visible(); },
#          "gui_button_system_menu_bg", "gui_button_system_menu_hovered_bg"));

        def on_enter_derived():
            chat_box = get_gui_chat_box()
            chat_box.print("You have entered the world.")

        def update_derived():
            update_kb_actions()
            update_mouse_actions()
            update_npcs()
            update_crea_movem()
            update_mouse_movem()
            update_kb_movem()
            get_tl_hovering().update()

        def render_derived():
            get_world_view().render()

        self.set_init_derived(init_derived)
        self.set_on_enter_derived(on_enter_derived)
        self.set_update_derived(update_derived)
        self.set_render_derived(render_derived)


intro_scene = IntroScene()
main_menu_scene = MainMenuScene()
world_gen_scene = WorldGenScene()
main_scene = MainScene()


def setup_scenes():
    global intro_scene
    global main_menu_scene
    global world_gen_scene
    global main_scene
    scene_mngr = get_scene_mngr()
    scene_mngr.add_scene("intro_scene", intro_scene)
    scene_mngr.add_scene("main_menu_scene", main_menu_scene)
    scene_mngr.add_scene("world_gen_scene", world_gen_scene)
    scene_mngr.add_scene("main_scene", main_scene)
    scene_mngr.go_to_scene("intro_scene")

def test_fn():
    #asd()
    print("TJosan frAn Python!! :))")