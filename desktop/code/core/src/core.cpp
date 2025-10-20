/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "core.hpp"

_NS_START_
namespace Core
{
    void engine::init(str_view game_win_title, color clear_color) const
    {
        randomize();

        _<sdl_device>().init(game_win_title, clear_color);
    }

    void engine::run()
    {
        try
        {
            while (running_)
            {
                _<Input::mouse_inp>().reset();
                _<cursor>().reset_style_to_normal();
                _<Renderers::img_2d_rend>().reset_counter();

                poll_events();

                _<ScenesCore::scene_mngr>().update_curr_scene();
                _<fps_counter>().update();

                _<sdl_device>().clear_canv();
                _<ScenesCore::scene_mngr>().render_curr_scene();
                _<cursor>().render();
                _<sdl_device>().present_canv();
            }
        }
        catch (std::exception &e)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", e.what(),
                                     nullptr);
        }
    }

    void engine::stop()
    {
        running_ = false;
    }

    void engine::poll_events()
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

                _<Input::kb_inp>().reg_key_press(ev.key.keysym.sym);

                break;

            case SDL_KEYUP:

                _<Input::kb_inp>().reg_key_release(ev.key.keysym.sym);

                break;

            case SDL_MOUSEBUTTONDOWN:

                _<Input::mouse_inp>().reg_mouse_btn_down(ev.button.button);

                break;

            case SDL_MOUSEBUTTONUP:

                _<Input::mouse_inp>().reg_mouse_btn_up(ev.button.button);

                break;
            }
        }
    }

    engine::sdl_device::~sdl_device()
    {
        SDL_GL_DeleteContext(*context_);
    }

    void engine::sdl_device::init(str_view game_win_title, color clear_color)
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

    void engine::sdl_device::clear_canv() const
    {
        auto clear_color{clear_color_.to_sdl_color()};

        glClearColor(clear_color.r, clear_color.g, clear_color.b,
                     clear_color.a);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void engine::sdl_device::present_canv() const
    {
        SDL_GL_SwapWindow(win_.get());
    }

    s_ptr<SDL_Window> engine::sdl_device::create_win()
    {
        auto flags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                   SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN_DESKTOP |
                   SDL_WINDOW_OPENGL};

        auto screen_sz{get_screen_sz()};

        auto win_res{s_ptr<SDL_Window>(
            SDL_CreateWindow(game_win_title_.data(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, screen_sz.w, screen_sz.h,
                             flags),
            sdl_del())};

        if (!win_res)
        {
            print_ln("Window could not be created. SDL Error: " +
                     str(SDL_GetError()));
        }

        return win_res;
    }

    sz engine::sdl_device::get_screen_sz() const
    {
        SDL_DisplayMode dm;

        SDL_GetCurrentDisplayMode(0, &dm);

        auto w = dm.w;
        auto h = dm.h;

        return {w, h};
    }

    void engine::fps_counter::update()
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

    void engine::cursor::init()
    {
        disable_sys_curs();
    }

    void engine::cursor::disable_sys_curs()
    {
        SDL_ShowCursor(SDL_DISABLE);
    }

    void engine::cursor::reset_style_to_normal()
    {
        curs_style_ = curs_styles::normal;
    }

    void engine::cursor::render()
    {
        auto mouse_pos{norm_mouse_pos(_<engine::sdl_device>().win())};

        auto w{k_curs_sz};
        auto h{conv_w_to_h(k_curs_sz, _<engine::sdl_device>().win())};

        str curs_img;

        switch (curs_style_)
        {
        case curs_styles::normal:

            curs_img = "curs_normal";

            break;

        case curs_styles::hovering_clickable_gui:

            curs_img = "curs_hovering_clickable_gui";

            break;
        }

        _<Renderers::img_2d_rend>().draw_img(curs_img, mouse_pos.x - w / 2,
                                             mouse_pos.y - h / 2, w, h);
    }

    void engine::Assets::Images::image_bank::init()
    {
        load_imgs();
    }

    void engine::Assets::Images::image_bank::cleanup()
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

    void engine::Assets::Images::image_bank::load_imgs()
    {
        auto base_path{str(SDL_GetBasePath())};
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
                    s_ptr<SDL_Surface>(IMG_Load(file_path.data()), sdl_del())};

                auto img_sz{sz{surf->w, surf->h}};

                tex_sizes_.insert({hash, img_sz});

                auto tex{load_single_tex(surf)};

                textures_.insert({hash, tex});
            }
        }
    }

    GLuint engine::Assets::Images::image_bank::get_tex(int img_name_hash) const
    {
        return textures_.at(img_name_hash);
    }

    sz engine::Assets::Images::image_bank::get_img_sz(int img_name_hash) const
    {
        if (tex_sizes_.contains(img_name_hash))
        {
            return tex_sizes_.at(img_name_hash);
        }

        return {-1, -1};
    }

    GLuint
    engine::Assets::Images::image_bank::load_single_tex(s_ptr<SDL_Surface> surf)
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
    engine::Assets::Images::image_bank::text_tex_exists(float x, float y,
                                                        int text_hash) const
    {
        return text_texes_.contains(x) && text_texes_.at(x).contains(y) &&
               text_texes_.at(x).at(y).contains(text_hash);
    }

    GLuint engine::Assets::Images::image_bank::obtain_text_tex(float x, float y,
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

    void engine::Assets::Models::model_bank::model::init(str_view file_path)
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

    void engine::Assets::Models::model_bank::model::process_node(
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

    engine::Assets::Models::model_bank::mesh
    engine::Assets::Models::model_bank::model::process_mesh(
        aiMesh *mesh, const aiScene *scene, aiMatrix4x4 transformation)
    {
        glm::vec3 extents;
        glm::vec3 origin;

        vec<vertex> vertices =
            get_vertices(mesh, extents, origin, transformation);

        vec<unsigned int> indices = get_indices(mesh);

        vec<texture> textures = get_textures(mesh, scene);

        return engine::Assets::Models::model_bank::mesh(
            vertices, indices, textures, extents, origin, mesh->mName);
    }

    vec<engine::Assets::Models::model_bank::vertex>
    engine::Assets::Models::model_bank::model::get_vertices(
        aiMesh *mesh, glm::vec3 &extents, glm::vec3 &origin,
        aiMatrix4x4 transformation)
    {
        vec<vertex> vertices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            engine::Assets::Models::model_bank::vertex vertex;

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

    vec<unsigned int>
    engine::Assets::Models::model_bank::model::get_indices(aiMesh *mesh)
    {
        vec<unsigned int> indices;

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

    vec<engine::Assets::Models::model_bank::texture>
    engine::Assets::Models::model_bank::model::get_textures(
        aiMesh *mesh, const aiScene *scene)
    {
        vec<texture> textures;

        aiString s;

        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(
            aiTextureType_DIFFUSE, 0, &s);

        textures.push_back(texture(file_name_no_ext(s.C_Str())));

        return textures;
    }

    void engine::Assets::Models::model_bank::init()
    {
        auto base_path{str(SDL_GetBasePath())};
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

    s_ptr<engine::Assets::Models::model_bank::model>
    engine::Assets::Models::model_bank::get_model(int model_name_hash) const
    {
        if (models_.contains(model_name_hash))
        {
            return models_.at(model_name_hash);
        }

        return nullptr;
    }

    s_ptr<engine::Assets::Models::model_bank::model>
    engine::Assets::Models::model_bank::load_single_model(str_view file_path)
    {
        auto model_res{std::make_shared<model>(file_path)};

        return model_res;
    }

    void engine::ScenesCore::i_scene::init()
    {
        gui_ = std::make_shared<
            engine::ScenesCore::i_scene::ScenesGUI::gui_root>();

        init_derived_();
    }

    void engine::ScenesCore::i_scene::on_enter()
    {
        on_enter_derived_();
    }

    void engine::ScenesCore::i_scene::update()
    {
        gui_->update();

        update_derived_();
    }

    void engine::ScenesCore::i_scene::render() const
    {
        render_derived_();

        gui_->render();
    }

    void engine::ScenesCore::scene_mngr::add_scene(str_view scene_name,
                                                   i_scene &scene)
    {
        scene.init();

        scenes_.insert({hash(scene_name), scene});
    }

    void engine::ScenesCore::scene_mngr::go_to_scene(str_view scene_name)
    {
        curr_scene_ = hash(scene_name);

        if (scenes_.contains(curr_scene_))
        {
            scenes_.at(curr_scene_).on_enter();
        }
    }

    void engine::ScenesCore::scene_mngr::update_curr_scene()
    {
        if (scenes_.contains(curr_scene_))
        {
            scenes_.at(curr_scene_).update();
        }
    }

    void engine::ScenesCore::scene_mngr::render_curr_scene() const
    {
        if (scenes_.contains(curr_scene_))
        {
            scenes_.at(curr_scene_).render();
        }
    }
    ////////////////////
    // Keyboard
    ////////////////////
    void engine::Input::kb_inp::reset()
    {
        pressed_.clear();
    }

    void engine::Input::kb_inp::reg_key_press(SDL_Keycode key)
    {
        pressed_.insert(key);
    }

    void engine::Input::kb_inp::reg_key_release(SDL_Keycode key)
    {
        pressed_.erase(key);
    }

    bool engine::Input::kb_inp::key_pressed(SDL_Keycode key) const
    {
        return pressed_.contains(key);
    }

    bool engine::Input::kb_inp::key_pressed_pick_res(SDL_Keycode key)
    {
        auto res{pressed_.contains(key)};

        pressed_.erase(key);

        return res;
    }

    bool engine::Input::kb_inp::any_key_pressed_pick_res()
    {
        auto res{pressed_.size() > 0};

        pressed_.clear();

        return res;
    }

    ////////////////////
    // Mouse
    ////////////////////
    void engine::Input::mouse_inp::mouse_btn::reset()
    {
        pressed_ = false;
        been_fired_ = false;
        been_released_ = false;
    }

    void engine::Input::mouse_inp::mouse_btn::reg_press()
    {
        pressed_ = true;
        been_fired_ = true;
    }

    void engine::Input::mouse_inp::mouse_btn::reg_release()
    {
        pressed_ = false;
        been_released_ = true;
    }

    bool engine::Input::mouse_inp::mouse_btn::pressed_pick_res()
    {
        auto res{pressed_};

        pressed_ = false;

        return res;
    }

    bool engine::Input::mouse_inp::mouse_btn::been_fired_pick_res()
    {
        auto res{been_fired_};

        been_fired_ = false;

        return res;
    }

    bool engine::Input::mouse_inp::mouse_btn::been_fired_no_pick_res()
    {
        return been_fired_;
    }

    bool engine::Input::mouse_inp::mouse_btn::been_released_pick_res()
    {
        auto res{been_released_};

        been_released_ = false;

        return res;
    }

    bool engine::Input::mouse_inp::mouse_btn::been_released_no_pick_res()
    {
        return been_released_;
    }

    void engine::Input::mouse_inp::reset()
    {
        _<left_mouse_btn>().reset();
        _<right_mouse_btn>().reset();
    }

    void engine::Input::mouse_inp::reg_mouse_btn_down(Uint8 btn)
    {
        switch (btn)
        {
        case SDL_BUTTON_LEFT:

            _<left_mouse_btn>().reg_press();

            break;

        case SDL_BUTTON_RIGHT:

            _<right_mouse_btn>().reg_press();

            break;
        }
    }

    void engine::Input::mouse_inp::reg_mouse_btn_up(Uint8 btn)
    {
        switch (btn)
        {
        case SDL_BUTTON_LEFT:

            _<left_mouse_btn>().reg_release();

            break;

        case SDL_BUTTON_RIGHT:

            _<right_mouse_btn>().reg_release();

            break;
        }
    }

    bool engine::Input::mouse_inp::any_mouse_btn_pressed_pick_res()
    {
        auto res{_<left_mouse_btn>().pressed_pick_res()};

        res |= _<right_mouse_btn>().pressed_pick_res();

        return res;
    }
}
_NS_END_