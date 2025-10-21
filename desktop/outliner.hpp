#pragma diag_suppress 266
#pragma diag_suppress 311
#pragma diag_suppress 20
#pragma diag_suppress 283
#pragma diag_suppress 65
#pragma diag_suppress 77
#pragma diag_suppress 146
#pragma diag_suppress 281
#pragma diag_suppress 18
#pragma diag_suppress 28
#pragma diag_suppress 1696

namespace Forradia
{
#define _HIDE_FROM_OUTLINER_ }
    _HIDE_FROM_OUTLINER_

// virtualInclude 'code/common/src/common.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#define _NS_START_                                                             \
    namespace Forradia                                                         \
    {
#define _NS_END_ }

#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
typedef struct _TTF_Font TTF_Font;
struct SDL_Color;
typedef uint8_t Uint8;

_NS_START_
namespace Common
{
    namespace Aliases
    {
        // A set of aliases for commonly used types.
        using String = std::string;
        using StringView = std::string_view;
        template <class T> using SharedPtr = std::shared_ptr<T>;
        template <class T> using Vector = std::vector<T>;
        template <class T> using Function = std::function<T>;
    }
    using namespace Aliases;
    namespace Constants
    {
        // Constants that may be used throughout the project.
        static constexpr int k_one_sec_millis{
            1000}; ///< Number of milliseconds in one second.
    }
    using namespace Constants;
    namespace Singletons
    {
        // Singleton functions
        /**
         * Returns a singleton of an object of type T, in the
         * form of a SharedPtr.
         *
         * \tparam T Type to get singleton for.
         * \return The singleton object as a SharedPtr.
         */
        template <class T> SharedPtr<T> __()
        {
            // Create singleton instance only once.
            static SharedPtr<T> inst = std::make_shared<T>();
            return inst;
        }

        /**
         * Returns a singleton of an object of type T, in the
         * form of a reference.
         *
         * \tparam T Type to get singleton for.
         * \return The singleton object as a reference.
         */
        template <class T> T &_()
        {
            // Use the SharedPtr singleton function to obtain
            // the singleton, but return a reference to it.
            return *__<T>();
        }
    }
    using namespace Singletons;
    namespace HelperClasses
    {
        // Convenience classes
        /**
         * Class used for SharedPtrs of SDL objects,
         * which handles automaticallyfreeing up resources at object deletion.
         */
        class SDLDeleter
        {
          public:
            /**
             * Operator overloading for SDL_Window objects.
             *
             * \param win SDL window pointer to free resources for.
             */
            void operator()(SDL_Window *win) const;

            /**
             * Operator overloading for SDL_Renderer objects.
             *
             * \param rend SDL renderer pointer to free resources for.
             */
            void operator()(SDL_Renderer *rend) const;

            /**
             * Operator overloading for SDL_Surface objects.
             *
             * \param surf SDL surface pointer to free resources for.
             */
            void operator()(SDL_Surface *surf) const;

            /**
             * Operator overloading for SDL_Texture objects.
             *
             * \param tex SDL texture pointer to free resources for.
             */
            void operator()(SDL_Texture *tex) const;

            /**
             * Operator overloading for TTF_Font objects.
             *
             * \param font SDL font pointer to free resources for.
             */
            void operator()(TTF_Font *font) const;
        };
    }
    using namespace HelperClasses;
    namespace Matter
    {
        /**
         * Point in 2D space, using dimensions of int type.
         */
        class Point
        {
          public:
            /**
             * Equality operator between two Points.
             *
             * \param p Other Point to check equality against.
             * \return True if the two points are equal, otherwise false.
             */
            bool operator==(const Point &p) const;

            int x{0};
            int y{0};
        };

        /**
         * Point in 2D space using dimensions of float type.
         */
        class PointF
        {
          public:
            /**
             * Summing operator for the two points.
             *
             * \param p The other PointF to add to this point.
             * \return The resulting PointF with the dimensions added
             * separately.
             */
            PointF operator+(const PointF &p) const;

            /**
             * Subtraction operator for the two points.
             *
             * \param p The other PointF to subtract from this point.
             * \return The resulting PointF with the dimensions subtracted
             * separetely.
             */
            PointF operator-(const PointF &p) const;

            float x{0.0f}; ///< The x dimension.
            float y{0.0f}; ///< The y dimension.
        };

        /**
         * Point in 3D space using dimensions of float type.
         */
        class Point3F
        {
          public:
            float x{0.0f}; ///< The x dimension.
            float y{0.0f}; ///< The y dimension.
            float z{0.0f}; ///< The z dimension.
        };

        /**
         * Size in 2D space, with the dimensions as int values.
         */
        class Size
        {
          public:
            int w{0}; ///< Width.
            int h{0}; /// Height.
        };

        /**
         * Size in 2D space with dimensions of float values.
         */
        class SizeF
        {
          public:
            float w{0.0f}; ///< Width.
            float h{0.0f}; ///< Height.
        };

        /**
         * A rectangle in 2D space using dimensions of float type.
         */
        class RectF
        {
          public:
            /**
             * Check if this rectangle contains a certian point.
             *
             * \param p Point to check if it is contained in this rectangle.
             * \return True if the Point is within this rectangle, otherwise
             * false.
             */
            bool Contains(PointF p);

