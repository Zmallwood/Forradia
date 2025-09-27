/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class GUI;

    class IScene
    {
    public:
        IScene();

        void Update();

        void Render() const;

        virtual void OnEnter() {}

        virtual void Initialize() {}

    protected:
        virtual void UpdateDerived() {}

        virtual void RenderDerived() const {}

        auto GetGUI() const
        {
            return m_gui;
        }

    private:
        SharedPtr<GUI> m_gui;
    };
}
