/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <unordered_map>

namespace ForradiaEngine
{
    class AudioBank
    {
      public:
        static auto instance() -> AudioBank &
        {
            static AudioBank instance;
            return instance;
        }

        AudioBank(const AudioBank &) = delete;

        auto operator=(const AudioBank &) -> AudioBank & = delete;

        /**
         *  Constructor.
         */
        AudioBank()
        {
            this->initialize();
        }

        /**
         *  Destructor.
         */
        ~AudioBank()
        {
            this->cleanup();
        }

        auto playMusic(int musicNameHash) -> void;

        auto playSound(int audioNameHash) -> void;

      private:
        auto initialize() -> void;

        auto cleanup() -> void;

        auto loadMusic() -> void;

        auto loadSound() -> void;

        inline static const std::string k_relativeMusicPath{"./Resources/Music/"};
        inline static const std::string k_relativeSoundsPath{"./Resources/Sounds/"};
        std::unordered_map<int, std::shared_ptr<Mix_Music>> m_musicEntries{};
        std::unordered_map<int, std::shared_ptr<Mix_Chunk>> m_soundEntries{};
    };
}