            /**
             * Returns only the position of this rectangle.
             *
             * \return The position.
             */
            PointF GetPosition() const;

            /**
             * Adds an offset to this rectangle, with the dimensions altered
             * separately.
             *
             * \param offs The offset to add.
             */
            void Offset(PointF offs);

            float x{0.0f}; ///< The x coordinate.
            float y{0.0f}; ///< The y coordinate.
            float w{0.0f}; ///< The width, in the x dimension.
            float h{0.0f}; ///< The height, in the y dimension.
        };
        namespace Coloring
        {
            /**
             * A RGBA color with components defined with float values.
             */
            class Color
            {
              public:
                /**
                 * Convert this color to a corresponding SDL_Color object.
                 *
                 * \return Corresponding SDL_Color object.
                 */
                SDL_Color ToSDLColor() const;

                float r{0.0f};
                float g{0.0f};
                float b{0.0f};
                float a{0.0f};
            };

            /**
             * Contains a palette of colors.
             */
            namespace Colors
            {
                constexpr Color black{0.0f, 0.0f, 0.0f, 1.0f}; ///< Black color.

                constexpr Color wheat{1.0f, 1.0f, 0.65f,
                                      1.0f}; ///< Wheat color.

                constexpr Color wheat_transp{
                    1.0f, 1.0f, 0.65f, 0.7f}; ///< Transparent wheat color.

                constexpr Color yellow{1.0f, 1.0f, 0.0f,
                                       1.0f}; ///< Yellow color.

                constexpr Color yellow_transp{
                    1.0f, 1.0f, 0.0f, 0.7f}; ///< Transparent yellow color.
            }
        }
        using namespace Coloring;
    }
    using namespace Matter;
    namespace Utilities
    {
        namespace CanvasUtilities
        {
            // Canvas util functions
            Size GetCanvasSize(SharedPtr<SDL_Window> win);

            /**
             * Calculate the aspect ratio of a given window.
             *
             * \param win Window to calculate the aspect ratio for.
             * \return The calculated aspect ratio.
             */
            float CalcAspectRatio(SharedPtr<SDL_Window> win);

            /**
             * Convert a width to a height based on the width and the aspect
             * ratio.
             *
             * \param w Width to convert.
             * \param win Window to calculate the aspect ratio for.
             * \return The resulting height.
             */
            float ConvertWidthToHeight(float w, SharedPtr<SDL_Window> win);

            /**
             * Convert a height to a width base on the height and the aspect
             * ratio.
             *
             * \param h Height to convert.
             * \param win Window to calculate the aspect ratio for.
             * \return The resulting width.
             */
            float ConvertHeightToWidth(float h, SharedPtr<SDL_Window> win);
        }
        using namespace CanvasUtilities;
        namespace FilePathUtilities
        {
            // File path util functions
            String GetFileExtension(StringView path);

            String GetFileNameNoExtension(StringView path);
        }
        using namespace FilePathUtilities;
        namespace MouseUtilities
        {
            // Mouse util functions
            PointF GetNormallizedMousePosition(SharedPtr<SDL_Window> win);
        }
        using namespace MouseUtilities;
        namespace NumbersUtilities
        {
            // Numbers util functions
            float InvertMovementSpeed(float num);

            int Normalize(int val);

            float Ceil(float num, float k);
        }
        using namespace NumbersUtilities;
        namespace RandomizationUtilities
        {
            // Randomization util functions
            void Randomize();

            int GetRandomInt(int upper_lim);
        }
        using namespace RandomizationUtilities;
        namespace StringUtilities
        {
            // String util functions
            String Replace(StringView text, char repl, char repl_with);
        }
        using namespace StringUtilities;
        namespace TimeUtilities
        {
            // Time util functions
            int GetTicks();
        }
        using namespace TimeUtilities;
        namespace HashUtilities
        {
            // Hash util functions
            /**
             * Compute hash code from a given input text, which
             * gets computed the same every game start.
             *
             * \param text Text to compute hash code for.
             * \return Computed hash code.
             */
            int Hash(StringView text);
        }
        using namespace HashUtilities;
        namespace PrintUtilities
        {
            // Print util functions
            /**
             * Print out a string of text, without a following line break.
             *
             * \param text Text to print.
             */
            void Print(StringView text);

            /**
             * Print out a string of text, with an added line break at the end.
             *
             * \param text Text to print.
             */
            void PrintLine(StringView text);
        }
        using namespace PrintUtilities;
        namespace CastUtilities
        {
            // Cast util functions
            /**
             * Cast a value to int.
             *
             * \param val Value to cast.
             * \return Casted value.
             */
            constexpr int CInt(auto val)
            {
                return static_cast<int>(val);
            }

            /**
             * Cast a value to float.
             *
             * \param val Value to cast.
             * \return Casted value.
             */
            float CFloat(auto val)
            {
                return static_cast<float>(val);
            }

