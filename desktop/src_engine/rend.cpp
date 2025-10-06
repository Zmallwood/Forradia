/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "rend.hpp"
#include "engine.hpp"

namespace forr {
  void img_rend::draw_img(str_view img_name, float x, float y, float w,
                          float h) const {
    draw_img(hash(img_name), x, y, w, h);
  }

  void img_rend::draw_img(int img_name_hash, float x, float y, float w,
                          float h) const {
    return;
    // glEnable(GL_TEXTURE_2D);
    // glEnable(GL_BLEND);                                // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending function
    glBindTexture(GL_TEXTURE_2D, _<image_bank>().get_tex(img_name_hash));
    glBegin(GL_TRIANGLE_FAN);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, 0.5f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x + w, y, 0.5f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x + w, y + h, 0.5f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y + h, 0.5f);

    glEnd();
    glFlush();
    return;
    auto img{_<image_bank>().get_img(img_name_hash)};
    auto canv_sz{get_canv_sz(_<sdl_device>().win())};
    auto x_px{c_int(x * canv_sz.w)};
    auto y_px{c_int(y * canv_sz.h)};
    auto w_px{c_int(w * canv_sz.w)};
    auto h_px{c_int(h * canv_sz.h)};
    SDL_Rect rect{x_px, y_px, w_px, h_px};
    SDL_RenderCopy(_<sdl_device>().rend().get(), img.get(), nullptr, &rect);
  }

  void img_rend::draw_img_auto_h(str_view img_name, float x, float y,
                                 float w) const {
    auto hash{forr::hash(img_name)};
    auto img_sz{_<image_bank>().get_img_sz(hash)};
    if (img_sz.w <= 0 || img_sz.h <= 0)
      return;
    auto canv_asp_rat{calc_aspect_ratio(_<sdl_device>().win())};
    auto img_asp_rat{c_float(img_sz.w) / img_sz.h};
    auto h{w / img_asp_rat * canv_asp_rat};
    draw_img(hash, x, y, w, h);
  }

  void img_2d_rend::init() {
    std::string vertex_shader_src = R"(
      #version 330 core
      layout (location = 0) in vec3 aPos;
      layout (location = 1) in vec3 aColor;
      layout (location = 2) in vec2 aTexCoord;

      out vec3 ourColor;
      out vec2 TexCoord;

      void main()
      {
          gl_Position = vec4(aPos, 1.0);
          gl_Position.x = gl_Position.x * 2.0 - 1.0;
          gl_Position.y = gl_Position.y * -2.0 + 1.0;
          ourColor = aColor;
          TexCoord = aTexCoord;
      }
    )";

    std::string fragment_shader_src = R"(
      #version 330 core
      out vec4 FragColor;
        
      in vec3 ourColor;
      in vec2 TexCoord;

      uniform sampler2D ourTexture;

      void main()
      {
          FragColor = texture(ourTexture, TexCoord);
      }
    )";

    // Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const GLchar *source = (const GLchar *)vertex_shader_src.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

      // We don't need the shader anymore.
      glDeleteShader(vertexShader);

      // Use the infoLog as you see fit.

      // In this simple program, we'll just leave
      return;
    }

    // Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar *)fragment_shader_src.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

      // We don't need the shader anymore.
      glDeleteShader(fragmentShader);
      // Either of them. Don't leak shaders.
      glDeleteShader(vertexShader);

      // Use the infoLog as you see fit.

      // In this simple program, we'll just leave
      return;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    program_ = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(program_, vertexShader);
    glAttachShader(program_, fragmentShader);

    // Link our program
    glLinkProgram(program_);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE) {
      GLint maxLength = 0;
      glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<GLchar> infoLog(maxLength);
      glGetProgramInfoLog(program_, maxLength, &maxLength, &infoLog[0]);

      // We don't need the program anymore.
      glDeleteProgram(program_);
      // Don't leak shaders either.
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);

      // Use the infoLog as you see fit.

      // In this simple program, we'll just leave
      return;
    }

    // Always detach shaders after a successful link.
    glDetachShader(program_, vertexShader);
    glDetachShader(program_, fragmentShader);
  }

  void img_2d_rend::cleanup() {

    for (auto &entry : imgs_) {
      for (auto &entry2 : entry.second) {
        glDeleteVertexArrays(1, &entry2.second.vao);
        glDeleteBuffers(1, &entry2.second.ibo);
        glDeleteBuffers(1, &entry2.second.vbo);
      }
    }

    // for (auto &entry1 : imgs_) {
    //   for (auto &entry2 : entry1.second) {
    //     for (auto &entry3 : entry2.second) {
    //       for (auto &entry4 : entry3.second) {
    //         glDeleteVertexArrays(1, &entry4.second.vao);
    //         glDeleteBuffers(1, &entry4.second.ibo);
    //         glDeleteBuffers(1, &entry4.second.vbo);
    //       }
    //     }
    //   }
    // }

    glUseProgram(0);
    glDeleteProgram(program_);
  }

  void img_2d_rend::reset_counter() { counter_ = 0; }

  void img_2d_rend::draw_img(int img_name_hash, float x, float y, float w,
                             float h) {
    auto tex_id{_<image_bank>().get_tex(img_name_hash)};

    img_2d_rend::draw_tex(tex_id, x, y, w, h);
  }

  void img_2d_rend::draw_tex(GLuint tex_id, float x, float y, float w,
                             float h) {

    // float vertices[] = {
    //// positions          // colors           // texture coords
    // 0.6f,  0.5f,  -0.9f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
    // 0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    //-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    //-0.5f, 0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    //};

    //    GLfloat vertices[] = {1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f,
    //                          -1.0f, 1.0f,  0.0f,  -1.0f, -1.0f, -1.0f, 0.0f,
    //                          0.0f,  -1.0f, 1.0f,  -1.0f, 0.0f,  1.0f};

    // auto hash_file{hash(loc.file_name())};
    glUseProgram(program_);
    glEnable(GL_BLEND);                                // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending
    float vertices[] = {
        x,     y,     0.0f, 1.0f, 1.0f, 1.0f, 0.0, 0.0, // top right
        x + w, y,     0.0f, 1.0f, 1.0f, 1.0f, 1.0, 0.0,
        x + w, y + h, 0.0f, 1.0f, 1.0f, 1.0f, 1.0, 1.0, // bottom right
        x,     y + h, 0.0f, 1.0f, 1.0f, 1.0f, 0.0, 1.0  // bottom left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 2, 3 // first triangle
    };
    auto count_vertices{4};

    // unsigned int indices[]{0, 1, 2, 0, 2, 3};

    auto indices_count{4};

    GLuint obj_vao;
    GLuint obj_ibo;
    GLuint obj_vbo;

    auto need_create_buffers{false};

    // if (imgs_.contains(x) && imgs_.at(x).contains(y) &&
    //     imgs_.at(x).at(y).contains(w) && imgs_.at(x).at(y).at(w).contains(h))
    //     {
    if (imgs_.contains(counter_) && imgs_.at(counter_).contains(tex_id)) {

      // auto &entry = imgs_.at(x).at(y).at(w).at(h);
      need_create_buffers = false;
    } else {
      need_create_buffers = true;
      glGenVertexArrays(1, &obj_vao);
      glGenBuffers(1, &obj_vbo);
      glGenBuffers(1, &obj_ibo);
    }

    auto need_fill_buffers{false};




    if (!need_create_buffers) {

      auto &entry = imgs_.at(counter_).at(tex_id);
      obj_vao = entry.vao;
      obj_ibo = entry.ibo;
      obj_vbo = entry.vbo;

      glBindVertexArray(obj_vao);
      glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
if (x != entry.x || y != entry.y || w != entry.w || h != entry.h) {

        need_fill_buffers = true;

        entry.x = x;
        entry.y = y;
        entry.w = w;
        entry.h = h;
      }
    } else {

      glBindVertexArray(obj_vao);
      glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);

      Entry entry;
      entry.vao = obj_vao;
      entry.ibo = obj_ibo;
      entry.vbo = obj_vbo;
      entry.x = x;
      entry.y = y;
      entry.w = w;
      entry.h = h;
      imgs_[counter_][tex_id] = entry;
      // imgs_[x][y][w][h] = entry;

      // std::cout << hash_file << ":" << loc.line()<< "\n";

      // std::cout << loc.file_name() << ":" << loc.line() << "\n";

      need_fill_buffers = true;
    }

    if (need_fill_buffers) {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(indices[0]) * indices_count, indices,
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 8 * count_vertices,
                     vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
                              0);
        // glColor3f(1.0f, 0.0f, 1.0f);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
                              (void *)(sizeof(vertices[0]) * 3));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
                              (void *)(sizeof(vertices[0]) * 6));
        glEnableVertexAttribArray(2);
    }

    // auto tex_id{_<image_bank>().get_tex(img_name_hash)};
    // glEnableClientState(GL_VERTEX_ARRAY);

    //      glGenVertexArrays(1, &obj_vao);
    //      glBindVertexArray(obj_vao);
    //
    //      glGenBuffers(1, &obj_ibo);
    //      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
    //      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) *
    //      indices_count,
    //                   indices, GL_STATIC_DRAW);
    //
    //      glGenBuffers(1, &obj_vbo);
    //      glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
    //      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) *
    //      count_vertices,
    //                   vertices, GL_STATIC_DRAW);
    //
    //      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    //      sizeof(vertices[0]) * 8,
    //                            0);
    //      glEnableVertexAttribArray(0);
    //
    //      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
    //      sizeof(vertices[0]) * 8,
    //                            (void *)(sizeof(vertices[0]) * 3));
    //      glEnableVertexAttribArray(1);
    //
    //      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
    //      sizeof(vertices[0]) * 8,
    //                            (void *)(sizeof(vertices[0]) * 5));
    //      glEnableVertexAttribArray(2);
    //
    //      glBindVertexArray(0);
    //      glBindBuffer(GL_ARRAY_BUFFER, 0);
    //      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //

    // auto tex_id{_<image_bank>().get_tex(img_name_hash)};
    //  glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(obj_vao);
    glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
    //    glFlush();

    //    ushort pindices[3];
    //    pindices[0] = 0;
    //    pindices[1] = 1;
    //    pindices[2] = 2;
    //
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort) * 3, pindices,
    //                 GL_STATIC_DRAW);
    //
    //    glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
    //    glEnableClientState(GL_VERTEX_ARRAY);
    //    glVertexPointer(3, GL_FLOAT, sizeof(vertices[0]),
    // 0); // The starting point of the VBO, for the vertices
    //    glEnableClientState(GL_NORMAL_ARRAY);
    //    glNormalPointer(
    //        GL_FLOAT, sizeof(vertices[0]),
    //        (void *)(sizeof(vertices[0]) *
    //                 3)); // The starting point of normals, 12 bytes away
    //    glClientActiveTexture(GL_TEXTURE0);
    //    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //    glTexCoordPointer(
    //        2, GL_FLOAT, sizeof(vertices[0]),
    //        (void *)(sizeof(vertices[0]) *
    //                 5)); // The starting point of texcoords, 24 bytes away
    //
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
    // To render, we can either use glDrawElements or glDrawRangeElements
    // The is the number of indices. 3 indices needed to make a single triangle
    //   glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)0);

    //    GLenum err;
    // while((err = glGetError()) != GL_NO_ERROR)
    //{
    // std::cout << "ERROR\n";
    //}
    ++counter_;
    return;

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void img_2d_rend::draw_img_auto_h(str_view img_name, float x, float y,
                                    float w) {
    auto hash{forr::hash(img_name)};
    auto img_sz{_<image_bank>().get_img_sz(hash)};
    if (img_sz.w <= 0 || img_sz.h <= 0)
      return;
    auto canv_asp_rat{calc_aspect_ratio(_<sdl_device>().win())};
    auto img_asp_rat{c_float(img_sz.w) / img_sz.h};
    auto h{w / img_asp_rat * canv_asp_rat};
    draw_img(hash, x, y, w, h);
  }

  void img_2d_rend::draw_img(str_view img_name, float x, float y, float w,
                             float h) {
    draw_img(hash(img_name), x, y, w, h);
  }

  void text_rend::init() {
    TTF_Init();
    add_fonts();
  }

  void text_rend::add_fonts() {
    auto abs_font_path{str(SDL_GetBasePath()) + k_default_font_path.data()};
    for (auto font_sz : {font_szs::_20, font_szs::_26}) {
      auto font_path_unix_style{repl(abs_font_path, '\\', '/')};
      auto font_sz_n{c_int(font_sz)};
      auto new_font{s_ptr<TTF_Font>(
          TTF_OpenFont(font_path_unix_style.c_str(), font_sz_n), sdl_del())};
      if (!new_font) {
        print_ln("Error loading font.");
        return;
      }
      fonts_.insert({font_sz, new_font});
    }
  }

  void text_rend::draw_str(str_view text, float x, float y, font_szs font_sz,
                           bool cent_align, color text_color) const {
    if (text.empty())
      return;
    auto font_raw{fonts_.at(font_sz).get()};

    sz text_dim;
    TTF_SizeText(font_raw, text.data(), &text_dim.w, &text_dim.h);
    SDL_Rect dest;
    auto canv_sz{get_canv_sz(_<sdl_device>().win())};
    dest.x = c_int(x * canv_sz.w);
    dest.y = c_int(y * canv_sz.h);
    dest.w = text_dim.w;
    dest.h = text_dim.h;
    if (cent_align) {
      dest.x -= dest.w / 2;
      dest.y -= dest.h / 2;
    }

    auto text_hash{hash(text)};
    auto xx{c_float(c_int(x * 1000))};
    auto yy{c_float(c_int(y * 1000))};

    auto tex_already_exists{_<image_bank>().text_tex_exists(xx, yy, text_hash)};
    auto tex{_<image_bank>().obtain_text_tex(xx, yy, text_hash)};
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);                                // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending function
    // if (!tex_already_exists) {
    glBindTexture(GL_TEXTURE_2D, tex);

    /* Load image file */

    /* Find out pixel format type */
    // glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    // if (!tex_already_exists) {
    if (tex_already_exists) {
    } else {
      auto sdl_color{text_color.to_sdl_color()};
      auto surf{TTF_RenderText_Solid(font_raw, text.data(), sdl_color)};

      // auto new_w{pow(2, std::ceil(log(surf->w) / log(2)))};
      // auto new_h{pow(2, std::ceil(log(surf->h) / log(2)))};

      auto new_w{surf->w};
      auto new_h{surf->h};
      auto intermediary = SDL_CreateRGBSurface(
          0, new_w, new_h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
      // auto intermediary = SDL_CreateRGBSurface(
      //     0, new_w, new_h, 32, 0xff000000, 0x00ff0000, 0x0000ff00,
      //     0x000000ff);

      SDL_BlitSurface(surf, 0, intermediary, 0);

      glTexImage2D(GL_TEXTURE_2D, 0, 4, intermediary->w, intermediary->h, 0,
                   GL_RGBA, GL_UNSIGNED_BYTE, intermediary->pixels);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      SDL_FreeSurface(intermediary);
      SDL_FreeSurface(surf);
    }
    //}
    auto xf{c_float(dest.x) / canv_sz.w};
    auto yf{c_float(dest.y) / canv_sz.h};
    auto wf{c_float(dest.w) / canv_sz.w};
    auto hf{c_float(dest.h) / canv_sz.h};
    _<img_2d_rend>().draw_tex(tex, xf, yf, wf, hf);
    return;
    // glBindTexture(GL_TEXTURE_2D, tex);
    // glBegin(GL_TRIANGLE_FAN);

    // auto xf{c_float(dest.x) / canv_sz.w};
    // auto yf{c_float(dest.y) / canv_sz.h};
    // auto wf{c_float(dest.w) / canv_sz.w};
    // auto hf{c_float(dest.h) / canv_sz.h};

    // glTexCoord2f(0.0f, 0.0f);
    // glVertex3f(xf, yf, 0.5f);

    // glTexCoord2f(1.0f, 0.0f);
    // glVertex3f(xf + wf, yf, 0.5f);

    // glTexCoord2f(1.0f, 1.0f);
    // glVertex3f(xf + wf, yf + hf, 0.5f);

    // glTexCoord2f(0.0f, 1.0f);
    // glVertex3f(xf, yf + hf, 0.5f);

    // glEnd();
    // glFlush();

    // auto rend{_<sdl_device>().rend().get()};
    // auto tex{SDL_CreateTextureFromSurface(rend, surf)};
    // SDL_RenderCopy(rend, tex, nullptr, &dest);
    // SDL_DestroyTexture(tex);
    // SDL_FreeSurface(intermediary);
  }
}