/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class gui;

  class i_scene {
   public:
    void init();

    void update();

    void render() const;

    void on_enter();

   protected:
    virtual void init_derived() {}

    virtual void on_enter_derived() {}

    virtual void update_derived() {}

    virtual void render_derived() const {}

    auto get_gui() const { return m_gui; }

   private:
    s_ptr<gui> m_gui;
  };

  class scene_manager {
   public:
    void add_scene(str_view scene_name, i_scene &scene);

    void go_to_scene(str_view scene_name);

    void update_curr_scene();

    void render_curr_scene() const;

   private:
    std::map<int, i_scene &> m_scenes;
    int m_curr_scene{0};
  };
}