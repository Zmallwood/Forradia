/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "rend.hpp"
#include "core.hpp"
#include "models.hpp"
#include <glm/gtx/transform.hpp>

_NS_START_
void img_rend::draw_img(str_view img_name, float x, float y, float w,
                        float h) const {
  // draw_img(hash(img_name), x, y, w, h);
}

void img_rend::draw_img(int img_name_hash, float x, float y, float w,
                        float h) const {
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending
  // function glBindTexture(GL_TEXTURE_2D,
  // _<image_bank>().get_tex(img_name_hash)); glBegin(GL_TRIANGLE_FAN);

  // glTexCoord2f(0.0f, 0.0f);
  // glVertex3f(x, y, 0.5f);

  // glTexCoord2f(1.0f, 0.0f);
  // glVertex3f(x + w, y, 0.5f);

  // glTexCoord2f(1.0f, 1.0f);
  // glVertex3f(x + w, y + h, 0.5f);

  // glTexCoord2f(0.0f, 1.0f);
  // glVertex3f(x, y + h, 0.5f);

  // glEnd();
  // glFlush();
  // return;
  // auto img{_<image_bank>().get_img(img_name_hash)};
  // auto canv_sz{get_canv_sz(_<sdl_device>().win())};
  // auto x_px{c_int(x * canv_sz.w)};
  // auto y_px{c_int(y * canv_sz.h)};
  // auto w_px{c_int(w * canv_sz.w)};
  // auto h_px{c_int(h * canv_sz.h)};
  // SDL_Rect rect{x_px, y_px, w_px, h_px};
  // SDL_RenderCopy(_<sdl_device>().rend().get(), img.get(), nullptr, &rect);
}

void img_rend::draw_img_auto_h(str_view img_name, float x, float y,
                               float w) const {
  // auto hash{forr::hash(img_name)};
  // auto img_sz{_<image_bank>().get_img_sz(hash)};
  // if (img_sz.w <= 0 || img_sz.h <= 0)
  //   return;
  // auto canv_asp_rat{calc_aspect_ratio(_<sdl_device>().win())};
  // auto img_asp_rat{c_float(img_sz.w) / img_sz.h};
  // auto h{w / img_asp_rat * canv_asp_rat};
  // draw_img(hash, x, y, w, h);
}

void shader_program::init(str_view vert_src, str_view frag_src) {
  GLuint vertex_shader{glCreateShader(GL_VERTEX_SHADER)};
  const GLchar *source{(const GLchar *)vert_src.data()};
  glShaderSource(vertex_shader, 1, &source, 0);
  glCompileShader(vertex_shader);
  GLint is_compiled{0};
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint max_length{0};
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);
    std::vector<GLchar> infoLog(max_length);
    glGetShaderInfoLog(vertex_shader, max_length, &max_length, &infoLog[0]);
    glDeleteShader(vertex_shader);
    return;
  }
  GLuint fragment_shader{glCreateShader(GL_FRAGMENT_SHADER)};
  source = (const GLchar *)frag_src.data();
  glShaderSource(fragment_shader, 1, &source, 0);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint max_length{0};
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);
    std::vector<GLchar> infoLog(max_length);
    glGetShaderInfoLog(fragment_shader, max_length, &max_length, &infoLog[0]);
    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);
    return;
  }
  program_ = glCreateProgram();
  glAttachShader(program_, vertex_shader);
  glAttachShader(program_, fragment_shader);
  glLinkProgram(program_);
  GLint isLinked{0};
  glGetProgramiv(program_, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint max_length{0};
    glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &max_length);
    std::vector<GLchar> infoLog(max_length);
    glGetProgramInfoLog(program_, max_length, &max_length, &infoLog[0]);
    glDeleteProgram(program_);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return;
  }
  glDetachShader(program_, vertex_shader);
  glDetachShader(program_, fragment_shader);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void shader_program::cleanup() { glDeleteProgram(program_); }

