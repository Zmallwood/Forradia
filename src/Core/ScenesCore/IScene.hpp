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
        void Initialize();

        void Update();

        void Render() const;

        virtual void OnEnter() {}

    protected:
        virtual void InitializeDerived() {}

        virtual void UpdateDerived() {}

        virtual void RenderDerived() const {}

        auto GetGUI() const { return m_gui; }

    private:
        SharedPtr<GUI> m_gui;
    };
}
