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
            Initialize(vert_src, frag_src);
        }

        ~ShaderProgram()
        {
            Cleanup();
        }

        auto GetProgramID() const
        {
            return m_programID;
        }

      private:
        void Initialize(StringView vert_src, StringView frag_src);

        void Cleanup();

        GLuint m_programID;
    };

    class Image2DRenderer
    {
      public:
        Image2DRenderer()
        {
            Initialize();
        };

        ~Image2DRenderer()
        {
            Cleanup();
        }

        void ResetCounter();

        void DrawImage(StringView img_name, float x, float y, float w, float h);

        void DrawImage(int img_name_hash, float x, float y, float w, float h);

        void DrawTexture(GLuint tex_id, float x, float y, float w, float h);

        void DrawImageAutoHeight(StringView img_name, float x, float y, float w);

      private:
        void Initialize();

        void Cleanup();

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

        SharedPtr<ShaderProgram> m_shaderProgram;
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
            Initialize();
        };

        ~GroundRenderer()
        {
            Cleanup();
        }

        void DrawTile(int img_name_hash, int x_coord, int y_coord, float tl_sz,
                       Point3F camera_pos, Vector<float> &elevs, float elev_h);

        void DrawTexture(GLuint tex_id, Vector<float> &verts, Point3F camera_pos);

      private:
        void Initialize();

        void Cleanup();

        glm::vec3 ComputeNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

        SharedPtr<ShaderProgram> shader_program_;
        std::map<float, std::map<float, Entry>> imgs_;
    };

    class ModelRenderer
    {
      public:
        ModelRenderer()
        {
            Initialize();
        }

        void DrawModel(int model_name_hash, float x, float y, float elev,
                        Point3F camera_pos, float elev_h);

      private:
        void Initialize();

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
            Initialize();
        }

        void DrawString(StringView text, float x, float y,
                      FontSizes font_sz = FontSizes::_20, bool cent_align = false,
                      Color text_color = Colors::wheat_transp) const;

      private:
        void Initialize();

        void AddFonts();

        const String k_default_font_path{"./res/fonts/PixeloidSans.ttf"};

        std::map<FontSizes, SharedPtr<TTF_Font>> fonts_;
    };
};
}
_NS_END_