void img_2d_rend::init() {
  str vertex_shader_src{R"(
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
    )"};
  str fragment_shader_src{R"(
      #version 330 core
      out vec4 FragColor;
        
      in vec3 ourColor;
      in vec2 TexCoord;

      uniform sampler2D ourTexture;

      void main()
      {
          FragColor = texture(ourTexture, TexCoord);
      }
    )"};
  shader_program_ =
      std::make_shared<shader_program>(vertex_shader_src, fragment_shader_src);
}

void img_2d_rend::cleanup() {
  for (auto &entry : imgs_) {
    for (auto &entry2 : entry.second) {
      glDeleteVertexArrays(1, &entry2.second.vao);
      glDeleteBuffers(1, &entry2.second.ibo);
      glDeleteBuffers(1, &entry2.second.vbo);
    }
  }
  glUseProgram(0);
}

void img_2d_rend::reset_counter() { counter_ = 0; }

void img_2d_rend::draw_img(int img_name_hash, float x, float y, float w,
                           float h) {
  auto tex_id{_<Core::engine::Assets::Images::image_bank>().get_tex(img_name_hash)};

  img_2d_rend::draw_tex(tex_id, x, y, w, h);
}

void img_2d_rend::draw_tex(GLuint tex_id, float x, float y, float w, float h) {
  auto canv_sz{get_canv_sz(_<engine::sdl_device>().win())};
  glViewport(0, 0, canv_sz.w, canv_sz.h);
  glUseProgram(shader_program_->program());
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  float vertices[] = {x,     y,     0.0f, 1.0f, 1.0f, 1.0f, 0.0, 0.0,
                      x + w, y,     0.0f, 1.0f, 1.0f, 1.0f, 1.0, 0.0,
                      x + w, y + h, 0.0f, 1.0f, 1.0f, 1.0f, 1.0, 1.0,
                      x,     y + h, 0.0f, 1.0f, 1.0f, 1.0f, 0.0, 1.0};
  unsigned int indices[] = {0, 1, 2, 3};
  auto vertices_count{4};
  auto indices_count{4};
  GLuint obj_vao;
  GLuint obj_ibo;
  GLuint obj_vbo;
  auto need_create_buffers{false};
  if (imgs_.contains(counter_) && imgs_.at(counter_).contains(tex_id)) {
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
    img_2d_rend::entry entry;
    entry.vao = obj_vao;
    entry.ibo = obj_ibo;
    entry.vbo = obj_vbo;
    entry.x = x;
    entry.y = y;
    entry.w = w;
    entry.h = h;
    imgs_[counter_][tex_id] = entry;
    need_fill_buffers = true;
  }

  if (need_fill_buffers) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices_count,
                 indices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 8 * vertices_count,
                 vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
                          (void *)(sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
                          (void *)(sizeof(vertices[0]) * 6));
    glEnableVertexAttribArray(2);
  }
  glBindVertexArray(obj_vao);
  glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
  glBindTexture(GL_TEXTURE_2D, tex_id);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  ++counter_;
}

void img_2d_rend::draw_img_auto_h(str_view img_name, float x, float y,
                                  float w) {
  auto hash{forr::hash(img_name)};
  auto img_sz{_<Core::engine::Assets::Images::image_bank>().get_img_sz(hash)};
  if (img_sz.w <= 0 || img_sz.h <= 0)
    return;
  auto canv_asp_rat{calc_aspect_ratio(_<engine::sdl_device>().win())};
  auto img_asp_rat{c_float(img_sz.w) / img_sz.h};
  auto h{w / img_asp_rat * canv_asp_rat};
  draw_img(hash, x, y, w, h);
}

void img_2d_rend::draw_img(str_view img_name, float x, float y, float w,
                           float h) {
  draw_img(hash(img_name), x, y, w, h);
}