            /**
             * Cast a value to Uint8.
             *
             * \param val Value to cast.
             * \return Casted value.
             */
            Uint8 CUint8(auto val)
            {
                return static_cast<Uint8>(val);
            }
        }
        using namespace CastUtilities;
    }
    using namespace Utilities;
}
using namespace Common;
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'code/core/src/core.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

#include "gui.hpp"
#include "render.hpp"

_NS_START_

namespace Core
{
    class Engine
    {
      public:
        class SDLDevice
        {
          public:
            ~SDLDevice();

            void Initialize(StringView game_win_title, Color clear_color);

            void ClearCanvas() const;

            void PresentCanvas() const;

            auto GetWindow() const
            {
                return m_window;
            }

          private:
            SharedPtr<SDL_Window> CreateWindow();

            Size GetScreenSize() const;

            SharedPtr<SDL_Window> m_window;
            SharedPtr<SDL_GLContext> m_context;
            String m_gameWindowTitle;
            Color m_clearColor;
        };

        class FPSCounter
        {
          public:
            void Update();

            auto GetFPS() const
            {
                return m_fps;
            }

          private:
            const PointF k_position{0.93f, 0.02f};

            int m_fps{0};
            int m_framesCount{0};
            int m_ticksLastUpdate{0};
        };

        class Cursor
        {
          public:
            enum class CursorStyles
            {
                normal,
                hovering_clickable_gui,
                hovering_creature
            };

            Cursor()
            {
                Initialize();
            }

            void ResetStyleToNormal();

            void Render();

            auto SetCursorStyle(CursorStyles value)
            {
                m_cursorStyle = value;
            }

          private:
            void Initialize();

            void DisableSystemCursor();

            constexpr static float k_cursorSize{0.05f};

            CursorStyles m_cursorStyle{CursorStyles::normal};
        };

        class Assets
        {
          public:
            class Images
            {
              public:
                class ImageBank
                {
                  public:
                    ImageBank()
                    {
                        Initialize();
                    }

                    ~ImageBank()
                    {
                        Cleanup();
                    }

                    GLuint GetTexture(int img_name_hash) const;

                    Size GetImageSize(int img_name_hash) const;

                    bool TextTextureExists(float x, float y,
                                           int unique_id) const;

                    GLuint ObtainTextTexture(float x, float y, int text_hash);

                  private:
                    void Initialize();

                    void Cleanup();

                    void LoadImages();

                    GLuint LoadSingleTexture(SharedPtr<SDL_Surface> surf);

                    inline static const String k_relativeImagesPath{
                        "./res/images/"};

                    std::map<int, GLuint> m_textures;
                    std::map<int, Size> m_textureSizes;
                    std::map<float, std::map<float, std::map<int, GLuint>>>
                        m_textTextures;
                };
            };
            class Models
            {
              public:
                class ModelBank
                {
                  public:
                    class Vertex
                    {
                      public:
                        glm::vec3 position;
                        glm::vec3 normal;
                        glm::vec2 tex_coord;
                        glm::vec3 tangent;
                        glm::vec3 bitangent;
                    };

                    class Texture
                    {
                      public:
                        String path;
                    };

                    class Mesh
                    {
                      public:
                        Vector<Vertex> vertices;
                        Vector<unsigned int> indices;
                        Vector<Texture> textures;
                        glm::vec3 extents;
                        glm::vec3 origin;
                        aiString name;
                    };

                    class Model
                    {
                      public:
                        Model(StringView file_path)
                        {
                            Initialize(file_path);
                        };

                        auto &GetMeshesRef() const
                        {
                            return m_meshes;
                        }

                      private:
                        void Initialize(StringView file_path);

                        void ProcessNode(aiNode *node, const aiScene *scene,
                                         aiMatrix4x4 transform);

                        Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene,
                                         aiMatrix4x4 transformation);

                        Vector<Vertex> GetVertices(aiMesh *mesh,
                                                   glm::vec3 &extents,
                                                   glm::vec3 &origin,
                                                   aiMatrix4x4 transformation);

                        Vector<unsigned int> GetIndices(aiMesh *mesh);

                        Vector<Texture> GetTextures(aiMesh *mesh,
                                                    const aiScene *scene);

                        Vector<Mesh> m_meshes;
                    };

                  public:
                    ModelBank()
                    {
                        Initialize();
                    }

                    SharedPtr<Model> GetModel(int model_name_hash) const;

                  private:
                    void Initialize();

                    SharedPtr<Model> LoadSingleModel(StringView file_path);

                    inline static const String k_relativeModelsPath{
                        "./res/models/"};

                    std::map<int, SharedPtr<Model>> m_models;
                };
            };
        };
        class ScenesCore
        {
          public:
            class IScene
            {
              public:
                class ScenesGUI
                {
                  public:
                    class GUIRoot : public GUIComponentsLibrary::GUIComponent
                    {
                      public:
                        GUIRoot() : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f)
                        {
                        }
                    };
                };

                void Initialize();

                void Update();

                void Render() const;

                void OnEnter();

                void SetInitializeDerived(Function<void()> value)
                {
                    m_initializeDerived = value;
                }

                void SetOnEnterDerived(Function<void()> value)
                {
                    m_onEnterDerived = value;
                }

