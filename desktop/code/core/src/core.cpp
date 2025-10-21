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
            while (running_)
            {
                _<Input::MouseInput>().Reset();
                _<Cursor>().ResetStyleToNormal();
                _<Renderers::Image2DRenderer>().reset_counter();

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
        running_ = false;
    }

    void Engine::PollEvents()
    {
        SDL_Event ev;

        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:

                running_ = false;

                break;

            case SDL_KEYDOWN:

                _<Input::KeyboardInput>().RegisterKeyPress(ev.key.keysym.sym);

                break;

            case SDL_KEYUP:

                _<Input::KeyboardInput>().RegisterKeyRelease(ev.key.keysym.sym);

                break;

            case SDL_MOUSEBUTTONDOWN:

                _<Input::MouseInput>().RegisterMouseButtonDown(ev.button.button);

                break;

            case SDL_MOUSEBUTTONUP:

                _<Input::MouseInput>().RegisterMouseButtonUp(ev.button.button);

                break;
            }
        }
    }

    Engine::SDLDevice::~SDLDevice()
    {
        SDL_GL_DeleteContext(*context_);
    }

    void Engine::SDLDevice::Initialize(StringView game_win_title, Color clear_color)
    {
        game_win_title_ = game_win_title;
        clear_color_ = clear_color;

        SDL_Init(SDL_INIT_EVERYTHING);

        window_ = CreateWindow();

        context_ =
            std::make_shared<SDL_GLContext>(SDL_GL_CreateContext(window_.get()));

        SDL_GL_MakeCurrent(window_.get(), *context_);

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
        auto clear_color{clear_color_.ToSDLColor()};

        glClearColor(clear_color.r, clear_color.g, clear_color.b,
                     clear_color.a);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Engine::SDLDevice::PresentCanvas() const
    {
        SDL_GL_SwapWindow(window_.get());
    }

    SharedPtr<SDL_Window> Engine::SDLDevice::CreateWindow()
    {
        auto flags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                   SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN_DESKTOP |
                   SDL_WINDOW_OPENGL};

        auto screen_sz{GetScreenSize()};

        auto win_res{SharedPtr<SDL_Window>(
            SDL_CreateWindow(game_win_title_.data(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, screen_sz.w, screen_sz.h,
                             flags),
            SDLDeleter())};

        if (!win_res)
        {
            PrintLine("Window could not be created. SDL Error: " +
                     String(SDL_GetError()));
        }

        return win_res;
    }

    Size Engine::SDLDevice::GetScreenSize() const
    {
        SDL_DisplayMode dm;

        SDL_GetCurrentDisplayMode(0, &dm);

        auto w = dm.w;
        auto h = dm.h;

        return {w, h};
    }

    void Engine::FPSCounter::Update()
    {
        auto now{GetTicks()};

        if (now > ticks_last_update_ + k_one_sec_millis)
        {
            fps_ = frames_count_;
            frames_count_ = 0;
            ticks_last_update_ = now;
        }

        ++frames_count_;
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
        cursor_style_ = CursorStyles::normal;
    }

    void Engine::Cursor::Render()
    {
        auto mouse_pos{GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

        auto w{k_curs_sz};
        auto h{ConvertWidthToHeight(k_curs_sz, _<Engine::SDLDevice>().GetWindow())};

        String curs_img;

        switch (cursor_style_)
        {
        case CursorStyles::normal:

            curs_img = "curs_normal";

            break;

        case CursorStyles::hovering_clickable_gui:

            curs_img = "curs_hovering_clickable_gui";

            break;
        }

        _<Renderers::Image2DRenderer>().draw_img(curs_img, mouse_pos.x - w / 2,
                                             mouse_pos.y - h / 2, w, h);
    }

    void Engine::Assets::Images::ImageBank::Initialize()
    {
        LoadImages();
    }

    void Engine::Assets::Images::ImageBank::Cleanup()
    {
        for (auto entry : textures_)
        {
            glDeleteTextures(1, &entry.second);
        }

        for (auto entry1 : text_texes_)
        {
            for (auto entry2 : entry1.second)
            {
                for (auto tex : entry2.second)
                {
                    glDeleteTextures(1, &tex.second);
                }
            }
        }
    }

    void Engine::Assets::Images::ImageBank::LoadImages()
    {
        auto base_path{String(SDL_GetBasePath())};
        auto imgs_path{base_path + k_rel_imgs_path.data()};

        if (!std::filesystem::exists(imgs_path))
        {
            return;
        }

        std::filesystem::recursive_directory_iterator rdi{imgs_path};

        for (auto it : rdi)
        {
            auto file_path{Replace(it.path().string(), '\\', '/')};

            if (GetFileExtension(file_path) == "png")
            {
                auto file_name{GetFileNameNoExtension(file_path)};

                auto hash{Forradia::Hash(file_name)};

                auto surf{
                    SharedPtr<SDL_Surface>(IMG_Load(file_path.data()), SDLDeleter())};

                auto img_sz{Size{surf->w, surf->h}};

                tex_sizes_.insert({hash, img_sz});

                auto tex{LoadSingleTexture(surf)};

                textures_.insert({hash, tex});
            }
        }
    }

    GLuint Engine::Assets::Images::ImageBank::GetTexture(int img_name_hash) const
    {
        return textures_.at(img_name_hash);
    }

    Size Engine::Assets::Images::ImageBank::GetImageSize(int img_name_hash) const
    {
        if (tex_sizes_.contains(img_name_hash))
        {
            return tex_sizes_.at(img_name_hash);
        }

        return {-1, -1};
    }

    GLuint
    Engine::Assets::Images::ImageBank::LoadSingleTexture(SharedPtr<SDL_Surface> surf)
    {
        GLuint tex;

        glGenTextures(1, &tex);

        glBindTexture(GL_TEXTURE_2D, tex);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, surf->pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return tex;
    }

    bool
    Engine::Assets::Images::ImageBank::TextTextureExists(float x, float y,
                                                        int text_hash) const
    {
        return text_texes_.contains(x) && text_texes_.at(x).contains(y) &&
               text_texes_.at(x).at(y).contains(text_hash);
    }

    GLuint Engine::Assets::Images::ImageBank::ObtainTextTexture(float x, float y,
                                                               int text_hash)
    {
        if (TextTextureExists(x, y, text_hash))
        {
            return text_texes_.at(x).at(y).at(text_hash);
        }

        GLuint tex;

        glGenTextures(1, &tex);

        text_texes_[x][y][text_hash] = tex;

        return tex;
    }

    void Engine::Assets::Models::ModelBank::Model::Initialize(StringView file_path)
    {
        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(
            file_path.data(), aiProcess_Triangulate | aiProcess_FlipUVs |
                                  aiProcess_CalcTangentSpace |
                                  aiProcess_GenBoundingBoxes |
                                  aiProcess_FixInfacingNormals);

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
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

            // Only apply transformation on meshes not entities such as lights
            // or camera.
            transformation *= node->mTransformation;

            meshes_.push_back(ProcessMesh(mesh, scene, transformation));
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

        Vector<Vertex> vertices =
            GetVertices(mesh, extents, origin, transformation);

        Vector<unsigned int> indices = GetIndices(mesh);

        Vector<Texture> textures = GetTextures(mesh, scene);

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

            aiVector3D v = transformation * mesh->mVertices[i];

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

        glm::vec3 min = glm::vec3(mesh->mAABB.mMin.x, mesh->mAABB.mMin.y,
                                  mesh->mAABB.mMin.z);

        glm::vec3 max = glm::vec3(mesh->mAABB.mMax.x, mesh->mAABB.mMax.y,
                                  mesh->mAABB.mMax.z);

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
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        return indices;
    }

    Vector<Engine::Assets::Models::ModelBank::Texture>
    Engine::Assets::Models::ModelBank::Model::GetTextures(
        aiMesh *mesh, const aiScene *scene)
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
        auto base_path{String(SDL_GetBasePath())};
        auto imgs_path{base_path + k_rel_models_path.data()};

        if (!std::filesystem::exists(imgs_path))
        {
            return;
        }

        std::filesystem::recursive_directory_iterator rdi{imgs_path};

        for (auto it : rdi)
        {
            auto file_path{Replace(it.path().string(), '\\', '/')};

            if (GetFileExtension(file_path) == "obj")
            {
                auto file_name{GetFileNameNoExtension(file_path)};

                auto hash{Forradia::Hash(file_name)};

                auto model{LoadSingleModel(file_path)};

                models_.insert({hash, model});
            }
        }
    }

    SharedPtr<Engine::Assets::Models::ModelBank::Model>
    Engine::Assets::Models::ModelBank::GetModel(int model_name_hash) const
    {
        if (models_.contains(model_name_hash))
        {
            return models_.at(model_name_hash);
        }

        return nullptr;
    }

    SharedPtr<Engine::Assets::Models::ModelBank::Model>
    Engine::Assets::Models::ModelBank::LoadSingleModel(StringView file_path)
    {
        auto model_res{std::make_shared<Model>(file_path)};

        return model_res;
    }

    void Engine::ScenesCore::IScene::Initialize()
    {
        gui_ = std::make_shared<
            Engine::ScenesCore::IScene::ScenesGUI::GUIRoot>();

        initialize_derived_();
    }

    void Engine::ScenesCore::IScene::OnEnter()
    {
        on_enter_derived_();
    }

    void Engine::ScenesCore::IScene::Update()
    {
        gui_->update();

        update_derived_();
    }

    void Engine::ScenesCore::IScene::Render() const
    {
        render_derived_();

        gui_->render();
    }

    void Engine::ScenesCore::SceneManager::AddScene(StringView scene_name,
                                                   IScene &scene)
    {
        scene.Initialize();

        scenes_.insert({Hash(scene_name), scene});
    }

    void Engine::ScenesCore::SceneManager::GoToScene(StringView scene_name)
    {
        curr_scene_ = Hash(scene_name);

        if (scenes_.contains(curr_scene_))
        {
            scenes_.at(curr_scene_).OnEnter();
        }
    }

    void Engine::ScenesCore::SceneManager::UpdateCurrentScene()
    {
        if (scenes_.contains(curr_scene_))
        {
            scenes_.at(curr_scene_).Update();
        }
    }

    void Engine::ScenesCore::SceneManager::RenderCurrentScene() const
    {
        if (scenes_.contains(curr_scene_))
        {
            scenes_.at(curr_scene_).Render();
        }
    }
    
    void Engine::Input::KeyboardInput::Reset()
    {
        pressed_.clear();
    }

    void Engine::Input::KeyboardInput::RegisterKeyPress(SDL_Keycode key)
    {
        pressed_.insert(key);
    }

    void Engine::Input::KeyboardInput::RegisterKeyRelease(SDL_Keycode key)
    {
        pressed_.erase(key);
    }

    bool Engine::Input::KeyboardInput::KeyIsPressed(SDL_Keycode key) const
    {
        return pressed_.contains(key);
    }

    bool Engine::Input::KeyboardInput::KeyIsPressedPickResult(SDL_Keycode key)
    {
        auto res{pressed_.contains(key)};

        pressed_.erase(key);

        return res;
    }

    bool Engine::Input::KeyboardInput::AnyKeyIsPressedPickResult()
    {
        auto res{pressed_.size() > 0};

        pressed_.clear();

        return res;
    }

    void Engine::Input::MouseInput::MouseButton::Reset()
    {
        pressed_ = false;
        been_fired_ = false;
        been_released_ = false;
    }

    void Engine::Input::MouseInput::MouseButton::RegisterPress()
    {
        pressed_ = true;
        been_fired_ = true;
    }

    void Engine::Input::MouseInput::MouseButton::RegisterRelease()
    {
        pressed_ = false;
        been_released_ = true;
    }

    bool Engine::Input::MouseInput::MouseButton::IsPressedPickResult()
    {
        auto res{pressed_};

        pressed_ = false;

        return res;
    }

    bool Engine::Input::MouseInput::MouseButton::HasBeenFiredPickResult()
    {
        auto res{been_fired_};

        been_fired_ = false;

        return res;
    }

    bool Engine::Input::MouseInput::MouseButton::HasBeenFired()
    {
        return been_fired_;
    }

    bool Engine::Input::MouseInput::MouseButton::HasBeenReleasedPickResult()
    {
        auto res{been_released_};

        been_released_ = false;

        return res;
    }

    bool Engine::Input::MouseInput::MouseButton::HasBeenReleased()
    {
        return been_released_;
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
        auto res{_<LeftMouseButton>().IsPressedPickResult()};

        res |= _<RightMouseButton>().IsPressedPickResult();

        return res;
    }
}
_NS_END_