/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "AudioBank.hpp"
#include <string>
#include <SDL2/SDL_mixer.h>

namespace ForradiaEngine
{
    auto AudioBank::initialize() -> void
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            throwError("Failed to open audio: " + std::string(Mix_GetError()));
        }

        this->loadMusic();
        this->loadSound();
    }

    auto AudioBank::cleanup() -> void
    {
        Mix_CloseAudio();
    }

    auto AudioBank::loadMusic() -> void
    {
        auto basePath{std::string(SDL_GetBasePath())};
        auto musicPath{basePath + k_relativeMusicPath};

        if (std::filesystem::exists(musicPath) == false)
        {
            return;
        }

        std::filesystem::recursive_directory_iterator rdi{musicPath};

        for (const auto &file : rdi)
        {
            auto filePath{replace(file.path().string(), '\\', '/')};

            if (getFileExtension(filePath) == "ogg" || getFileExtension(filePath) == "mp3")
            {
                auto fileName{getFileNameNoExtension(filePath)};
                auto hash{ForradiaEngine::hash(fileName)};

                auto music{std::shared_ptr<Mix_Music>(Mix_LoadMUS(filePath.data()), SDLDeleter())};

                m_musicEntries[hash] = music;
            }
        }
    }

    auto AudioBank::loadSound() -> void
    {
        auto basePath{std::string(SDL_GetBasePath())};
        auto soundsPath{basePath + k_relativeSoundsPath};

        if (std::filesystem::exists(soundsPath) == false)
        {
            return;
        }

        std::filesystem::recursive_directory_iterator rdi{soundsPath};

        for (const auto &file : rdi)
        {
            auto filePath{replace(file.path().string(), '\\', '/')};

            if (getFileExtension(filePath) == "wav")
            {
                auto fileName{getFileNameNoExtension(filePath)};
                auto hash{ForradiaEngine::hash(fileName)};

                auto sound{std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(filePath.data()), SDLDeleter())};

                m_soundEntries[hash] = sound;
            }
        }
    }

    auto AudioBank::playMusic(int musicNameHash) -> void
    {
        if (m_musicEntries.contains(musicNameHash) == false)
        {
            return;
        }

        Mix_PlayMusic(m_musicEntries[musicNameHash].get(), -1);
    }

    auto AudioBank::playSound(int audioNameHash) -> void
    {
        if (m_soundEntries.contains(audioNameHash) == false)
        {
            return;
        }

        Mix_PlayChannel(-1, m_soundEntries[audioNameHash].get(), 0);
    }

    auto AudioBank::toggleMuteMusic() -> void
    {
        if (m_musicMuted)
        {
            this->unmuteMusic();
        }
        else
        {
            this->muteMusic();
        }
    }

    auto AudioBank::muteMusic() -> void
    {
        Mix_VolumeMusic(0);
        m_musicMuted = true;
    }

    auto AudioBank::unmuteMusic() -> void
    {
        Mix_VolumeMusic(MIX_MAX_VOLUME);
        m_musicMuted = false;
    }
}