                void SetUpdateDerived(Function<void()> value)
                {
                    m_updateDerived = value;
                }

                void SetRenderDerived(Function<void()> value)
                {
                    m_renderDerived = value;
                }

              protected:
                auto GetGUI() const
                {
                    return m_gui;
                }

              private:
                SharedPtr<ScenesGUI::GUIRoot> m_gui;
                Function<void()> m_initializeDerived{[] {}};
                Function<void()> m_onEnterDerived{[] {}};
                Function<void()> m_updateDerived{[] {}};
                Function<void()> m_renderDerived{[] {}};
            };

            class SceneManager
            {
              public:
                void AddScene(StringView scene_name, IScene &scene);

                void GoToScene(StringView scene_name);

                void UpdateCurrentScene();

                void RenderCurrentScene() const;

              private:
                std::map<int, IScene &> m_scenes;
                int m_currentScene{0};
            };
        };
        class Input
        {
          public:
            class KeyboardInput
            {
              public:
                void Reset();

                void RegisterKeyPress(SDL_Keycode key);

                void RegisterKeyRelease(SDL_Keycode key);

                bool KeyIsPressed(SDL_Keycode key) const;

                bool KeyIsPressedPickResult(SDL_Keycode key);

                bool AnyKeyIsPressedPickResult();

              private:
                std::set<SDL_Keycode> m_pressed;
            };

            class MouseInput
            {
              public:
                class MouseButton
                {
                  public:
                    void Reset();

                    void RegisterPress();

                    void RegisterRelease();

                    bool IsPressedPickResult();

                    bool HasBeenFiredPickResult();

                    bool HasBeenFired();

                    bool HasBeenReleasedPickResult();

                    bool HasBeenReleased();

                  private:
                    bool m_pressed{false};
                    bool m_hasBeenFired{false};
                    bool m_hasBeenReleased{false};
                };

                class LeftMouseButton : public MouseButton
                {
                  public:
                    using MouseButton::Reset;

                    using MouseButton::RegisterPress;

                    using MouseButton::RegisterRelease;

                    using MouseButton::IsPressedPickResult;

                    using MouseButton::HasBeenFiredPickResult;

                    using MouseButton::HasBeenFired;

                    using MouseButton::HasBeenReleasedPickResult;

                    using MouseButton::HasBeenReleased;
                };

                class RightMouseButton : public MouseButton
                {
                  public:
                    using MouseButton::Reset;

                    using MouseButton::RegisterPress;

                    using MouseButton::RegisterRelease;

                    using MouseButton::IsPressedPickResult;

                    using MouseButton::HasBeenFiredPickResult;

                    using MouseButton::HasBeenFired;

                    using MouseButton::HasBeenReleasedPickResult;

                    using MouseButton::HasBeenReleased;
                };

                void Reset();

                void RegisterMouseButtonDown(Uint8 btn);

                void RegisterMouseButtonUp(Uint8 btn);

                bool AnyMouseButtonIsPressedPickResult();
            };
        };
        class Renderers : public RenderersCollection
        {
          public:
            using RenderersCollection::FontSizes;
            using RenderersCollection::GroundRenderer;
            using RenderersCollection::Image2DRenderer;
            using RenderersCollection::ModelRenderer;
            using RenderersCollection::TextRenderer;
        };

        void Initialize(StringView game_win_title, Color clear_color) const;

        void Run();

        void Stop();

      private:
        void PollEvents();

        bool m_running{true};
    };
#define _HIDE_FROM_OUTLINER_CORE_BOTTOM_ }
    _HIDE_FROM_OUTLINER_CORE_BOTTOM_
    using namespace Core;
    _NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'code/core/src/gui.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
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
namespace GUIComponentsLibrary
{
    class GUIComponent
    {
      public:
        GUIComponent(float x, float y, float w, float h)
            : m_bounds({x, y, w, h})
        {
        }

        SharedPtr<GUIComponent> AddChildComponent(SharedPtr<GUIComponent> comp);

        void Update();

        void Render() const;

        virtual RectF GetBounds() const;

        void SetPosition(PointF new_pos);

        void ToggleVisibility();

        auto GetVisible() const
        {
            return m_visible;
        }

        void SetVisible(bool value)
        {
            m_visible = value;
        }

        void SetParentComponent(GUIComponent *value)
        {
            m_parentComponent = value;
        }

      protected:
        virtual void UpdateDerived()
        {
        }

        virtual void RenderDerived() const
        {
        }

      private:
        RectF m_bounds;
        Vector<SharedPtr<GUIComponent>> m_childComponents;
        bool m_visible{true};
        bool m_enabled{true};
        GUIComponent *m_parentComponent{nullptr};
    };

    class GUILabel : public GUIComponent
    {
      public:
        GUILabel(float x, float y, float w, float h, StringView text = "",
                 bool cent_align = false, Color color = Colors::wheat_transp)
            : GUIComponent(x, y, w, h), m_text(text), m_centerAlign(cent_align),
              m_color(color)
        {
        }

        void SetText(StringView value)
        {
            m_text = value;
        }

      protected:
        virtual void RenderDerived() const override;

      private:
        String m_text;
        bool m_centerAlign{false};
        Color m_color;
    };

