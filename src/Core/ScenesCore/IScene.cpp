#include "IScene.hpp"

namespace Forradia
{
    IScene::IScene()
    {
    }

    void IScene::Update()
    {
        UpdateDerived();
    }

    void IScene::Render() const
    {
        RenderDerived();
    }
}
