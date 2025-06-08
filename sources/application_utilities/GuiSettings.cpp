#include "GuiSettings.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "Settings.h"

GuiSettings::GuiSettings(const Window& window, const Context& context)
    : settings_(Settings::getInstance())
{
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window.getSdlWindow(), context.getGlContext());
    ImGui_ImplOpenGL3_Init("#version 460");  // Use the appropriate GLSL version
    ImGui::StyleColorsDark(); // Sets the default style to dark mode
}


GuiSettings::~GuiSettings()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}


void 
GuiSettings::update()
{
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    // Render GUI settings
    ImGui::Begin("Settings");
    // Add ImGui widgets for each setting, e.g., sliders, checkboxes
    ImGui::SliderFloat("Sensitivity", &settings_.camera.sensitivity, 0.0f, 1.0f);
  
    if (ImGui::Button("Simulation On/Off")) 
    {
        std::cout << "Simulation On/Off" << std::endl;
        settings_.simulation.isRunning = !settings_.simulation.isRunning;
    }
    
    //ImGui::Combo("Camera Mode", &c, "Spherical\0Flying\0");
    const char* cameraModes[] = { "Spherical", "Third Person", "First Person" };
    int currentMode = static_cast<int>(settings_.camera.mode);
    if (ImGui::Combo("Camera Mode", &currentMode, cameraModes, IM_ARRAYSIZE(cameraModes)))
    {
        settings_.camera.mode = static_cast<CameraMode>(currentMode);
    }

    ImGui::End();

    render();
}


void 
GuiSettings::render()
{
    // render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