    class GUIPanel : public GUIComponent
    {
      public:
        GUIPanel(float x, float y, float w, float h,
                 StringView bg_img = k_defaultBackgroundImage)
            : GUIComponent(x, y, w, h), m_backgroundImage(bg_img)
        {
        }

      protected:
        virtual void RenderDerived() const override;

        void SetBackgroundImage(StringView value)
        {
            m_backgroundImage = value;
        }

      private:
        inline static const String k_defaultBackgroundImage{"gui_panel_bg"};

        String m_backgroundImage;
    };

    class GUIButton : public GUIPanel
    {
      public:
        GUIButton(float x, float y, float w, float h, StringView text,
                  Function<void()> action, StringView bg_img = k_backgroundImage,
                  StringView hovered_bg_img = k_hoveredBackgroundImage)
            : GUIPanel(x, y, w, h), m_text(text), m_action(action),
              m_backgroundImage(bg_img), m_hoveredBackgroundImage(hovered_bg_img)
        {
        }

      protected:
        virtual void UpdateDerived() override;

        virtual void RenderDerived() const override;

      private:
        inline static const String k_backgroundImage{"gui_button_bg"};
        inline static const String k_hoveredBackgroundImage{"gui_button_hovered_bg"};

        String m_text;
        Function<void()> m_action;
        String m_backgroundImage;
        String m_hoveredBackgroundImage;
    };

    class GUIMovablePanel : public GUIPanel
    {
      public:
        GUIMovablePanel(float x, float y, float w, float h)
            : GUIPanel(x, y, w, h)
        {
        }

      protected:
        void UpdateDerived() override;

        void StartMove();

        void StopMove();

        virtual RectF GetDragArea();

        auto GetIsBeingMoved() const
        {
            return m_isBeingMoved;
        }

        auto GetMoveStartingPosition() const
        {
            return m_moveStartingPosition;
        }

        auto GetMoveStartingMousePosition() const
        {
            return m_moveStartingMousePosition;
        }

      private:
        bool m_isBeingMoved{false};
        PointF m_moveStartingPosition{-1, -1};
        PointF m_moveStartingMousePosition{-1, -1};
    };

    class GUIWindow : public GUIMovablePanel
    {
      public:
        GUIWindow(float x, float y, float w, float h, StringView win_title)
            : GUIMovablePanel(x, y, w, h)
        {
            Initialize(win_title);
        }

      protected:
        void RenderDerived() const override;

        RectF GetDragArea() override;

        auto GetGUIWindowTitleBar() const
        {
            return m_guiWindowTitleBar;
        }

      private:
        void Initialize(StringView win_title);

        class GUIWindowTitleBar : public GUIPanel
        {
          public:
            GUIWindowTitleBar(GUIWindow &parent_win, StringView win_title)
                : m_parentWindow(parent_win), k_windowTitle(win_title),
                  GUIPanel(0.0f, 0.0f, 0.0f, 0.0f, "gui_win_title_bar_bg")
            {
                Initialize();
            }

            void RenderDerived() const override;

            RectF GetBounds() const override;

          private:
            void Initialize();

            inline static const float k_h{0.04f};
            const String k_windowTitle;

            GUIWindow &m_parentWindow;
        };

        SharedPtr<GUIWindowTitleBar> m_guiWindowTitleBar;
    };

    class GUIFPSPanel : public GUIMovablePanel
    {
      public:
        GUIFPSPanel() : GUIMovablePanel(0.92f, 0.02f, 0.07f, 0.04f)
        {
            Initialize();
        }

      protected:
        void UpdateDerived() override;

      private:
        void Initialize();

        SharedPtr<GUILabel> m_fpsTextPanel;
    };

    class GUIChatBox : public GUIPanel
    {
      public:
        GUIChatBox()
            : GUIPanel(0.0f, 0.8f, 0.4f, 0.2f, k_defaultBackgroundImageDerived)
        {
        }

        void RenderDerived() const override;

        void Print(StringView text);

      private:
        constexpr static StringView k_defaultBackgroundImageDerived{"gui_chat_box_bg"};
        inline static const float k_lineHeight{0.025f};
        inline static const float k_separatorHeight{0.003f};
        inline static const float k_margin{0.008f};

        Vector<String> m_lines;
    };
}
#define _HIDE_FROM_OUTLINER_CORE_BOTTOM_ }
_HIDE_FROM_OUTLINER_CORE_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'code/core/src/render.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
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

        auto GetProgram() const
        {
            return program_;
        }

      private:
        void Initialize(StringView vert_src, StringView frag_src);

        void Cleanup();

        GLuint program_;
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
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 


// virtualInclude 'code/theme_0/src/theme_0_core.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
namespace Theme0
{
    namespace TileGridMath
    {
        SizeF CalcTileSize();

        float CalcTileSizeNew();

        Size CalcGridSize();
    }
    using namespace TileGridMath;

    namespace GameplayCore
    {
        namespace Player
        {
            enum class BodyPartTypes
            {
                none,
                overall_body,
                right_arm,
                left_arm,
                legs
            };

