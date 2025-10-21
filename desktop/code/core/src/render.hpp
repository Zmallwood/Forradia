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
  protected:
    class ShaderProgram
    {
      public:
        ShaderProgram(StringView vert_src, StringView frag_src)
        {
            init(vert_src, frag_src);
        }

        ~ShaderProgram()
        {
            cleanup();
        }

        auto program() const
        {
            return program_;
        }

      private:
        void init(StringView vert_src, StringView frag_src);

        void cleanup();

        GLuint program_;
    };

    class Image2DRenderer
    {
      public:
        Image2DRenderer()
        {
            init();
        };

        ~Image2DRenderer()
        {
            cleanup();
        }

        void reset_counter();

        void draw_img(StringView img_name, float x, float y, float w, float h);

        void draw_img(int img_name_hash, float x, float y, float w, float h);

        void draw_tex(GLuint tex_id, float x, float y, float w, float h);

        void draw_img_auto_h(StringView img_name, float x, float y, float w);

      private:
        void init();

        void cleanup();

        class Entry
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

        SharedPtr<ShaderProgram> shader_program_;
        std::map<int, std::map<int, Entry>> imgs_;
        int counter_{0};
    };

    class Entry
    {
      public:
        GLuint vao;
        GLuint ibo;
        GLuint vbo;
        float x;
        float y;
        float z;
    };

    class GroundRenderer
    {
      public:
        GroundRenderer()
        {
            init();
        };

        ~GroundRenderer()
        {
            cleanup();
        }

        void draw_tile(int img_name_hash, int x_coord, int y_coord, float tl_sz,
                       Point3F camera_pos, Vector<float> &elevs, float elev_h);

        void draw_tex(GLuint tex_id, Vector<float> &verts, Point3F camera_pos);

      private:
        void init();

        void cleanup();

        glm::vec3 compute_normal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

        SharedPtr<ShaderProgram> shader_program_;
        std::map<float, std::map<float, Entry>> imgs_;
    };

    class ModelRenderer
    {
      public:
        ModelRenderer()
        {
            init();
        }

        void draw_model(int model_name_hash, float x, float y, float elev,
                        Point3F camera_pos, float elev_h);

      private:
        void init();

        SharedPtr<ShaderProgram> shader_program_;
        std::map<float, std::map<float, std::map<float, std::map<int, Entry>>>>
            models_;
        static constexpr float k_mdl_scale{0.08f};
    };

    enum struct FontSizes
    {
        _20 = 20,
        _26 = 26
    };

    class TextRenderer
    {
      public:
        TextRenderer()
        {
            init();
        }

        void draw_str(StringView text, float x, float y,
                      FontSizes font_sz = FontSizes::_20, bool cent_align = false,
                      Color text_color = Colors::wheat_transp) const;

      private:
        void init();

        void add_fonts();

        const String k_default_font_path{"./res/fonts/PixeloidSans.ttf"};

        std::map<FontSizes, SharedPtr<TTF_Font>> fonts_;
    };
};
}
_NS_END_