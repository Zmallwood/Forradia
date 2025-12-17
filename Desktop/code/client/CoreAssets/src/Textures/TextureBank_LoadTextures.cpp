/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "TextureBank.hpp"

namespace Forradia {
auto TextureBank::LoadTextures() -> void {
  auto basePath{String(SDL_GetBasePath())};
  auto imagesPath{basePath + k_relativeImagesPath.data()};

  if (false == std::filesystem::exists(imagesPath))
    return;

  std::filesystem::recursive_directory_iterator rdi{imagesPath};

  // Iterate through the directory using the rdi.
  for (auto it : rdi) {
    auto filePath{Replace(it.path().string(), '\\', '/')};

    if (GetFileExtension(filePath) == "png") {
      auto fileName{GetFileNameNoExtension(filePath)};
      auto hash{Forradia::Hash(fileName)};
      auto surface{SharedPtr<SDL_Surface>(IMG_Load(filePath.data()), SDLDeleter())};
      auto textureID{this->LoadSingleTexture(surface)};
      auto imageSize{Size{surface->w, surface->h}};
      TextureEntry newTextureEntry;
      newTextureEntry.textureID = textureID;
      newTextureEntry.dimensions = imageSize;
      m_textureEntries[hash] = newTextureEntry;
    }
  }
}
}
