#include "gui.h"
#include "base/log.h"
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <SDL.h>
#include <GL/gl3w.h> // Initialize with glewInit()
#include <teenypath.h>

#define WINDOW_TITLE "filemantaray"

SDL_GLContext gl_context;
SDL_Window *window;
ImGuiIO io;
const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
void GUILoop(FileSystem &fs)
{
    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT){
                done = true;
            }
            if (event.type == SDL_WINDOWEVENT &&
                    event.window.event == SDL_WINDOWEVENT_CLOSE &&
                    event.window.windowID == SDL_GetWindowID(window)) {
                done = true;
            }
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
        {
            ImGui::Begin("Hello, /dpt/!");
            ImGui::Text("%.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);

            for (auto &it : fs.m_roots) {
                ImGui::Text("%s", it.string().c_str());
            }
            ImGui::End();
        }
        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
}

void GUIInit()
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER |
            SDL_INIT_GAMECONTROLLER) != 0) {
        Error("%s", SDL_GetError());
        exit(-1);
    }

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
            SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    const SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL |
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    if (gl3wInit() != 0) {
        Error("Failed to initialize OpenGL loader!");
        exit(1);
    }
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO();
    //(void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void GUICleanup()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
