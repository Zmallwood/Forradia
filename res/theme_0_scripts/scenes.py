from embedded import (
    py_i_scene,
    get_scene_mngr,
    scene_mngr
)
from typing import cast


class IntroSceneTEST(py_i_scene):
    def __init__(self):
        py_i_scene.__init__(self)
        self.set_action2(lambda: print("DERIVED"))
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



intro_scene_TEST0 = IntroSceneTEST()
def get_scenes():
    global intro_scene_TEST0
    #intro_scene_TEST = IntroSceneTEST()
    return [intro_scene_TEST0]



def setup_scenes():
    print("Setting up scenes")
    scene_mngr = get_scene_mngr()
    scene_mngr.add_scene("intro_scene_TEST", intro_scene_TEST0)
    #scene_mngr.update_curr_scene()
    #scene_mngr.add_scene("intro_scene_TEST", intro_scene_TEST)
    #intro_scene_TEST.update()
    #scene_mngr.go_to_scene("main_menu_scene")
    #scene_mngr.go_to_scene("intro_scene_TEST")

def test_fn():
    #asd()
    print("TJosan frAn Python!! :))")
    ccccc = CppClass()
    ccccc.print()