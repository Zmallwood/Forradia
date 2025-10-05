from embedded import (
    i_scene,
    get_scene_mngr,
    get_img_rend,
    gui,
    gui_label,
    make_shared_gui_label,
    make_shared_gui_panel,
    get_gui_chat_box,
    ticks,
    get_cursor,
    curs_styles,
    get_kb_inp,
    get_mouse_inp
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


        def render_derived():
            img_rend = get_img_rend()
            img_rend.draw_img("default_scene_bg", 0.0, 0.0, 1.0, 1.0)
            img_rend.draw_img_auto_h("forradia_logo", 0.35, 0.1, 0.3)

        self.set_init_derived(init_derived)
        self.set_render_derived(render_derived)
    

class WorldGenScene(i_scene):
    pass

class MainScene(i_scene):
    pass


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