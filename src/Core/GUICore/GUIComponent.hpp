/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class GUIComponent
    {
    public:
        GUIComponent(float x,
                     float y,
                     float width,
                     float height)
            : m_bounds({x, y, width, height})
        {
        }

        SharedPtr<GUIComponent> AddChildComponent(SharedPtr<GUIComponent> component);

        void Update();

        void Render() const;

        void ToggleVisibility();

        void SetVisible(bool value) { m_visible = value; }

    protected:
        virtual void UpdateDerived() {}

        virtual void RenderDerived() const {}

        auto GetBounds() const { return m_bounds; }

    private:
        RectF m_bounds;
        Vector<SharedPtr<GUIComponent>> m_childComponents;
        bool m_visible{true};
        bool m_enabled{true};
    };
}
