//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "GUIFPSPanel.hpp"
#include "FPSCounter.hpp"
#include "GUILabel.hpp"

namespace Forradia {
    void GUIFPSPanel::Initialize() {
        // Create the FPS text label.

        m_fpsTextPanel = std::make_shared<GUILabel>("GUILabelFPSPanel", 0.01f, 0.01f, 0.1f, 0.05f);

        // Add the FPS text label to this panel.

        this->AddChildComponent(m_fpsTextPanel);
    }

    void GUIFPSPanel::UpdateDerived() {
        // Do the updating specific to the base class (GUIMovablePanel).

        GUIMovablePanel::UpdateDerived();

        // Get the FPS.

        auto fps{_<FPSCounter>().GetFPS()};

        // Set the text of the FPS text label.

        m_fpsTextPanel->SetText(fmt::format("FPS: {}", fps));
    }
}