#include "MainScene.hpp"
#include "Theme0/Theme0Mechanics/WorldView/WorldView.hpp"
#include "Theme0/Theme0Mechanics/PlayerMovement/UpdateKeyboardMovement.hpp"
#include "Theme0/Theme0Mechanics/MobMovement/UpdateMobMovement.hpp"
#include "Theme0/Theme0Mechanics/General/UpdateKeyboardBindingActions.hpp"

namespace Forradia
{
    void MainScene::UpdateDerived()
    {
        UpdateMobMovement();

        UpdateKeyboardMovement();

        UpdateKeyboardBindingActions();
    }

    void MainScene::RenderDerived() const
    {
        _<WorldView>().Render();
    }
}
