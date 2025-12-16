//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "TextureBank.hpp"

namespace Forradia {
    void TextureBank::Initialize() {
        this->LoadTextures();
    }

    void TextureBank::Cleanup() {
        for (auto entry : m_textureEntries) {
            glDeleteTextures(1, &entry.second.textureID);
        }
        for (auto entry : m_textTextureIDs) {
            glDeleteTextures(1, &entry.second);
        }
        m_textureEntries.clear();
        m_textTextureIDs.clear();
    }

    GLuint TextureBank::GetTexture(int imageNameHash) const {
        if (m_textureEntries.contains(imageNameHash)) {
            return m_textureEntries.at(imageNameHash).textureID;
        }
        return -1;
    }

    Size TextureBank::GetTextureDimensions(int imageNameHash) const {
        if (m_textureEntries.contains(imageNameHash)) {
            return m_textureEntries.at(imageNameHash).dimensions;
        }
        return {-1, -1};
    }
}