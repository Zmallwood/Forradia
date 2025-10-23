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
#pragma diag_suppress 262
#pragma diag_suppress 243
#pragma diag_suppress 864
#pragma diag_suppress 169
#pragma diag_suppress 1670
#pragma diag_suppress 239
#pragma diag_suppress 276

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
        static constexpr int k_oneSecMillis{
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
            static SharedPtr<T> instance{std::make_shared<T>()};

            return instance;
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
             * \param window SDL window pointer to free resources for.
             */
            void operator()(SDL_Window *window) const;

            /**
             * Operator overloading for SDL_Renderer objects.
             *
             * \param renderer SDL renderer pointer to free resources for.
             */
            void operator()(SDL_Renderer *renderer) const;

            /**
             * Operator overloading for SDL_Surface objects.
             *
             * \param surface SDL surface pointer to free resources for.
             */
            void operator()(SDL_Surface *surface) const;

            /**
             * Operator overloading for SDL_Texture objects.
             *
             * \param texture SDL texture pointer to free resources for.
             */
            void operator()(SDL_Texture *texture) const;

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
             * \param other Other Point to check equality against.
             * \return True if the two points are equal, otherwise false.
             */
            bool operator==(const Point &other) const;

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
             * \param other The other PointF to add to this point.
             * \return The resulting PointF with the dimensions added
             * separately.
             */
            PointF operator+(const PointF &other) const;

            /**
             * Subtraction operator for the two points.
             *
             * \param other The other PointF to subtract from this point.
             * \return The resulting PointF with the dimensions subtracted
             * separetely.
             */
            PointF operator-(const PointF &other) const;

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
            int width{0};  ///< Width.
            int height{0}; /// Height.
        };

        /**
         * Size in 2D space with dimensions of float values.
         */
        class SizeF
        {
          public:
            float width{0.0f};  ///< Width.
            float height{0.0f}; ///< Height.
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
             * \param point Point to check if it is contained in this rectangle.
             * \return True if the Point is within this rectangle, otherwise
             * false.
             */
            bool Contains(PointF point);

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
             * \param offset The offset to add.
             */
            void Offset(PointF offset);

            float x{0.0f};      ///< The x coordinate.
            float y{0.0f};      ///< The y coordinate.
            float width{0.0f};  ///< The width, in the x dimension.
            float height{0.0f}; ///< The height, in the y dimension.
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
                constexpr Color Black{0.0f, 0.0f, 0.0f, 1.0f}; ///< Black color.

                constexpr Color Wheat{1.0f, 1.0f, 0.65f,
                                      1.0f}; ///< Wheat color.

                constexpr Color WheatTransparent{
                    1.0f, 1.0f, 0.65f, 0.7f}; ///< Transparent wheat color.

                constexpr Color Yellow{1.0f, 1.0f, 0.0f,
                                       1.0f}; ///< Yellow color.

                constexpr Color YellowTransparent{
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
            Size GetCanvasSize(SharedPtr<SDL_Window> window);

            /**
             * Calculate the aspect ratio of a given window.
             *
             * \param window Window to calculate the aspect ratio for.
             * \return The calculated aspect ratio.
             */
            float CalcAspectRatio(SharedPtr<SDL_Window> window);

            /**
             * Convert a width to a height based on the width and the aspect
             * ratio.
             *
             * \param width Width to convert.
             * \param window Window to calculate the aspect ratio for.
             * \return The resulting height.
             */
            float ConvertWidthToHeight(float width,
                                       SharedPtr<SDL_Window> window);

            /**
             * Convert a height to a width base on the height and the aspect
             * ratio.
             *
             * \param height Height to convert.
             * \param window Window to calculate the aspect ratio for.
             * \return The resulting width.
             */
            float ConvertHeightToWidth(float height,
                                       SharedPtr<SDL_Window> window);
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
            PointF GetNormallizedMousePosition(SharedPtr<SDL_Window> window);
        }
        using namespace MouseUtilities;
        namespace NumbersUtilities
        {
            // Numbers util functions
            float InvertMovementSpeed(float movementSpeed);

            int Normalize(int value);

            float Ceil(float number, float k);
        }
        using namespace NumbersUtilities;
        namespace RandomizationUtilities
        {
            // Randomization util functions
            void Randomize();

            int GetRandomInt(int upperLimit);
        }
        using namespace RandomizationUtilities;
        namespace StringUtilities
        {
            // String util functions
            String Replace(StringView text, char replace, char replaceWith);
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
             * \param value Value to cast.
             * \return Casted value.
             */
            constexpr int CInt(auto value)
            {
                return static_cast<int>(value);
            }

            /**
             * Cast a value to float.
             *
             * \param value Value to cast.
             * \return Casted value.
             */
            float CFloat(auto value)
            {
                return static_cast<float>(value);
            }

            /**
             * Cast a value to Uint8.
             *
             * \param value Value to cast.
             * \return Casted value.
             */
            Uint8 CUint8(auto value)
            {
                return static_cast<Uint8>(value);
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

            void Initialize(StringView gameWindowTitle, Color clearColor);

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
                Normal,
                HoveringClickableGUI,
                HoveringCreature
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

            CursorStyles m_cursorStyle{CursorStyles::Normal};
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

                    GLuint GetTexture(int imageNameHash) const;

                    Size GetImageSize(int imageNameHash) const;

                    bool TextTextureExists(float x, float y,
                                           int uniqueID) const;

                    GLuint ObtainTextTexture(float x, float y, int textHash);

                  private:
                    void Initialize();

                    void Cleanup();

                    void LoadImages();

                    GLuint LoadSingleTexture(SharedPtr<SDL_Surface> surface);

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
                        glm::vec2 uv;
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
                        Model(StringView filePath)
                        {
                            Initialize(filePath);
                        };

                        auto &GetMeshesRef() const
                        {
                            return m_meshes;
                        }

                      private:
                        void Initialize(StringView filePath);

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

                    SharedPtr<Model> GetModel(int modelNameHash) const;

                  private:
                    void Initialize();

                    SharedPtr<Model> LoadSingleModel(StringView filePath);

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
                void AddScene(StringView sceneName, IScene &scene);

                void GoToScene(StringView sceneName);

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

                void RegisterMouseButtonDown(Uint8 button);

                void RegisterMouseButtonUp(Uint8 button);

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

        void Initialize(StringView gameWindowTitle, Color clearColor) const;

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
        GUIComponent(float x, float y, float width, float height)
            : m_bounds({x, y, width, height})
        {
        }

        SharedPtr<GUIComponent>
        AddChildComponent(SharedPtr<GUIComponent> component);

        void Update();

        void Render() const;

        virtual RectF GetBounds() const;

        void SetPosition(PointF newPosition);

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
        GUILabel(float x, float y, float width, float height,
                 StringView text = "", bool centerAlign = false,
                 Color color = Colors::WheatTransparent)
            : GUIComponent(x, y, width, height), m_text(text),
              m_centerAlign(centerAlign), m_color(color)
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
        GUIPanel(float x, float y, float width, float height,
                 StringView backgroundImage = k_defaultBackgroundImage)
            : GUIComponent(x, y, width, height),
              m_backgroundImage(backgroundImage)
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
        GUIButton(float x, float y, float width, float height, StringView text,
                  Function<void()> action,
                  StringView backgroundImage = k_backgroundImage,
                  StringView hoveredBackgroundImage = k_hoveredBackgroundImage)
            : GUIPanel(x, y, width, height), m_text(text), m_action(action),
              m_backgroundImage(backgroundImage),
              m_hoveredBackgroundImage(hoveredBackgroundImage)
        {
        }

      protected:
        virtual void UpdateDerived() override;

        virtual void RenderDerived() const override;

      private:
        inline static const String k_backgroundImage{"gui_button_bg"};
        inline static const String k_hoveredBackgroundImage{
            "gui_button_hovered_bg"};

        String m_text;
        Function<void()> m_action;
        String m_backgroundImage;
        String m_hoveredBackgroundImage;
    };

    class GUIMovablePanel : public GUIPanel
    {
      public:
        GUIMovablePanel(float x, float y, float width, float height)
            : GUIPanel(x, y, width, height)
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
        GUIWindow(float x, float y, float width, float height,
                  StringView windowTitle)
            : GUIMovablePanel(x, y, width, height)
        {
            Initialize(windowTitle);
        }

      protected:
        void RenderDerived() const override;

        RectF GetDragArea() override;

        auto GetGUIWindowTitleBar() const
        {
            return m_guiWindowTitleBar;
        }

      private:
        void Initialize(StringView windowTitle);

        class GUIWindowTitleBar : public GUIPanel
        {
          public:
            GUIWindowTitleBar(GUIWindow &parentWindow, StringView windowTitle)
                : m_parentWindow(parentWindow), k_windowTitle(windowTitle),
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
        constexpr static StringView k_defaultBackgroundImageDerived{
            "gui_chat_box_bg"};
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
        ShaderProgram(StringView vertexShaderSource,
                      StringView fragmentShaderSource)
        {
            Initialize(vertexShaderSource, fragmentShaderSource);
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
        void Initialize(StringView vertexShaderSource,
                        StringView fragmentShaderSource);

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

        void DrawImage(StringView imageName, float x, float y, float width,
                       float height);

        void DrawImage(int imageNameHash, float x, float y, float width,
                       float height);

        void DrawTexture(GLuint textureID, float x, float y, float width,
                         float height, bool useOperationsMemory = false);

        void DrawImageAutoHeight(StringView imageName, float x, float y,
                                 float width);

      private:
        void Initialize();

        void Cleanup();

        class Image2DRenderingOperation
        {
          public:
            float x;
            float y;
            float width;
            float height;
            GLuint vao;
            GLuint ibo;
            GLuint vbo;
        };

        SharedPtr<ShaderProgram> m_shaderProgram;
        std::map<float,
                 std::map<float, std::map<GLuint, Image2DRenderingOperation>>>
            m_operationsMemory;
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

        void DrawTile(int imageNameHash, int xCoordinate, int yCoordinate,
                      float tileSize, Point3F cameraPosition,
                      Vector<float> &elevations, float elevationHeight);

        void DrawTexture(GLuint textureID, Vector<float> &vertices,
                         Point3F cameraPosition);

      private:
        void Initialize();

        void Cleanup();

        class GroundRenderingOperation
        {
          public:
            float x;
            float y;
            GLuint vao;
            GLuint ibo;
            GLuint vbo;
        };

        glm::vec3 ComputeNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

        SharedPtr<ShaderProgram> m_shaderProgram;
        std::map<float,
                 std::map<float, std::map<GLuint, GroundRenderingOperation>>>
            m_operationsMemory;
    };

    class ModelRenderer
    {
      public:
        ModelRenderer()
        {
            Initialize();
        }

        ~ModelRenderer()
        {
            Cleanup();
        }

        void DrawModel(int modelNameHash, float x, float y, float elevations,
                       Point3F cameraPosition, float elevationHeight);

      private:
        void Initialize();

        void Cleanup();

        class ModelRenderingOperation
        {
          public:
            float x;
            float y;
            float z;
            int verticesCount;
            GLuint vao;
            GLuint ibo;
            GLuint vbo;
        };

        SharedPtr<ShaderProgram> m_shaderProgram;
        std::map<
            float,
            std::map<float,
                     std::map<float, std::map<int, ModelRenderingOperation>>>>
            m_operationsMemory;
        static constexpr float k_modelScale{0.14f};
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
                        FontSizes fontSizes = FontSizes::_20,
                        bool centerAlign = false,
                        Color textColor = Colors::WheatTransparent) const;

      private:
        void Initialize();

        void AddFonts();

        const String k_defaultFontPath{"./res/fonts/PixeloidSans.ttf"};

        std::map<FontSizes, SharedPtr<TTF_Font>> m_fonts;
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
                None,
                OverallBody,
                RightArm,
                LeftArm,
                Legs
            };

            class BodyPart
            {
              public:
                auto GetStrength() const
                {
                    return m_strength;
                }
                auto GetCurrentEnergy() const
                {
                    return m_currentEnergy;
                }
                auto GetMaxEnergy() const
                {
                    return m_maxEnergy;
                }
                auto GetTemperature() const
                {
                    return m_temperature;
                }

              private:
                float m_strength{0.1f};
                float m_currentEnergy{1.0f};
                float m_maxEnergy{1.0f};
                float m_temperature{37.0f};
            };

            class PlayerBody
            {
              public:
                PlayerBody()
                {
                    Initialize();
                }

                BodyPart *GetBodyPartPtr(BodyPartTypes bodyPartType);

              private:
                void Initialize();

                std::map<BodyPartTypes, BodyPart> m_bodyParts;
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
                    return m_name;
                }

                auto GetPosition() const
                {
                    return m_position;
                }

                auto GetMovementSpeed() const
                {
                    return m_movementSpeed;
                }

                auto GetTicksLastMovement() const
                {
                    return m_ticksLastMovement;
                }

                void SetTicksLastMovement(int value)
                {
                    m_ticksLastMovement = value;
                }

                auto GetDestination() const
                {
                    return m_destination;
                }

                void SetDestination(Point value)
                {
                    m_destination = value;
                }

                auto &GetBodyRef()
                {
                    return m_body;
                }

                auto GetMoney() const
                {
                    return m_money;
                }

              private:
                void Initialize();

                void MoveToSuitablePosition();

                String m_name{"Unnamed Player"};
                Point m_position{60, 50};
                float m_movementSpeed{5.0f};
                int m_ticksLastMovement{0};
                Point m_destination{-1, -1};
                PlayerBody m_body;
                int m_money{0};
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
        return m_hoveredCoordinate;
    }

  private:
    Point m_hoveredCoordinate{-1, -1};
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
        None,
        N,
        E,
        S,
        W,
        NE,
        SE,
        SW,
        NW
    };

    class Creature
    {
      public:
        Creature(StringView type_name) : m_type{Hash(type_name)}
        {
            Initialize();
        }

        auto GetType() const
        {
            return m_type;
        }

        auto GetTicksLastMovement() const
        {
            return m_ticksLastMovement;
        }

        void SetTicksLastMovement(int value)
        {
            m_ticksLastMovement = value;
        }

        auto GetMovementSpeed() const
        {
            return m_movementSpeed;
        }

        auto GetDestination() const
        {
            return m_destination;
        }

        void SetDestination(Point value)
        {
            m_destination = value;
        }

      private:
        void Initialize();

        int m_type{0};
        int m_ticksLastMovement{0};
        float m_movementSpeed{2.0f};
        Point m_destination{-1, -1};
    };

    class NPC
    {
      public:
        NPC(StringView type_name) : m_type{Hash(type_name)}
        {
            Initialize();
        }

        auto GetType() const
        {
            return m_type;
        }

        auto GetName() const
        {
            return m_name;
        }

        auto GetTicksLastMovement() const
        {
            return m_ticksLastMovement;
        }

        void SetTicksLastMovement(int value)
        {
            m_ticksLastMovement = value;
        }

        auto GetMovementSpeed() const
        {
            return m_movementSpeed;
        }

        auto GetDestination() const
        {
            return m_destination;
        }

        void SetDestination(Point value)
        {
            m_destination = value;
        }

        auto GetTicksNextSpontaneousSpeech() const
        {
            return m_ticksNextSpontaneousSpeech;
        }

        void SetTicksNextSpontaneousSpeech(int value)
        {
            m_ticksNextSpontaneousSpeech = value;
        }

      private:
        void Initialize();

        void GenerateName();

        int m_type{0};
        String m_name;
        int m_ticksLastMovement{0};
        float m_movementSpeed{2.0f};
        Point m_destination{-1, -1};
        int m_ticksNextSpontaneousSpeech{0};
    };

    class Object
    {
      public:
        Object(StringView object_type_name) : m_type(Hash(object_type_name))
        {
        }

        auto GetType() const
        {
            return m_type;
        }

      private:
        int m_type{0};
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
            return m_trunkParts;
        }

        auto GetNeedleTypes() const
        {
            return m_needleTypes;
        }

        auto GetWidthFactor() const
        {
            return m_widthFactor;
        }

      private:
        void Initialize(StringView obj_type_name);

        Vector<PointF> m_trunkParts;
        Vector<int> m_needleTypes;
        float m_widthFactor{1.0f};
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
            return m_objects;
        }

      private:
        Vector<SharedPtr<Object>> m_objects;
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
            return m_ground;
        }

        void SetGround(StringView ground_name);

        auto GetObjectsStack() const
        {
            return m_objectsStack;
        }

        auto GetCreature() const
        {
            return m_creature;
        }

        void
        SetCreature(SharedPtr<Forradia::Theme0::WorldStructure::Creature> val)
        {
            m_creature = val;
        }

        auto GetNPC() const
        {
            return m_npc;
        }

        void SetNPC(SharedPtr<Forradia::Theme0::WorldStructure::NPC> value)
        {
            m_npc = value;
        }

        auto GetElevation() const
        {
            return m_elevation;
        }

        void SetElevation(int value)
        {
            m_elevation = value;
        }

        auto GetWaterDepth() const
        {
            return m_waterDepth;
        }

        void SetWaterDepth(int value)
        {
            m_waterDepth = value;
        }

        auto GetRiverDirection1() const
        {
            return m_riverDirection1;
        }

        void SetRiverDirection1(Directions value)
        {
            m_riverDirection1 = value;
        }

        auto GetRiverDirection2() const
        {
            return m_riverDirection2;
        }

        void SetRiverDirection2(Directions value)
        {
            m_riverDirection2 = value;
        }

      private:
        void Initialize();

        int m_ground{0};
        SharedPtr<Forradia::Theme0::WorldStructure::ObjectsStack>
            m_objectsStack;
        SharedPtr<Forradia::Theme0::WorldStructure::Creature> m_creature;
        SharedPtr<Forradia::Theme0::WorldStructure::NPC> m_npc;
        int m_elevation{0};
        int m_waterDepth{0};
        Directions m_riverDirection1{Directions::None};
        Directions m_riverDirection2{Directions::None};
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
            return m_creaturesMirror;
        }

        auto &GetNPCsMirrorRef()
        {
            return m_npcsMirror;
        }

      private:
        void Initialize(Size w_area_sz, float world_scaling);

        Vector<Vector<SharedPtr<Tile>>> m_tiles;
        std::map<SharedPtr<Creature>, Point> m_creaturesMirror;
        std::map<SharedPtr<NPC>, Point> m_npcsMirror;
    };

    class World
    {
      public:
        void Initialize(Size w_area_sz, float world_scaling);

        auto GetCurrentWorldArea() const
        {
            return m_currentWorldArea;
        }

      private:
        SharedPtr<WorldArea> m_currentWorldArea;
    };
}
using namespace WorldStructure;
#define _HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

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
        static constexpr String k_gameWindowTitle{"Forradia"};
        static constexpr Color k_clearColor{Colors::black};
        static constexpr int k_numGridRows{15};
        static constexpr Size k_worldAreaSize{120, 100};
        static constexpr float k_worldScaling{5.0f};
    };
}
using namespace Configuration;
#define _HIDE_FROM_OUTLINER_GAME_PROPS_BOTTOM_ }
_HIDE_FROM_OUTLINER_GAME_PROPS_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 
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
        static constexpr float k_slotSize{0.04f};
        inline static const String k_slotImageName{"gui_inventory_win_slot_bg"};
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

        int m_selectedBodyPart{0};
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> m_labelBodyPartName;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> m_labelBodyPartStrength;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel> m_labelBodyPartEnergy;
        SharedPtr<Core::GUIComponentsLibrary::GUILabel>
            m_labelBodyPartTemperature;
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
        static constexpr float k_indentWidth{0.01f};
        static constexpr float k_lineHeight{0.025f};

        class GUIInteractionMenuEntry
        {
          public:
            GUIInteractionMenuEntry(StringView label, Function<void()> action)
                : m_label(label), m_action(action)
            {
            }

            auto GetLabel() const
            {
                return m_label;
            }

            auto GetAction() const
            {
                return m_action;
            }

          private:
            String m_label;
            Function<void()> m_action;
        };

        Vector<GUIInteractionMenuEntry> m_entries;
    };
}
using namespace SpecializedGUI;
#define _HIDE_FROM_OUTLINER_GUI_SPEC_BOTTOM_ }
_HIDE_FROM_OUTLINER_GUI_SPEC_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 


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

        SharedPtr<Theme0::WorldStructure::WorldArea> m_worldArea;
        float m_scale;
        Size m_size;
    };
}
using namespace WorldGeneration;
#define _HIDE_FROM_OUTLINER_WORLD_GRATOR_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_GRATOR_BOTTOM_
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 

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
_NS_END_
// virtualIncludeEnd - DO NOT EDIT CONTENT ABOVE 









#define _HIDE_FROM_OUTLINER_ namespace Forradia {
_HIDE_FROM_OUTLINER_
}