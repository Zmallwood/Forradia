/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "core.hpp"

_NS_START_
namespace Core
{
    void Engine::Initialize(StringView game_win_title, Color clear_color) const
    {
        Randomize();

        _<SDLDevice>().Initialize(game_win_title, clear_color);
    }

    void Engine::Run()
    {
        try
        {
            while (m_running)
            {
                _<Input::MouseInput>().Reset();
                _<Cursor>().ResetStyleToNormal();

                PollEvents();

                _<ScenesCore::SceneManager>().UpdateCurrentScene();
                _<FPSCounter>().Update();

                _<SDLDevice>().ClearCanvas();
                _<ScenesCore::SceneManager>().RenderCurrentScene();
                _<Cursor>().Render();
                _<SDLDevice>().PresentCanvas();
            }
        }
        catch (std::exception &e)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", e.what(),
                                     nullptr);
        }
    }

    void Engine::Stop()
    {
        m_running = false;
    }

    void Engine::PollEvents()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:

                m_running = false;

                break;

            case SDL_KEYDOWN:

                _<Input::KeyboardInput>().RegisterKeyPress(
                    event.key.keysym.sym);

                break;

            case SDL_KEYUP:

                _<Input::KeyboardInput>().RegisterKeyRelease(
                    event.key.keysym.sym);

                break;

            case SDL_MOUSEBUTTONDOWN:

                _<Input::MouseInput>().RegisterMouseButtonDown(
                    event.button.button);

                break;

            case SDL_MOUSEBUTTONUP:

                _<Input::MouseInput>().RegisterMouseButtonUp(
                    event.button.button);

                break;
            }
        }
    }

    Engine::SDLDevice::~SDLDevice()
    {
        SDL_GL_DeleteContext(*m_context);
    }

    void Engine::SDLDevice::Initialize(StringView game_win_title,
                                       Color clear_color)
    {
        m_gameWindowTitle = game_win_title;
        m_clearColor = clear_color;

        SDL_Init(SDL_INIT_EVERYTHING);

        m_window = CreateWindow();

        m_context = std::make_shared<SDL_GLContext>(
            SDL_GL_CreateContext(m_window.get()));

        SDL_GL_MakeCurrent(m_window.get(), *m_context);

        GLenum status = glewInit();

        if (GLEW_OK != status)
        {
            printf("GLEW Error: ", glewGetErrorString(status));
        }

        SDL_GL_SetSwapInterval(0);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
    }

    void Engine::SDLDevice::ClearCanvas() const
    {
        auto clearColor{m_clearColor.ToSDLColor()};

        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Engine::SDLDevice::PresentCanvas() const
    {
        SDL_GL_SwapWindow(m_window.get());
    }

    SharedPtr<SDL_Window> Engine::SDLDevice::CreateWindow()
    {
        auto flags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                   SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN_DESKTOP |
                   SDL_WINDOW_OPENGL};

        auto screenSize{GetScreenSize()};

        auto windowResult{SharedPtr<SDL_Window>(
            SDL_CreateWindow(m_gameWindowTitle.data(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, screenSize.width,
                             screenSize.height, flags),
            SDLDeleter())};

        if (!windowResult)
        {
            PrintLine("Window could not be created. SDL Error: " +
                      String(SDL_GetError()));
        }

        return windowResult;
    }

    Size Engine::SDLDevice::GetScreenSize() const
    {
        SDL_DisplayMode displayMode;

        SDL_GetCurrentDisplayMode(0, &displayMode);

        auto width{displayMode.w};
        auto height{displayMode.h};

        return {width, height};
    }

    void Engine::FPSCounter::Update()
    {
        auto now{GetTicks()};

        if (now > m_ticksLastUpdate + k_oneSecMillis)
        {
            m_fps = m_framesCount;
            m_framesCount = 0;
            m_ticksLastUpdate = now;
        }

        ++m_framesCount;
    }

    void Engine::Cursor::Initialize()
    {
        DisableSystemCursor();
    }

    void Engine::Cursor::DisableSystemCursor()
    {
        SDL_ShowCursor(SDL_DISABLE);
    }

    void Engine::Cursor::ResetStyleToNormal()
    {
        m_cursorStyle = CursorStyles::Normal;
    }

    void Engine::Cursor::Render()
    {
        auto mousePosition{
            GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

        auto width{k_cursorSize};
        auto height{ConvertWidthToHeight(k_cursorSize,
                                         _<Engine::SDLDevice>().GetWindow())};

        String cursorImage;

        switch (m_cursorStyle)
        {
        case CursorStyles::Normal:

            cursorImage = "curs_normal";

            break;

        case CursorStyles::HoveringClickableGUI:

            cursorImage = "curs_hovering_clickable_gui";

            break;
        }

        _<Renderers::Image2DRenderer>().DrawImage(
            cursorImage, mousePosition.x - width / 2,
            mousePosition.y - height / 2, width, height);
    }

    void Engine::Assets::Images::ImageBank::Initialize()
    {
        LoadImages();
    }

    void Engine::Assets::Images::ImageBank::Cleanup()
    {
        for (auto entry : m_textures)
        {
            glDeleteTextures(1, &entry.second);
        }

        for (auto entry1 : m_textTextures)
        {
            for (auto entry2 : entry1.second)
            {
                for (auto texture : entry2.second)
                {
                    glDeleteTextures(1, &texture.second);
                }
            }
        }
    }

    void Engine::Assets::Images::ImageBank::LoadImages()
    {
        auto basePath{String(SDL_GetBasePath())};
        auto imagesPath{basePath + k_relativeImagesPath.data()};

        if (!std::filesystem::exists(imagesPath))
        {
            return;
        }

        std::filesystem::recursive_directory_iterator rdi{imagesPath};

        for (auto it : rdi)
        {
            auto filePath{Replace(it.path().string(), '\\', '/')};

            if (GetFileExtension(filePath) == "png")
            {
                auto fileName{GetFileNameNoExtension(filePath)};

                auto hash{Forradia::Hash(fileName)};

                auto surface{SharedPtr<SDL_Surface>(IMG_Load(filePath.data()),
                                                    SDLDeleter())};

                auto imageSize{Size{surface->w, surface->h}};

                m_textureSizes.insert({hash, imageSize});

                auto texture{LoadSingleTexture(surface)};

                m_textures.insert({hash, texture});
            }
        }
    }

    GLuint
    Engine::Assets::Images::ImageBank::GetTexture(int img_name_hash) const
    {
        return m_textures.at(img_name_hash);
    }

    Size
    Engine::Assets::Images::ImageBank::GetImageSize(int img_name_hash) const
    {
        if (m_textureSizes.contains(img_name_hash))
        {
            return m_textureSizes.at(img_name_hash);
        }

        return {-1, -1};
    }

    GLuint Engine::Assets::Images::ImageBank::LoadSingleTexture(
        SharedPtr<SDL_Surface> surf)
    {
        GLuint texture;

        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, surf->pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return texture;
    }

    bool
    Engine::Assets::Images::ImageBank::TextTextureExists(float x, float y,
                                                         int text_hash) const
    {
        return m_textTextures.contains(x) && m_textTextures.at(x).contains(y) &&
               m_textTextures.at(x).at(y).contains(text_hash);
    }

    GLuint Engine::Assets::Images::ImageBank::ObtainTextTexture(float x,
                                                                float y,
                                                                int text_hash)
    {
        if (TextTextureExists(x, y, text_hash))
        {
            return m_textTextures.at(x).at(y).at(text_hash);
        }

        GLuint texture;

        glGenTextures(1, &texture);

        m_textTextures[x][y][text_hash] = texture;

        return texture;
    }

    void
    Engine::Assets::Models::ModelBank::Model::Initialize(StringView file_path)
    {
        Assimp::Importer importer;

        const aiScene *scene{importer.ReadFile(
            file_path.data(), aiProcess_Triangulate | aiProcess_FlipUVs |
                                  aiProcess_CalcTangentSpace |
                                  aiProcess_GenBoundingBoxes |
                                  aiProcess_FixInfacingNormals)};

        if (!scene || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP Could not load model: "
                      << importer.GetErrorString() << std::endl;
        }
        else
        {
            ProcessNode(scene->mRootNode, scene, aiMatrix4x4());
        }
    }

    void Engine::Assets::Models::ModelBank::Model::ProcessNode(
        aiNode *node, const aiScene *scene, aiMatrix4x4 transformation)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh{scene->mMeshes[node->mMeshes[i]]};

            // Only apply transformation on meshes not entities such as lights
            // or camera.
            transformation *= node->mTransformation;

            m_meshes.push_back(ProcessMesh(mesh, scene, transformation));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene, transformation);
        }
    }

    Engine::Assets::Models::ModelBank::Mesh
    Engine::Assets::Models::ModelBank::Model::ProcessMesh(
        aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation)
    {
        glm::vec3 extents;
        glm::vec3 origin;

        Vector<Vertex> vertices{
            GetVertices(mesh, extents, origin, transformation)};

        Vector<unsigned int> indices{GetIndices(mesh)};

        Vector<Texture> textures{GetTextures(mesh, scene)};

        return Engine::Assets::Models::ModelBank::Mesh(
            vertices, indices, textures, extents, origin, mesh->mName);
    }

    Vector<Engine::Assets::Models::ModelBank::Vertex>
    Engine::Assets::Models::ModelBank::Model::GetVertices(
        aiMesh *mesh, glm::vec3 &extents, glm::vec3 &origin,
        aiMatrix4x4 transformation)
    {
        Vector<Vertex> vertices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Engine::Assets::Models::ModelBank::Vertex vertex;

            glm::vec3 vector3;

            aiVector3D v{transformation * mesh->mVertices[i]};

            // Vertices.
            vector3.x = v.x;
            vector3.y = v.y;
            vector3.z = v.z;

            vertex.position = vector3;

            // Normals.
            if (mesh->mNormals)
            {
                vector3.x = mesh->mNormals[i].x;
                vector3.y = mesh->mNormals[i].y;
                vector3.z = mesh->mNormals[i].z;

                vertex.normal = vector3;
            }

            // Texture coordinates.
            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vector2;

                vector2.x = mesh->mTextureCoords[0][i].x;
                vector2.y = mesh->mTextureCoords[0][i].y;

                vertex.tex_coord = vector2;
            }
            else
            {
                vertex.tex_coord = glm::vec2(0, 0);
            }
            if (mesh->mTangents)
            {
                vector3.x = mesh->mTangents[i].x;
                vector3.y = mesh->mTangents[i].y;
                vector3.z = mesh->mTangents[i].z;

                vertex.tangent = vector3;
            }
            // Bitangent.
            if (mesh->mBitangents)
            {
                vector3.x = mesh->mBitangents[i].x;
                vector3.y = mesh->mBitangents[i].y;
                vector3.z = mesh->mBitangents[i].z;

                vertex.bitangent = vector3;
            }

            vertices.push_back(vertex);
        }

        glm::vec3 min{glm::vec3(mesh->mAABB.mMin.x, mesh->mAABB.mMin.y,
                                mesh->mAABB.mMin.z)};

        glm::vec3 max{glm::vec3(mesh->mAABB.mMax.x, mesh->mAABB.mMax.y,
                                mesh->mAABB.mMax.z)};

        extents = (max - min) * 0.5f;

        origin = glm::vec3((min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f,
                           (min.z + max.z) / 2.0f);
        return vertices;
    }

    Vector<unsigned int>
    Engine::Assets::Models::ModelBank::Model::GetIndices(aiMesh *mesh)
    {
        Vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face{mesh->mFaces[i]};

            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        return indices;
    }

    Vector<Engine::Assets::Models::ModelBank::Texture>
    Engine::Assets::Models::ModelBank::Model::GetTextures(aiMesh *mesh,
                                                          const aiScene *scene)
    {
        Vector<Texture> textures;

        aiString s;

        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(
            aiTextureType_DIFFUSE, 0, &s);

        textures.push_back(Texture(GetFileNameNoExtension(s.C_Str())));

        return textures;
    }

    void Engine::Assets::Models::ModelBank::Initialize()
    {
        auto basePath{String(SDL_GetBasePath())};
        auto imagesPath{basePath + k_relativeModelsPath.data()};

        if (!std::filesystem::exists(imagesPath))
        {
            return;
        }

        std::filesystem::recursive_directory_iterator rdi{imagesPath};

        for (auto it : rdi)
        {
            auto filePath{Replace(it.path().string(), '\\', '/')};

            if (GetFileExtension(filePath) == "obj")
            {
                auto fileName{GetFileNameNoExtension(filePath)};

                auto hash{Forradia::Hash(fileName)};

                auto model{LoadSingleModel(filePath)};

                m_models.insert({hash, model});
            }
        }
    }

    SharedPtr<Engine::Assets::Models::ModelBank::Model>
    Engine::Assets::Models::ModelBank::GetModel(int model_name_hash) const
    {
        if (m_models.contains(model_name_hash))
        {
            return m_models.at(model_name_hash);
        }

        return nullptr;
    }

    SharedPtr<Engine::Assets::Models::ModelBank::Model>
    Engine::Assets::Models::ModelBank::LoadSingleModel(StringView file_path)
    {
        auto modelResult{std::make_shared<Model>(file_path)};

        return modelResult;
    }

    void Engine::ScenesCore::IScene::Initialize()
    {
        m_gui =
            std::make_shared<Engine::ScenesCore::IScene::ScenesGUI::GUIRoot>();

        m_initializeDerived();
    }

    void Engine::ScenesCore::IScene::OnEnter()
    {
        m_onEnterDerived();
    }

    void Engine::ScenesCore::IScene::Update()
    {
        m_gui->Update();

        m_updateDerived();
    }

    void Engine::ScenesCore::IScene::Render() const
    {
        m_renderDerived();

        m_gui->Render();
    }

    void Engine::ScenesCore::SceneManager::AddScene(StringView scene_name,
                                                    IScene &scene)
    {
        scene.Initialize();

        m_scenes.insert({Hash(scene_name), scene});
    }

    void Engine::ScenesCore::SceneManager::GoToScene(StringView scene_name)
    {
        m_currentScene = Hash(scene_name);

        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).OnEnter();
        }
    }

    void Engine::ScenesCore::SceneManager::UpdateCurrentScene()
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).Update();
        }
    }

    void Engine::ScenesCore::SceneManager::RenderCurrentScene() const
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene).Render();
        }
    }

    void Engine::Input::KeyboardInput::Reset()
    {
        m_pressed.clear();
    }

    void Engine::Input::KeyboardInput::RegisterKeyPress(SDL_Keycode key)
    {
        m_pressed.insert(key);
    }

    void Engine::Input::KeyboardInput::RegisterKeyRelease(SDL_Keycode key)
    {
        m_pressed.erase(key);
    }

    bool Engine::Input::KeyboardInput::KeyIsPressed(SDL_Keycode key) const
    {
        return m_pressed.contains(key);
    }

    bool Engine::Input::KeyboardInput::KeyIsPressedPickResult(SDL_Keycode key)
    {
        auto result{m_pressed.contains(key)};

        m_pressed.erase(key);

        return result;
    }

    bool Engine::Input::KeyboardInput::AnyKeyIsPressedPickResult()
    {
        auto result{m_pressed.size() > 0};

        m_pressed.clear();

        return result;
    }

    void Engine::Input::MouseInput::MouseButton::Reset()
    {
        m_pressed = false;
        m_hasBeenFired = false;
        m_hasBeenReleased = false;
    }

    void Engine::Input::MouseInput::MouseButton::RegisterPress()
    {
        m_pressed = true;
        m_hasBeenFired = true;
    }

    void Engine::Input::MouseInput::MouseButton::RegisterRelease()
    {
        m_pressed = false;
        m_hasBeenReleased = true;
    }

    bool Engine::Input::MouseInput::MouseButton::IsPressedPickResult()
    {
        auto result{m_pressed};

        m_pressed = false;

        return result;
    }

    bool Engine::Input::MouseInput::MouseButton::HasBeenFiredPickResult()
    {
        auto result{m_hasBeenFired};

        m_hasBeenFired = false;

        return result;
    }

    bool Engine::Input::MouseInput::MouseButton::HasBeenFired()
    {
        return m_hasBeenFired;
    }

    bool Engine::Input::MouseInput::MouseButton::HasBeenReleasedPickResult()
    {
        auto result{m_hasBeenReleased};

        m_hasBeenReleased = false;

        return result;
    }

    bool Engine::Input::MouseInput::MouseButton::HasBeenReleased()
    {
        return m_hasBeenReleased;
    }

    void Engine::Input::MouseInput::Reset()
    {
        _<LeftMouseButton>().Reset();
        _<RightMouseButton>().Reset();
    }

    void Engine::Input::MouseInput::RegisterMouseButtonDown(Uint8 btn)
    {
        switch (btn)
        {
        case SDL_BUTTON_LEFT:

            _<LeftMouseButton>().RegisterPress();

            break;

        case SDL_BUTTON_RIGHT:

            _<RightMouseButton>().RegisterPress();

            break;
        }
    }

    void Engine::Input::MouseInput::RegisterMouseButtonUp(Uint8 btn)
    {
        switch (btn)
        {
        case SDL_BUTTON_LEFT:

            _<LeftMouseButton>().RegisterRelease();

            break;

        case SDL_BUTTON_RIGHT:

            _<RightMouseButton>().RegisterRelease();

            break;
        }
    }

    bool Engine::Input::MouseInput::AnyMouseButtonIsPressedPickResult()
    {
        auto result{_<LeftMouseButton>().IsPressedPickResult()};

        result |= _<RightMouseButton>().IsPressedPickResult();

        return result;
    }
}
_NS_END_