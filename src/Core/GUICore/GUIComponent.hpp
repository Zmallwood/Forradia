#pragma once

namespace Forradia
{
    class GUIComponent
    {
    public:
        GUIComponent(float x,
                     float y,
                     float width,
                     float height);

        void AddChildComponent(std::shared_ptr<GUIComponent> component);

        void Update();

        void Render() const;

        void ToggleVisibility();

    protected:
        virtual void UpdateDerived() {}

        virtual void RenderDerived() const {}

        auto GetBounds() const
        {
            return m_bounds;
        }

        void SetVisible(bool value)
        {
            m_visible = value;
        }

    private:
        RectF m_bounds;
        std::vector<std::shared_ptr<GUIComponent>> m_childComponents;
        bool m_visible{true};
        bool m_enabled{true};
    };
}