void ground_rend::init() {
  str vertex_shader_src{R"(
      #version 330 core
      layout (location = 0) in vec3 aPos;
      layout (location = 1) in vec3 aColor;
      layout (location = 2) in vec2 aTexCoord;
      layout (location = 3) in vec3 aNormal;

      uniform mat4 MVP;

      out vec3 ourColor;
      out vec2 TexCoord;
      out vec3 Normal;

      void main()
      {
          vec4 v = vec4(aPos, 1.0);
          gl_Position = MVP * v;
          gl_Position.x = gl_Position.x * 2.0 - 1.0;
          gl_Position.y = gl_Position.y * -2.0 + 1.0;
          ourColor = aColor;
          TexCoord = aTexCoord;
          Normal = aNormal;
      }
    )"};
  str fragment_shader_src{R"(
      #version 330 core
      out vec4 FragColor;
        
      in vec3 ourColor;
      in vec2 TexCoord;
      in vec3 Normal;

      uniform sampler2D ourTexture;


      void main()
      {
          vec3 lightColor = vec3(1.0, 1.0, 0.8);
          vec3 norm = normalize(Normal);
          vec3 lightDir = vec3(10.0, 10.0, 20.0);
          float diff = max(dot(norm, lightDir), 0.0);
          vec3 diffuse = diff * lightColor*0.05;
          vec4 objectColor = texture(ourTexture, TexCoord);
          vec3 result = diffuse* objectColor.rgb;
          FragColor = vec4(result, objectColor.a);
      }
    )"};
  shader_program_ =
      std::make_shared<shader_program>(vertex_shader_src, fragment_shader_src);
}

void ground_rend::cleanup() {
  for (auto &entry : imgs_) {
    for (auto &entry2 : entry.second) {
      glDeleteVertexArrays(1, &entry2.second.vao);
      glDeleteBuffers(1, &entry2.second.ibo);
      glDeleteBuffers(1, &entry2.second.vbo);
    }
  }
  glUseProgram(0);
}

void ground_rend::draw_tile(int img_name_hash, int x_coord, int y_coord,
                            float tl_sz, pt3_f camera_pos, vec<float> &elevs,
                            float elev_h) {
  auto tex_id{_<Core::engine::Assets::Images::image_bank>().get_tex(img_name_hash)};
  auto x{tl_sz * x_coord};
  auto y{tl_sz * y_coord};
  auto w{tl_sz};
  auto h{tl_sz};
  vec<float> verts{{x,
                    y,
                    -elevs.at(0) * elev_h,
                    1.0f,
                    1.0f,
                    1.0f,
                    0.0,
                    0.0,
                    x + w,
                    y,
                    -elevs.at(1) * elev_h,
                    1.0f,
                    1.0f,
                    1.0f,
                    1.0,
                    0.0,
                    x + w + w,
                    y,
                    -elevs.at(2) * elev_h,
                    1.0f,
                    1.0f,
                    1.0f,
                    1.0,
                    1.0,
                    x,
                    y + h,
                    -elevs.at(3) * elev_h,
                    1.0f,
                    1.0f,
                    1.0f,
                    0.0,
                    1.0,
                    x + w,
                    y + h,
                    -elevs.at(4) * elev_h,
                    1.0f,
                    1.0f,
                    1.0f,
                    1.0,
                    1.0,
                    x + w + w,
                    y + h,
                    -elevs.at(5) * elev_h,
                    1.0f,
                    1.0f,
                    1.0f,
                    1.0,
                    1.0,
                    x,
                    y + h + h,
                    -elevs.at(6) * elev_h,
                    1.0f,
                    1.0f,
                    1.0f,
                    1.0,
                    1.0,
                    x + w,
                    y + h + h,
                    -elevs.at(7) * elev_h,
                    1.0f,
                    1.0f,
                    1.0f,
                    1.0,
                    1.0,
                    x + w + w,
                    y + h + h,
                    -elevs.at(8) * elev_h,
                    1.0f,
                    1.0f,
                    1.0f,
                    1.0,
                    1.0}};
  ground_rend::draw_tex(tex_id, verts, camera_pos);
}

