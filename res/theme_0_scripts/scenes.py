from embedded import (
    i_scene,
    get_scene_mngr,
    get_img_rend
)


class IntroScene(i_scene):
    def __init__(self):
        i_scene.__init__(self)
        self.set_action2(lambda: print("DERIVED"))

        def update_derived():
            print("UPDATE")

        def render_derived():
            img_rend = get_img_rend()
            img_rend.draw_img("default_scene_bg", 0.0, 0.0, 1.0, 1.0)
            print("RENDER")

        self.set_update_derived(update_derived)
        self.set_render_derived(render_derived)
        print("Initializing intro scene")

    def init(self):
        print("Initializing intro scene 2")

    def init_derived(self):
        print("Initializing intro scene more")

    def on_enter(self):
        print("Entering intro scene")
    #def update(self):
    #    print("Updating intro scene")
    #def update_derived(self):
    #    print("updateing intro scene")
    #def render_derived(self):
    #    print("Rendering intro scene")



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