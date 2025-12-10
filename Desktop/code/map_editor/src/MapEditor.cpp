//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "MapEditor.hpp"
#include "ImGuiDevice.hpp"
#include "SDLDevice.hpp"

namespace Forradia
{
    void MapEditor::Run()
    {
        _<ImGuiDevice>().Setup();

        auto renderer{_<SDLDevice>().m_renderer.get()};

        while (m_running)
        {
            PollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            // properties window
            ImGui::Begin("My Window");
            ImGui::SetWindowSize(ImVec2((float)200, (float)200));
            ImGui::Text("Color");
            ImGui::End();

            // send ImGui context to SDL Renderer context
            ImGui::Render();
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

            // show all renders now
            SDL_RenderPresent(renderer);

            // clear the renders
            //SDL_RenderClear(renderer);

            _<SDLDevice>().ClearCanvas();
        }
    }

    void MapEditor::PollEvents()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            // Pass events to ImGui
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT)
            {
                m_running = false;
            }
        }
    }
}