void ground_rend::draw_tex(GLuint tex_id, vec<float> &verts, pt3_f camera_pos) {
  glEnable(GL_DEPTH_TEST);
  auto canv_sz{get_canv_sz(_<engine::sdl_device>().win())};
  glViewport(0, 0, canv_sz.w * 1, canv_sz.h);
  glUseProgram(shader_program_->program());
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  auto vertices_no_normals = verts.data();
  unsigned int indices[] = {0, 1, 2, 3};
  vec<glm::vec3> normals;
  auto vertices_count{4};
  auto indices_count{4};
  auto _00x{vertices_no_normals[0 * 8 + 0]};
  auto _00y{vertices_no_normals[0 * 8 + 1]};
  auto _00z{vertices_no_normals[0 * 8 + 2]};
  auto _10x{vertices_no_normals[1 * 8 + 0]};
  auto _10y{vertices_no_normals[1 * 8 + 1]};
  auto _10z{vertices_no_normals[1 * 8 + 2]};
  auto _20x{vertices_no_normals[2 * 8 + 0]};
  auto _20y{vertices_no_normals[2 * 8 + 1]};
  auto _20z{vertices_no_normals[2 * 8 + 2]};
  auto _01x{vertices_no_normals[3 * 8 + 0]};
  auto _01y{vertices_no_normals[3 * 8 + 1]};
  auto _01z{vertices_no_normals[3 * 8 + 2]};
  auto _11x{vertices_no_normals[4 * 8 + 0]};
  auto _11y{vertices_no_normals[4 * 8 + 1]};
  auto _11z{vertices_no_normals[4 * 8 + 2]};
  auto _21x{vertices_no_normals[5 * 8 + 0]};
  auto _21y{vertices_no_normals[5 * 8 + 1]};
  auto _21z{vertices_no_normals[5 * 8 + 2]};
  auto _02x{vertices_no_normals[6 * 8 + 0]};
  auto _02y{vertices_no_normals[6 * 8 + 1]};
  auto _02z{vertices_no_normals[6 * 8 + 2]};
  auto _12x{vertices_no_normals[7 * 8 + 0]};
  auto _12y{vertices_no_normals[7 * 8 + 1]};
  auto _12z{vertices_no_normals[7 * 8 + 2]};
  auto _22x{vertices_no_normals[8 * 8 + 0]};
  auto _22y{vertices_no_normals[8 * 8 + 1]};
  auto _22z{vertices_no_normals[8 * 8 + 2]};
  glm::vec3 v00 = {_00x, _00y, _00z};
  glm::vec3 v10 = {_10x, _10y, _10z};
  glm::vec3 v20 = {_20x, _20y, _20z};
  glm::vec3 v01 = {_01x, _01y, _01z};
  glm::vec3 v11 = {_11x, _11y, _11z};
  glm::vec3 v21 = {_21x, _21y, _21z};
  glm::vec3 v02 = {_02x, _02y, _02z};
  glm::vec3 v12 = {_12x, _12y, _12z};
  glm::vec3 v22 = {_22x, _22y, _22z};
  glm::vec3 normal00 = compute_normal(v10, v00, v01);
  glm::vec3 normal10 = compute_normal(v20, v10, v11);
  glm::vec3 normal11 = compute_normal(v21, v11, v12);
  glm::vec3 normal01 = compute_normal(v11, v01, v02);
  normal00.z *= -1.0f;
  normal10.z *= -1.0f;
  normal11.z *= -1.0f;
  normal01.z *= -1.0f;
  normals.push_back(normal00);
  normals.push_back(normal10);
  normals.push_back(normal11);
  normals.push_back(normal01);
  vec<float> vertices_vec;
  auto fn{[&](int i, int j) {
    vertices_vec.push_back(vertices_no_normals[i * 8 + 0]);
    vertices_vec.push_back(vertices_no_normals[i * 8 + 1]);
    vertices_vec.push_back(vertices_no_normals[i * 8 + 2]);
    vertices_vec.push_back(vertices_no_normals[i * 8 + 3]);
    vertices_vec.push_back(vertices_no_normals[i * 8 + 4]);
    vertices_vec.push_back(vertices_no_normals[i * 8 + 5]);
    vertices_vec.push_back(vertices_no_normals[i * 8 + 6]);
    vertices_vec.push_back(vertices_no_normals[i * 8 + 7]);
    vertices_vec.push_back(normals.at(j).x);
    vertices_vec.push_back(normals.at(j).y);
    vertices_vec.push_back(normals.at(j).z);
  }};
  fn(0, 0);
  fn(1, 1);
  fn(4, 2);
  fn(3, 3);
  auto vertices{vertices_vec.data()};
  GLuint obj_vao;
  GLuint obj_ibo;
  GLuint obj_vbo;
  auto need_create_buffers{false};
  if (imgs_.contains(verts.at(0)) &&
      imgs_.at(verts.at(0)).contains(verts.at(1))) {
    need_create_buffers = false;
  } else {
    need_create_buffers = true;
    glGenVertexArrays(1, &obj_vao);
    glGenBuffers(1, &obj_vbo);
    glGenBuffers(1, &obj_ibo);
  }
  auto need_fill_buffers{false};
  if (!need_create_buffers) {
    auto &entry = imgs_.at(verts.at(0)).at(verts.at(1));
    obj_vao = entry.vao;
    obj_ibo = entry.ibo;
    obj_vbo = entry.vbo;
    glBindVertexArray(obj_vao);
    glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
    if (verts.at(0) != entry.x || verts.at(1) != entry.y) {
      need_fill_buffers = true;
      entry.x = verts.at(0);
      entry.y = verts.at(1);
    }
  } else {
    glBindVertexArray(obj_vao);
    glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
    forr::entry entry;
    entry.vao = obj_vao;
    entry.ibo = obj_ibo;
    entry.vbo = obj_vbo;
    entry.x = verts.at(0);
    entry.y = verts.at(1);
    imgs_[verts.at(0)][verts.at(1)] = entry;
    need_fill_buffers = true;
  }
  if (need_fill_buffers) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices_count,
                 indices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 11 * vertices_count,
                 vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 11,
                          0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 11,
                          (void *)(sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 11,
                          (void *)(sizeof(vertices[0]) * 6));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 11,
                          (void *)(sizeof(vertices[0]) * 8));
    glEnableVertexAttribArray(3);
  }
  glm::mat4 model_matrix = glm::mat4(1.0f);
  model_matrix = glm::translate(model_matrix, glm::vec3(-0.5f, -0.5f, 0.0f));
  // auto asp_rat{calc_aspect_ratio(_<sdl_device>().win())};
  //  lookAt function takes in camera position, target, and up vector.
  //  lookAt function takes camera position, camera target and up vector.
  glm::mat4 camera_matrix = glm::lookAt(
      glm::vec3(camera_pos.x, camera_pos.y - 2.0f, -camera_pos.z + 2.5f),
      glm::vec3(camera_pos.x, camera_pos.y, -camera_pos.z),
      glm::vec3(0.0f, 0.0f, -1.0f));
  // perspective function takes field of view, aspect ratio, near clipping
  // distance and far clipping distance.
  auto asp_rat{calc_aspect_ratio(_<engine::sdl_device>().win())};
  glm::mat4 projection_matrix = glm::perspective(90.0f, asp_rat, 0.1f, 100.0f);
  glm::mat4 final_matrix = projection_matrix * camera_matrix * model_matrix;
  GLuint matrix_id = glGetUniformLocation(shader_program_->program(), "MVP");
  glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &final_matrix[0][0]);
  glBindVertexArray(obj_vao);
  glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
  glBindTexture(GL_TEXTURE_2D, tex_id);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDisable(GL_DEPTH_TEST);
}