            class BodyPart
            {
              public:
                auto GetStrength() const
                {
                    return strength_;
                }
                auto GetCurrentEnergy() const
                {
                    return current_energy_;
                }
                auto GetMaxEnergy() const
                {
                    return max_energy_;
                }
                auto GetTemperature() const
                {
                    return temperature_;
                }

              private:
                float strength_{0.1f};
                float current_energy_{1.0f};
                float max_energy_{1.0f};
                float temperature_{37.0f};
            };

            class PlayerBody
            {
              public:
                PlayerBody()
                {
                    Initialize();
                }

                BodyPart *GetBodyPartPtr(BodyPartTypes type);

              private:
                void Initialize();

                std::map<BodyPartTypes, BodyPart> parts_;
            };

            class PlayerCharacter
            {
              public:
                PlayerCharacter()
                {
                    Initialize();
                }

                void MoveNorth();

                void MoveEast();

                void MoveSouth();

                void MoveWest();

                auto GetName() const
                {
                    return name_;
                }

                auto GetPosition() const
                {
                    return position_;
                }

                auto GetMovementSpeed() const
                {
                    return movement_speed_;
                }

                auto GetTicksLastMovement() const
                {
                    return ticks_last_movement_;
                }

                void SetTicksLastMovement(int value)
                {
                    ticks_last_movement_ = value;
                }

                auto GetDestination() const
                {
                    return destination_;
                }

                void SetDestination(Point value)
                {
                    destination_ = value;
                }

                auto &GetBodyRef()
                {
                    return body_;
                }

                auto GetMoney() const
                {
                    return money_;
                }

              private:
                void Initialize();

                void MoveToSuitablePosition();

                String name_{"Unnamed Player"};
                Point position_{60, 50};
                float movement_speed_{5.0f};
                int ticks_last_movement_{0};
                Point destination_{-1, -1};
                PlayerBody body_;
                int money_{0};
            };
        }
        using namespace Player;
#define _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_1_                             \
    }                                                                          \
    using namespace GameplayCore;
        _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_1_
#define _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_2_ }
        _HIDE_FROM_OUTLINER_THEME_0_CORE_BOTTOM_2_
        using namespace Theme0;
        _NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 




// virtualInclude 'code/theme_0/src/update.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_UPDATE_TOP_1_                                      \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_UPDATE_TOP_1_
#define _HIDE_FROM_OUTLINER_UPDATE_TOP_2_                                      \
    namespace GameplayCore                                                     \
    {
_HIDE_FROM_OUTLINER_UPDATE_TOP_2_
void UpdateKeyboardActions();

void UpdateMouseActions();

void UpdateKeyboardMovement();

void UpdateMouseMovement();

void UpdateCreaturesMovement();

void UpdateNPCs();

class TileHovering
{
  public:
    void Update();

    auto GetHoveredCoordinate() const
    {
        return hovered_coordinate_;
    }

  private:
    Point hovered_coordinate_{-1, -1};
};
#define _HIDE_FROM_OUTLINER_UPDATE_BOTTOM_1_ }
_HIDE_FROM_OUTLINER_UPDATE_BOTTOM_1_
#define _HIDE_FROM_OUTLINER_UPDATE_BOTTOM_2_ }
_HIDE_FROM_OUTLINER_UPDATE_BOTTOM_2_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 





// virtualInclude 'code/theme_0/src/world_view.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_1_                                  \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_1_
#define _HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_2_                                  \
    namespace GameplayCore                                                     \
    {
_HIDE_FROM_OUTLINER_WORLD_VIEW_TOP_2_
class WorldView
{
  public:
    void Render() const;
};
}
#define _HIDE_FROM_OUTLINER_WORLD_VIEW_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_VIEW_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 




// virtualInclude 'code/theme_0_world_struct/src/world_struct.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_WORLD_STRUCT_TOP_                                  \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_WORLD_STRUCT_TOP_
namespace WorldStructure
{
    enum class Directions
    {
        none,
        n,
        e,
        s,
        w,
        ne,
        se,
        sw,
        nw
    };

    class Creature
    {
      public:
        Creature(StringView type_name) : type_{Hash(type_name)}
        {
            Initialize();
        }

        auto GetType() const
        {
            return type_;
        }

        auto GetTicksLastMovement() const
        {
            return ticks_last_movement_;
        }

        void SetTicksLastMovement(int value)
        {
            ticks_last_movement_ = value;
        }

        auto GetMovementSpeed() const
        {
            return movement_speed_;
        }

        auto GetDestination() const
        {
            return destination_;
        }

        void SetDestination(Point value)
        {
            destination_ = value;
        }

      private:
        void Initialize();

        int type_{0};
        int ticks_last_movement_{0};
        float movement_speed_{2.0f};
        Point destination_{-1, -1};
    };

    class NPC
    {
      public:
        NPC(StringView type_name) : type_{Hash(type_name)}
        {
            Initialize();
        }

        auto GetType() const
        {
            return type_;
        }

        auto GetName() const
        {
            return name_;
        }

        auto GetTicksLastMovement() const
        {
            return ticks_last_movement_;
        }

        void SetTicksLastMovement(int value)
        {
            ticks_last_movement_ = value;
        }

