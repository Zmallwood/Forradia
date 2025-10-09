/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class img_rend {
   public:
    void draw_img(str_view img_name, float x, float y, float w, float h) const;

    void draw_img(int img_name_hash, float x, float y, float w, float h) const;

    void draw_img_auto_h(str_view img_name, float x, float y, float w) const;
  };

  class img_2d_rend {
   public:
    img_2d_rend() { init(); };

    ~img_2d_rend() { cleanup(); }

    void reset_counter();

    void draw_img(str_view img_name, float x, float y, float w, float h);

    void draw_img(int img_name_hash, float x, float y, float w, float h);

    void draw_tex(GLuint tex_id, float x, float y, float w, float h);

    void draw_img_auto_h(str_view img_name, float x, float y, float w);

   private:
    void init();

    void cleanup();

    class Entry {
     public:
      GLuint vao;
      GLuint ibo;
      GLuint vbo;
      float x;
      float y;
      float w;
      float h;
    };

    GLuint program_;
    std::map<int, std::map<int, Entry>> imgs_;
    int counter_{0};
  };

  class Entry {
   public:
    GLuint vao;
    GLuint ibo;
    GLuint vbo;
    float x;
    float y;
    float z;
  };

  class ground_rend {
   public:
    ground_rend() { init(); };

    ~ground_rend() { cleanup(); }

    void draw_tile(int img_name_hash, int x_coord, int y_coord, float tl_sz,
                   pt_f camera_pos, vec<float> &elevs);

    void draw_tex(GLuint tex_id, vec<float> &verts, pt_f camera_pos);

   private:
    void init();

    void cleanup();

    glm::vec3 compute_normal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

    GLuint program_;
    std::map<float, std::map<float, Entry>> imgs_;
  };

  class model_rend {
   public:
    model_rend() { init(); }

    void draw_model(int model_name_hash, float x, float y, float z,
                    pt_f camera_pos);

   private:
    void init();

    GLuint program_;
    std::map<float, std::map<float, std::map<float, std::map<int, Entry>>>>
        models_;
  };

  enum struct font_szs { _20 = 20, _26 = 26 };

  class text_rend {
   public:
    text_rend() { init(); }

    void draw_str(str_view text, float x, float y,
                  font_szs font_sz = font_szs::_20, bool cent_align = false,
                  color text_color = colors::wheat_transp) const;

   private:
    void init();

    void add_fonts();

    const str k_default_font_path{"./res/fonts/PixeloidSans.ttf"};

    std::map<font_szs, s_ptr<TTF_Font>> fonts_;
  };
}