glm::vec3 ground_rend::compute_normal(glm::vec3 p1, glm::vec3 p2,
                                      glm::vec3 p3) {
  // Uses p2 as a new origin for p1, p3.
  auto a = p3 - p2;
  auto b = p1 - p2;
  // Compute the cross product a X b to get the face normal.
  return glm::normalize(glm::cross(a, b));
}

void model_rend::init() {
  str vertex_shader_src{R"(
      #version 330 core
      layout (location = 0) in vec3 aPos;
      layout (location = 1) in vec3 aNormal;
      layout (location = 2) in vec2 aTexCoord;

      out vec3 FragPos;
      out vec3 Normal;
      out vec2 TexCoord;

      uniform mat4 projection; 
      uniform mat4 view; 
      uniform mat4 model;

      uniform float scale;

      void main()
      {
          FragPos = vec3(model * vec4(aPos, 1.0));
          Normal = vec3(model * vec4(aNormal, 0.0));
          gl_Position = projection * view * vec4(FragPos, 1.0);
          gl_Position.x = gl_Position.x * 2.0 - 1.0;
          gl_Position.y = gl_Position.y * -2.0 + 1.0;
          TexCoord = aTexCoord;
      }
    )"};
  str fragment_shader_src{R"(
      #version 330 core
      out vec4 FragColor;

      in vec3 Normal;  
      in vec3 FragPos;
      in vec2 TexCoord;

      uniform vec3 lightPos;
      uniform vec3 viewPos;
      uniform sampler2D ourTexture;

      vec3 lightColor = vec3(1,1,1);
      //vec3 objectColor = vec3(0.6, 0.6, 0.6);
      uniform float shininess = 32.0f;
      uniform vec3 material_specular = vec3(0.1f, 0.1f, 0.1f);
      uniform vec3 light_specular = vec3(0.5f, 0.5f, 0.5f);

      void main()
      {
          // ambient
          float ambientStrength = 0.2;
          vec3 ambient = ambientStrength * lightColor;

          // diffuse 
          vec3 norm = normalize(Normal);
          vec3 lightDir = normalize(lightPos - FragPos);
          float diff = max(dot(norm, lightDir), 0.0);
          vec3 diffuse = diff * lightColor;

          // specular
          vec3 viewDir = normalize(viewPos - FragPos);
          vec3 reflectDir = reflect(-lightDir, norm);  
          float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
          vec3 specular = light_specular * (spec * material_specular);  

          vec3 objectColor = texture(ourTexture, TexCoord).rgb;

          vec3 result = (ambient + diffuse + specular) * objectColor;
          FragColor = vec4(result, 1.0);
      }
    )"};
  shader_program_ =
      std::make_shared<shader_program>(vertex_shader_src, fragment_shader_src);
}

