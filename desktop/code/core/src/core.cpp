/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "core.hpp"

_NS_START_
namespace Core
{
    void Engine::init(StringView game_win_title, Color clear_color) const
    {
        randomize();

        _<SDLDevice>().init(game_win_title, clear_color);
    }

    void Engine::run()
    {
        try
        {
            while (running_)
            {
                _<Input::MouseInput>().reset();
                _<Cursor>().reset_style_to_normal();
                _<Renderers::img_2d_rend>().reset_counter();

                poll_events();

                _<ScenesCore::SceneManager>().update_curr_scene();
                _<FPSCounter>().update();

                _<SDLDevice>().clear_canv();
                _<ScenesCore::SceneManager>().render_curr_scene();
                _<Cursor>().render();
                _<SDLDevice>().present_canv();
            }
        }
        catch (std::exception &e)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", e.what(),
                                     nullptr);
        }
    }

    void Engine::stop()
    {
        running_ = false;
    }

    void Engine::poll_events()
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

                _<Input::KeyboardInput>().reg_key_press(ev.key.keysym.sym);

                break;

            case SDL_KEYUP:

                _<Input::KeyboardInput>().reg_key_release(ev.key.keysym.sym);

                break;

            case SDL_MOUSEBUTTONDOWN:

                _<Input::MouseInput>().reg_mouse_btn_down(ev.button.button);

                break;

            case SDL_MOUSEBUTTONUP:

                _<Input::MouseInput>().reg_mouse_btn_up(ev.button.button);

                break;
            }
        }
    }

    Engine::SDLDevice::~SDLDevice()
    {
        SDL_GL_DeleteContext(*context_);
    }

    void Engine::SDLDevice::init(StringView game_win_title, Color clear_color)
    {
        game_win_title_ = game_win_title;
        clear_color_ = clear_color;

        SDL_Init(SDL_INIT_EVERYTHING);

        win_ = create_win();

        context_ =
            std::make_shared<SDL_GLContext>(SDL_GL_CreateContext(win_.get()));

        SDL_GL_MakeCurrent(win_.get(), *context_);

        GLenum status = glewInit();

        if (GLEW_OK != status)
        {
            printf("GLEW Error: ", glewGetErrorString(status));
        }

        SDL_GL_SetSwapInterval(0);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
    }

    void Engine::SDLDevice::clear_canv() const
    {
        auto clear_color{clear_color_.to_sdl_color()};

        glClearColor(clear_color.r, clear_color.g, clear_color.b,
                     clear_color.a);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Engine::SDLDevice::present_canv() const
    {
        SDL_GL_SwapWindow(win_.get());
    }

    SharedPtr<SDL_Window> Engine::SDLDevice::create_win()
    {
        auto flags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                   SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN_DESKTOP |
                   SDL_WINDOW_OPENGL};

        auto screen_sz{get_screen_sz()};

        auto win_res{SharedPtr<SDL_Window>(
            SDL_CreateWindow(game_win_title_.data(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, screen_sz.w, screen_sz.h,
                             flags),
            SDLDeleter())};

        if (!win_res)
        {
            print_ln("Window could not be created. SDL Error: " +
                     String(SDL_GetError()));
        }

        return win_res;
    }

    Size Engine::SDLDevice::get_screen_sz() const
    {
        SDL_DisplayMode dm;

        SDL_GetCurrentDisplayMode(0, &dm);

        auto w = dm.w;
        auto h = dm.h;

        return {w, h};
    }

    void Engine::FPSCounter::update()
    {
        auto now{ticks()};

        if (now > ticks_last_update_ + k_one_sec_millis)
        {
            fps_ = frames_count_;
            frames_count_ = 0;
            ticks_last_update_ = now;
        }

        ++frames_count_;
    }

    void Engine::Cursor::init()
    {
        disable_sys_curs();
    }

    void Engine::Cursor::disable_sys_curs()
    {
        SDL_ShowCursor(SDL_DISABLE);
    }

    void Engine::Cursor::reset_style_to_normal()
    {
        curs_style_ = CursorStyles::normal;
    }

    void Engine::Cursor::render()
    {
        auto mouse_pos{norm_mouse_pos(_<Engine::SDLDevice>().win())};

        auto w{k_curs_sz};
        auto h{conv_w_to_h(k_curs_sz, _<Engine::SDLDevice>().win())};

        String curs_img;

        switch (curs_style_)
        {
        case CursorStyles::normal:

            curs_img = "curs_normal";

            break;

        case CursorStyles::hovering_clickable_gui:

            curs_img = "curs_hovering_clickable_gui";

            break;
        }

        _<Renderers::img_2d_rend>().draw_img(curs_img, mouse_pos.x - w / 2,
                                             mouse_pos.y - h / 2, w, h);
    }

    void Engine::Assets::Images::ImageBank::init()
    {
        load_imgs();
    }

    void Engine::Assets::Images::ImageBank::cleanup()
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

    void Engine::Assets::Images::ImageBank::load_imgs()
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
            auto file_path{repl(it.path().string(), '\\', '/')};

            if (file_ext(file_path) == "png")
            {
                auto file_name{file_name_no_ext(file_path)};

                auto hash{Forradia::hash(file_name)};

                auto surf{
                    SharedPtr<SDL_Surface>(IMG_Load(file_path.data()), SDLDeleter())};

                auto img_sz{Size{surf->w, surf->h}};

                tex_sizes_.insert({hash, img_sz});

                auto tex{load_single_tex(surf)};

                textures_.insert({hash, tex});
            }
        }
    }

    GLuint Engine::Assets::Images::ImageBank::get_tex(int img_name_hash) const
    {
        return textures_.at(img_name_hash);
    }

    Size Engine::Assets::Images::ImageBank::get_img_sz(int img_name_hash) const
    {
        if (tex_sizes_.contains(img_name_hash))
        {
            return tex_sizes_.at(img_name_hash);
        }

        return {-1, -1};
    }

    GLuint
    Engine::Assets::Images::ImageBank::load_single_tex(SharedPtr<SDL_Surface> surf)
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
    Engine::Assets::Images::ImageBank::text_tex_exists(float x, float y,
                                                        int text_hash) const
    {
        return text_texes_.contains(x) && text_texes_.at(x).contains(y) &&
               text_texes_.at(x).at(y).contains(text_hash);
    }

    GLuint Engine::Assets::Images::ImageBank::obtain_text_tex(float x, float y,
                                                               int text_hash)
    {
        if (text_tex_exists(x, y, text_hash))
        {
            return text_texes_.at(x).at(y).at(text_hash);
        }

        GLuint tex;

        glGenTextures(1, &tex);

        text_texes_[x][y][text_hash] = tex;

        return tex;
    }

    void Engine::Assets::Models::ModelBank::Model::init(StringView file_path)
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
            process_node(scene->mRootNode, scene, aiMatrix4x4());
        }
    }

    void Engine::Assets::Models::ModelBank::Model::process_node(
        aiNode *node, const aiScene *scene, aiMatrix4x4 transformation)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

            // Only apply transformation on meshes not entities such as lights
            // or camera.
            transformation *= node->mTransformation;

            meshes_.push_back(process_mesh(mesh, scene, transformation));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            process_node(node->mChildren[i], scene, transformation);
        }
    }

    Engine::Assets::Models::ModelBank::Mesh
    Engine::Assets::Models::ModelBank::Model::process_mesh(
        aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation)
    {
        glm::vec3 extents;
        glm::vec3 origin;

        Vector<Vertex> vertices =
            get_vertices(mesh, extents, origin, transformation);

        Vector<unsigned int> indices = get_indices(mesh);

        Vector<Texture> textures = get_textures(mesh, scene);

        return Engine::Assets::Models::ModelBank::Mesh(
            vertices, indices, textures, extents, origin, mesh->mName);
    }

    Vector<Engine::Assets::Models::ModelBank::Vertex>
    Engine::Assets::Models::ModelBank::Model::get_vertices(
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
    Engine::Assets::Models::ModelBank::Model::get_indices(aiMesh *mesh)
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
    Engine::Assets::Models::ModelBank::Model::get_textures(
        aiMesh *mesh, const aiScene *scene)
    {
        Vector<Texture> textures;

        aiString s;

        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(
            aiTextureType_DIFFUSE, 0, &s);

        textures.push_back(Texture(file_name_no_ext(s.C_Str())));

        return textures;
    }

    void Engine::Assets::Models::ModelBank::init()
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
            auto file_path{repl(it.path().string(), '\\', '/')};

            if (file_ext(file_path) == "obj")
            {
                auto file_name{file_name_no_ext(file_path)};

                auto hash{Forradia::hash(file_name)};

                auto model{load_single_model(file_path)};

                models_.insert({hash, model});
            }
        }
    }

    SharedPtr<Engine::Assets::Models::ModelBank::Model>
    Engine::Assets::Models::ModelBank::get_model(int model_name_hash) const
    {
        if (models_.contains(model_name_hash))
        {
            return models_.at(model_name_hash);
        }

        return nullptr;
    }

    SharedPtr<Engine::Assets::Models::ModelBank::Model>
    Engine::Assets::Models::ModelBank::load_single_model(StringView file_path)
    {
        auto model_res{std::make_shared<Model>(file_path)};

        return model_res;
    }

    void Engine::ScenesCore::IScene::init()
    {
        gui_ = std::make_shared<
            Engine::ScenesCore::IScene::ScenesGUI::GUIRoot>();

        init_derived_();
    }

    void Engine::ScenesCore::IScene::on_enter()
    {
        on_enter_derived_();
    }

    void Engine::ScenesCore::IScene::update()
    {
        gui_->update();

        update_derived_();
    }

    void Engine::ScenesCore::IScene::render() const
    {
        render_derived_();

        gui_->render();
    }

    void Engine::ScenesCore::SceneManager::add_scene(StringView scene_name,
                                                   IScene &scene)
    {
        scene.init();

        scenes_.insert({hash(scene_name), scene});
    }

    void Engine::ScenesCore::SceneManager::go_to_scene(StringView scene_name)
    {
        curr_scene_ = hash(scene_name);

        if (scenes_.contains(curr_scene_))
        {
            scenes_.at(curr_scene_).on_enter();
        }
    }

    void Engine::ScenesCore::SceneManager::update_curr_scene()
    {
        if (scenes_.contains(curr_scene_))
        {
            scenes_.at(curr_scene_).update();
        }
    }

    void Engine::ScenesCore::SceneManager::render_curr_scene() const
    {
        if (scenes_.contains(curr_scene_))
        {
            scenes_.at(curr_scene_).render();
        }
    }
    ////////////////////
    // Keyboard
    ////////////////////
    void Engine::Input::KeyboardInput::reset()
    {
        pressed_.clear();
    }

    void Engine::Input::KeyboardInput::reg_key_press(SDL_Keycode key)
    {
        pressed_.insert(key);
    }

    void Engine::Input::KeyboardInput::reg_key_release(SDL_Keycode key)
    {
        pressed_.erase(key);
    }

    bool Engine::Input::KeyboardInput::key_pressed(SDL_Keycode key) const
    {
        return pressed_.contains(key);
    }

    bool Engine::Input::KeyboardInput::key_pressed_pick_res(SDL_Keycode key)
    {
        auto res{pressed_.contains(key)};

        pressed_.erase(key);

        return res;
    }

    bool Engine::Input::KeyboardInput::any_key_pressed_pick_res()
    {
        auto res{pressed_.size() > 0};

        pressed_.clear();

        return res;
    }

    ////////////////////
    // Mouse
    ////////////////////
    void Engine::Input::MouseInput::MouseButton::reset()
    {
        pressed_ = false;
        been_fired_ = false;
        been_released_ = false;
    }

    void Engine::Input::MouseInput::MouseButton::reg_press()
    {
        pressed_ = true;
        been_fired_ = true;
    }

    void Engine::Input::MouseInput::MouseButton::reg_release()
    {
        pressed_ = false;
        been_released_ = true;
    }

    bool Engine::Input::MouseInput::MouseButton::pressed_pick_res()
    {
        auto res{pressed_};

        pressed_ = false;

        return res;
    }

    bool Engine::Input::MouseInput::MouseButton::been_fired_pick_res()
    {
        auto res{been_fired_};

        been_fired_ = false;

        return res;
    }

    bool Engine::Input::MouseInput::MouseButton::been_fired_no_pick_res()
    {
        return been_fired_;
    }

    bool Engine::Input::MouseInput::MouseButton::been_released_pick_res()
    {
        auto res{been_released_};

        been_released_ = false;

        return res;
    }

    bool Engine::Input::MouseInput::MouseButton::been_released_no_pick_res()
    {
        return been_released_;
    }

    void Engine::Input::MouseInput::reset()
    {
        _<LeftMouseButton>().reset();
        _<RightMouseButton>().reset();
    }

    void Engine::Input::MouseInput::reg_mouse_btn_down(Uint8 btn)
    {
        switch (btn)
        {
        case SDL_BUTTON_LEFT:

            _<LeftMouseButton>().reg_press();

            break;

        case SDL_BUTTON_RIGHT:

            _<RightMouseButton>().reg_press();

            break;
        }
    }

    void Engine::Input::MouseInput::reg_mouse_btn_up(Uint8 btn)
    {
        switch (btn)
        {
        case SDL_BUTTON_LEFT:

            _<LeftMouseButton>().reg_release();

            break;

        case SDL_BUTTON_RIGHT:

            _<RightMouseButton>().reg_release();

            break;
        }
    }

    bool Engine::Input::MouseInput::any_mouse_btn_pressed_pick_res()
    {
        auto res{_<LeftMouseButton>().pressed_pick_res()};

        res |= _<RightMouseButton>().pressed_pick_res();

        return res;
    }
}
_NS_END_