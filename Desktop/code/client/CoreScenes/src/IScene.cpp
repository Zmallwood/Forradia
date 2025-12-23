/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "IScene.hpp"
#include "GUI.hpp"

namespace Forradia
{
    auto IScene::initialize() -> void
    {
        m_gui = std::make_shared<GUI>();

        this->initializeDerived();
    }

    auto IScene::onEnter() -> void
    {
        this->onEnterDerived();
    }

    auto IScene::onMouseDown(Uint8 mouseButton) -> void
    {
        m_gui->onMouseDown(mouseButton);
    }

    auto IScene::onMouseUp(Uint8 mouseButton, int clickSpeed) -> void
    {
        m_gui->onMouseUp(mouseButton, clickSpeed);
    }

    auto IScene::onMouseWheel(int delta) -> void
    {
        m_gui->onMouseWheel(delta);
    }

    auto IScene::onKeyDown(SDL_Keycode key) -> void
    {
        m_gui->onKeyDown(key);
    }

    auto IScene::onKeyUp(SDL_Keycode key) -> void
    {
        m_gui->onKeyUp(key);
    }

    auto IScene::onTextInput(std::string_view text) -> void
    {
        m_gui->onTextInput(text);
    }

    auto IScene::update() -> void
    {
        m_gui->update();

        this->updateDerived();
    }

    auto IScene::render() const -> void
    {
        this->renderDerived();

        m_gui->render();
    }
}
