/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_GUI_TOP_                                           \
    namespace Core                                                             \
    {
_HIDE_FROM_OUTLINER_GUI_TOP_
class RenderersCollection
{
  public:
    class shader_program
    {
      public:
        shader_program(str_view vert_src, str_view frag_src)
        {
            init(vert_src, frag_src);
        }

        ~shader_program() { cleanup(); }

        auto program() const { return program_; }

      private:
        void init(str_view vert_src, str_view frag_src);

        void cleanup();

        GLuint program_;
    };

    class img_2d_rend
    {
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

        class entry
        {
          public:
            GLuint vao;
            GLuint ibo;
            GLuint vbo;
            float x;
            float y;
            float w;
            float h;
        };

        s_ptr<shader_program> shader_program_;
        std::map<int, std::map<int, entry>> imgs_;
        int counter_{0};
    };

    class entry
    {
      public:
        GLuint vao;
        GLuint ibo;
        GLuint vbo;
        float x;
        float y;
        float z;
    };

    class ground_rend
    {
      public:
        ground_rend() { init(); };

        ~ground_rend() { cleanup(); }

        void draw_tile(int img_name_hash, int x_coord, int y_coord, float tl_sz,
                       pt3_f camera_pos, vec<float> &elevs, float elev_h);

        void draw_tex(GLuint tex_id, vec<float> &verts, pt3_f camera_pos);

      private:
        void init();

        void cleanup();

        glm::vec3 compute_normal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

        s_ptr<shader_program> shader_program_;
        std::map<float, std::map<float, entry>> imgs_;
    };

    class model_rend
    {
      public:
        model_rend() { init(); }

        void draw_model(int model_name_hash, float x, float y, float elev,
                        pt3_f camera_pos, float elev_h);

      private:
        void init();

        s_ptr<shader_program> shader_program_;
        std::map<float, std::map<float, std::map<float, std::map<int, entry>>>>
            models_;
        static constexpr float k_mdl_scale{0.08f};
    };

    enum struct font_szs
    {
        _20 = 20,
        _26 = 26
    };

    class text_rend
    {
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
};
}
_NS_END_