        auto GetMovementSpeed() const
        {
            return movement_speed_;
        }

        auto GetDestination() const
        {
            return destination_;
        }

        void SetDestination(Point value)
        {
            destination_ = value;
        }

        auto GetTicksNextSpontaneousSpeech() const
        {
            return ticks_next_spontaneous_speech_;
        }

        void SetTicksNextSpontaneousSpeech(int value)
        {
            ticks_next_spontaneous_speech_ = value;
        }

      private:
        void Initialize();

        void GenerateName();

        int type_{0};
        String name_;
        int ticks_last_movement_{0};
        float movement_speed_{2.0f};
        Point destination_{-1, -1};
        int ticks_next_spontaneous_speech_{0};
    };

    class Object
    {
      public:
        Object(StringView object_type_name) : type_(Hash(object_type_name))
        {
        }

        auto GetType() const
        {
            return type_;
        }

      private:
        int type_{0};
    };

    class TreeObject : public Object
    {
      public:
        TreeObject(StringView obj_type_name) : Object(obj_type_name)
        {
            Initialize(obj_type_name);
        }

        auto GetTrunkParts() const
        {
            return trunk_parts_;
        }

        auto GetNeedleTypes() const
        {
            return needle_types_;
        }

        auto GetWidthFactor() const
        {
            return width_factor_;
        }

      private:
        void Initialize(StringView obj_type_name);

        Vector<PointF> trunk_parts_;
        Vector<int> needle_types_;
        float width_factor_{1.0f};
    };

    class ObjectsStack
    {
      public:
        void ClearObjects();

        void AddObject(StringView obj_type_name);

        void AddTreeObject(StringView obj_type_name);

        int GetSize() const;

        auto GetObjects() const
        {
            return objects_;
        }

      private:
        Vector<SharedPtr<Object>> objects_;
    };

    class Tile
    {
      public:
        Tile()
        {
            Initialize();
        }

        auto GetGround() const
        {
            return ground_;
        }

        void SetGround(StringView ground_name);

        auto GetObjectsStack() const
        {
            return objects_stack_;
        }

        auto GetCreature() const
        {
            return creature_;
        }

        void SetCreature(SharedPtr<Forradia::Theme0::WorldStructure::Creature> val)
        {
            creature_ = val;
        }

        auto GetNPC() const
        {
            return npc_;
        }

        void SetNPC(SharedPtr<Forradia::Theme0::WorldStructure::NPC> value)
        {
            npc_ = value;
        }

        auto GetElevation() const
        {
            return elevation_;
        }

        void SetElevation(int value)
        {
            elevation_ = value;
        }

        auto GetWaterDepth() const
        {
            return water_depth_;
        }

        void SetWaterDepth(int value)
        {
            water_depth_ = value;
        }

        auto GetRiverDirection1() const
        {
            return river_direction_1_;
        }

        void SetRiverDirection1(Directions value)
        {
            river_direction_1_ = value;
        }

        auto GetRiverDirection2() const
        {
            return river_direction_2_;
        }

        void SetRiverDirection2(Directions value)
        {
            river_direction_2_ = value;
        }

      private:
        void Initialize();

        int ground_{0};
        SharedPtr<Forradia::Theme0::WorldStructure::ObjectsStack> objects_stack_;
        SharedPtr<Forradia::Theme0::WorldStructure::Creature> creature_;
        SharedPtr<Forradia::Theme0::WorldStructure::NPC> npc_;
        int elevation_{0};
        int water_depth_{0};
        Directions river_direction_1_{Directions::none};
        Directions river_direction_2_{Directions::none};
    };

    class WorldArea
    {
      public:
        WorldArea(Size w_area_sz, float world_scaling)
        {
            Initialize(w_area_sz, world_scaling);
        }

        Size GetSize() const;

        bool IsValidCoordinate(int x, int y) const;

        bool IsValidCoordinate(Point coord) const;

        SharedPtr<Tile> GetTile(int x, int y) const;

        SharedPtr<Tile> GetTile(Point coord) const;

        auto &GetCreaturesMirrorRef()
        {
            return creatures_mirror_;
        }

        auto &GetNPCsMirrorRef()
        {
            return npcs_mirror_;
        }

      private:
        void Initialize(Size w_area_sz, float world_scaling);

        Vector<Vector<SharedPtr<Tile>>> tiles_;
        std::map<SharedPtr<Creature>, Point> creatures_mirror_;
        std::map<SharedPtr<NPC>, Point> npcs_mirror_;
    };

    class World
    {
      public:
        void Initialize(Size w_area_sz, float world_scaling);

        auto GetCurrentWorldArea() const
        {
            return current_world_area_;
        }

