from embedded import (
    i_scene,
    get_scene_mngr,
    get_img_rend,
    gui,
    gui_label,
    make_shared_gui_label
)


class IntroScene(i_scene):
    def __init__(self):
        i_scene.__init__(self)

        self.start_text_comp = None

        def init_derived():
            g = self.gui()
            lbl = make_shared_gui_label(0.45, 0.5, 0.1, 0.04, "Press to start", True)
            start_text_comp_ = g.add_child_comp(lbl)

        def update_derived():
            print("UPDATE")

        def render_derived():
            img_rend = get_img_rend()
            img_rend.draw_img("default_scene_bg", 0.0, 0.0, 1.0, 1.0)
            print("RENDER")

        self.set_init_derived(init_derived)
        self.set_update_derived(update_derived)
        self.set_render_derived(render_derived)
        print("Initializing intro scene")



intro_scene= IntroScene()


def setup_scenes():
    print("Setting up scenes")
    global intro_scene
    scene_mngr = get_scene_mngr()
    scene_mngr.add_scene("intro_scene_TEST", intro_scene)
    scene_mngr.go_to_scene("intro_scene_TEST")

def test_fn():
    #asd()
    print("TJosan frAn Python!! :))")