void model_rend::draw_model(int model_name_hash, float x, float y, float elev,
                            pt3_f camera_pos, float elev_h) {
  glEnable(GL_DEPTH_TEST);
  auto model{_<Core::engine::Assets::Models::model_bank>().get_model(model_name_hash)};
  if (!model) {
    std::cout << "Model not found" << std::endl;
    return;
  }
  auto &meshes{model->meshes_ref()};
  auto canv_sz{get_canv_sz(_<engine::sdl_device>().win())};
  glViewport(0, 0, canv_sz.w, canv_sz.h);
  glUseProgram(shader_program_->program());
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  vec<unsigned int> indices_vec;
  vec<glm::vec3> normals;
  vec<float> vertices_vec;
  auto i{0};
  for (auto &mesh : meshes) {
    for (auto &vertex : mesh.vertices) {
      vertices_vec.push_back(x + vertex.position.x * k_mdl_scale);
      vertices_vec.push_back(y + vertex.position.y * k_mdl_scale);
      vertices_vec.push_back(-elev * elev_h + vertex.position.z * k_mdl_scale);
      vertices_vec.push_back(vertex.normal.x);
      vertices_vec.push_back(vertex.normal.y);
      vertices_vec.push_back(vertex.normal.z);
      vertices_vec.push_back(vertex.tex_coord.x);
      vertices_vec.push_back(vertex.tex_coord.y);
    }
    for (auto &index : mesh.indices)
      indices_vec.push_back(i + mesh.indices[index]);
    i += mesh.vertices.size();
  }
  auto vertices_count{vertices_vec.size() / 8};
  auto indices_count{indices_vec.size()};
  auto vertices{vertices_vec.data()};
  auto indices{indices_vec.data()};
  GLuint obj_vao;
  GLuint obj_ibo;
  GLuint obj_vbo;
  auto need_create_buffers{false};
  if (models_.contains(x) && models_.at(x).contains(y) &&
      models_.at(x).at(y).contains(elev) &&
      models_.at(x).at(y).at(elev).contains(model_name_hash)) {
    need_create_buffers = false;
  } else {
    need_create_buffers = true;
    glGenVertexArrays(1, &obj_vao);
    glGenBuffers(1, &obj_vbo);
    glGenBuffers(1, &obj_ibo);
  }
  auto need_fill_buffers{false};
  if (!need_create_buffers) {
    auto &entry = models_.at(x).at(y).at(elev).at(model_name_hash);
    obj_vao = entry.vao;
    obj_ibo = entry.ibo;
    obj_vbo = entry.vbo;
    glBindVertexArray(obj_vao);
    glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
    if (x != entry.x || y != entry.y || elev != entry.z) {
      need_fill_buffers = true;
      entry.x = x;
      entry.y = y;
      entry.z = elev;
    }
  } else {
    glBindVertexArray(obj_vao);
    glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
    forr::entry entry;
    entry.vao = obj_vao;
    entry.ibo = obj_ibo;
    entry.vbo = obj_vbo;
    entry.x = x;
    entry.y = y;
    entry.z = elev;
    models_[x][y][elev][model_name_hash] = entry;
    need_fill_buffers = true;
  }
  if (need_fill_buffers) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices_count,
                 indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 8 * vertices_count,
                 vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
                          (void *)(sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
                          (void *)(sizeof(vertices[0]) * 6));
    glEnableVertexAttribArray(2);
  }
  glm::mat4 model_matrix = glm::mat4(1.0f);
  // lookAt function takes camera position, camera target and up vector.
  glm::mat4 camera_matrix = glm::lookAt(
      glm::vec3(camera_pos.x, camera_pos.y - 2.0f, -camera_pos.z + 2.5f),
      glm::vec3(camera_pos.x, camera_pos.y, -camera_pos.z),
      glm::vec3(0.0f, 0.0f, -1.0f));
  // perspective function takes field of view, aspect ratio, near clipping
  // distance and far clipping distance.
  auto asp_rat{calc_aspect_ratio(_<engine::sdl_device>().win())};
  glm::mat4 projection_matrix = glm::perspective(90.0f, asp_rat, 0.1f, 100.0f);
  GLuint matrix_projection =
      glGetUniformLocation(shader_program_->program(), "projection");
  glUniformMatrix4fv(matrix_projection, 1, GL_FALSE, &projection_matrix[0][0]);
  GLuint matrix_model =
      glGetUniformLocation(shader_program_->program(), "model");
  glUniformMatrix4fv(matrix_model, 1, GL_FALSE, &model_matrix[0][0]);
  GLuint matrix_view = glGetUniformLocation(shader_program_->program(), "view");
  glUniformMatrix4fv(matrix_view, 1, GL_FALSE, &camera_matrix[0][0]);
  glBindVertexArray(obj_vao);
  glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
  // std::cout << meshes.at(0).textures.size() << std::endl;
  auto tex_name{meshes.at(0).textures.at(0).path_};
  // std::cout << tex_name << std::endl;
  auto tex_name_hash{hash(tex_name)};
  auto tex_id{_<Core::engine::Assets::Images::image_bank>().get_tex(tex_name_hash)};
  glBindTexture(GL_TEXTURE_2D, tex_id);
  glDrawElements(GL_TRIANGLE_FAN, vertices_count, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDisable(GL_DEPTH_TEST);
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
  auto canv_sz{get_canv_sz(_<engine::sdl_device>().win())};
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
  auto tex_already_exists{_<Core::engine::Assets::Images::image_bank>().text_tex_exists(xx, yy, text_hash)};
  auto tex{_<Core::engine::Assets::Images::image_bank>().obtain_text_tex(xx, yy, text_hash)};
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindTexture(GL_TEXTURE_2D, tex);
  if (tex_already_exists) {
  } else {
    auto sdl_color{text_color.to_sdl_color()};
    auto surf{TTF_RenderText_Solid(font_raw, text.data(), sdl_color)};
    auto new_w{surf->w};
    auto new_h{surf->h};
    auto intermediary = SDL_CreateRGBSurface(
        0, new_w, new_h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    SDL_BlitSurface(surf, 0, intermediary, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, intermediary->w, intermediary->h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, intermediary->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(intermediary);
    SDL_FreeSurface(surf);
  }
  auto xf{c_float(dest.x) / canv_sz.w};
  auto yf{c_float(dest.y) / canv_sz.h};
  auto wf{c_float(dest.w) / canv_sz.w};
  auto hf{c_float(dest.h) / canv_sz.h};
  _<img_2d_rend>().draw_tex(tex, xf, yf, wf, hf);
}
_NS_END_