      private:
        SharedPtr<WorldArea> current_world_area_;
    };
}
using namespace WorldStructure;
#define _HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 


// virtualInclude 'code/theme_0/src/game_props.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_GAME_PROPS_TOP_                                    \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_GAME_PROPS_TOP_
namespace Configuration
{
    class GameProperties
    {
      public:
        static constexpr String k_game_win_title{"Forradia"};
        static constexpr Color k_clear_color{Colors::black};
        static constexpr int k_num_grid_rows{15};
        static constexpr Size k_w_area_sz{120, 100};
        static constexpr float k_world_scaling{5.0f};
    };
}
using namespace Configuration;
#define _HIDE_FROM_OUTLINER_GAME_PROPS_BOTTOM_ }
_HIDE_FROM_OUTLINER_GAME_PROPS_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

// virtualInclude 'code/theme_0/src/gui_spec.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_GUI_SPEC_TOP_                                      \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_GUI_SPEC_TOP_
namespace SpecializedGUI
{
    class GUIPlayerStatusBox : public Core::GUIComponentsLibrary::GUIPanel
    {
      public:
        GUIPlayerStatusBox() : GUIPanel(0.0f, 0.0f, 0.2f, 0.14f)
        {
        }

      protected:
        virtual void RenderDerived() const override;
    };

    class GUISystemMenu : public Core::GUIComponentsLibrary::GUIComponent
    {
      public:
        GUISystemMenu() : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f)
        {
            Initialize();
        }

      protected:
        void Initialize();

        virtual void UpdateDerived() override;

        virtual void RenderDerived() const override;
    };

    class GUIInventoryWindow : public Core::GUIComponentsLibrary::GUIWindow
    {
      public:
        GUIInventoryWindow() : GUIWindow(0.5f, 0.2f, 0.2f, 0.5f, "Inventory")
        {
        }

      protected:
        void RenderDerived() const override;

      private:
        static constexpr float k_margin{0.005f};
        static constexpr float k_slot_size{0.04f};
        inline static const String k_slot_img_name{"gui_inventory_win_slot_bg"};
    };

    class GUIPlayerBodyWindow : public Core::GUIComponentsLibrary::GUIWindow
    {
      public:
        GUIPlayerBodyWindow() : GUIWindow(0.2f, 0.2f, 0.2f, 0.5f, "Player body")
        {
            Initialize();
        }

      protected:
        void Initialize();

      private:
        void SelectBodyPart(int type);

        void UpdateBodyPartInfoLabels();

        int sel_body_part_{0};
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_name_;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_str_;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_energy_;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> lbl_body_part_temp_;
    };

    class GUIInteractionMenu : public Core::GUIComponentsLibrary::GUIPanel
    {
      public:
        GUIInteractionMenu() : GUIPanel(0.0f, 0.0f, 0.2f, 0.14f)
        {
            Initialize();
        }

        void BuildMenu();

      protected:
        void Initialize();

        virtual void UpdateDerived() override;

        virtual void RenderDerived() const override;

      private:
        static constexpr float k_indent_w{0.01f};
        static constexpr float k_line_h{0.025f};

        class GUIInteractionMenuEntry
        {
          public:
            GUIInteractionMenuEntry(StringView label, Function<void()> action)
                : label_(label), action_(action)
            {
            }

            auto GetLabel() const
            {
                return label_;
            }

            auto GetAction() const
            {
                return action_;
            }

          private:
            String label_;
            Function<void()> action_;
        };

        Vector<GUIInteractionMenuEntry> entries_;
    };
}
using namespace SpecializedGUI;
#define _HIDE_FROM_OUTLINER_GUI_SPEC_BOTTOM_ }
_HIDE_FROM_OUTLINER_GUI_SPEC_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 



// virtualInclude 'code/theme_0/src/world_gen.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "common.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_FORWARD_DECL_WORLD_GRATOR_TOP_                     \
    namespace Theme0                                                           \
    {                                                                          \
        namespace WorldStructure                                               \
        {                                                                      \
            class WorldArea;                                                   \
        }                                                                      \
    }
_HIDE_FROM_OUTLINER_FORWARD_DECL_WORLD_GRATOR_TOP_
#define _HIDE_FROM_OUTLINER_WORLD_GRATOR_TOP_                                  \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_WORLD_GRATOR_TOP_
namespace WorldGeneration
{
    class WorldGenerator
    {
      public:
        void GenerateNewWorld();

      private:
        void Prepare();
        void ClearWithDirt() const;
        void GenerateGrass() const;
        void GenerateLakes() const;
        void GenerateSingleLake(int min_x, int min_y, int max_x, int max_y,
                                int recurs) const;
        void GenerateElevation() const;
        void GenerateRock() const;
        void GenerateRivers() const;
        void GenerateObjects() const;
        void GenerateCreatures() const;
        void GenerateNPCs() const;

        SharedPtr<Theme0::WorldStructure::WorldArea> w_area_;
        float scale_;
        Size sz_;
    };
}
using namespace WorldGeneration;
#define _HIDE_FROM_OUTLINER_WORLD_GRATOR_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_GRATOR_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 


// virtualInclude 'code/theme_0/src/scripts.hpp'
// virtualIncludeStart - DO NOT EDIT CONTENT BELOW 
/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_SCRIPTS_TOP_                                       \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_SCRIPTS_TOP_
namespace Scripting
{
    class ScriptEngine
    {
      public:
        void Initialize();

        void LoadScripts();
    };
}
using namespace Scripting;
}
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 









#define _HIDE_FROM_OUTLINER_ namespace Forradia {
_HIDE_FROM_OUTLINER_
}