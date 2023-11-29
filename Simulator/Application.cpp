//
// Created by apgra on 11/27/2023.
//

#include <imgui.h>
#include "Application.h"
#include "../Renderer/Shader.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


bool imGUIActive = true;

glm::vec3 boundsColor(1.0f);

void Application::Run() {
    onStart();

    while (!m_Window->shouldClose()) {
        onTick();
        onRender();
        onImGUIRender();
    }

    onClose();
}

void Application::onStart() {
    m_Window = std::make_unique<Window>(1280, 720, "3D World");
    m_Window->setUserPointer(this);

    m_Window->setKeyCallback(onKeyPressed);
    m_Window->setScrollCallback(onScroll);
    m_Window->setResizeCallback(onWindowResize);

    glEnable(GL_DEPTH_TEST);

    Shader::initializeShaders();

    //Setup IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    const char* glsl_version = "#version 460";
    ImGui_ImplGlfw_InitForOpenGL(m_Window->getGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 4.0f), 4.0f);
    m_FluidSim = std::make_unique<FluidSim>(&simConfig);

}

void Application::onTick() {
    processInput(m_Window->getGLFWWindow());
    m_Window->tick();

    m_FluidSim->step(deltaTime);

    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Application::onRender() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    Shaders::solid_unlit->bind();
    Shaders::solid_unlit->setMat4("projection", m_Camera->projection(m_Window->getSize()));
    Shaders::solid_unlit->setMat4("view", m_Camera->view());

    Shaders::solid_unlit->setVec3("color", boundsColor);

    m_FluidSim->draw();
}

void Application::onImGUIRender() {
    if(!imGUIActive){
        return;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Config Window");

    bool reset = false;

    if(ImGui::CollapsingHeader("Bounds Config")) {
        ImGui::InputFloat2("Bounds Center", &simConfig.bounds.center.x);
        ImGui::SliderFloat2("Bounds Offset", &simConfig.bounds.offset.x, 0.0f, 10.0f);
        ImGui::ColorPicker3("Bounds Color", &boundsColor.x);
    }

    ImGui::InputInt("Num Particles", &simConfig.numParticles);


    if(ImGui::Button("Reset Sim")){
        m_FluidSim->reset();
    }

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void Application::onClose() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}


void Application::processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_W)){
        m_Camera->move(Forward, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_S)){
        m_Camera->move(Backward, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_A)){
        m_Camera->move(Left , deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_D)){
        m_Camera->move(Right, deltaTime);
    }

    //Mouse Input
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE)) {
        static double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        m_Camera->rotate((float) mouseX, (float) mouseY);
    }
}

void Application::onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Application* app = (Application*) glfwGetWindowUserPointer(window);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        imGUIActive = !imGUIActive;
    }
}

void Application::onScroll(GLFWwindow *window, double xoffset, double yoffset) {
    Application* app = (Application*) glfwGetWindowUserPointer(window);


    if(yoffset > 0){
        app->GetCamera()->increaseMoveSpeed(1.0f);
    }

    if(yoffset < 0){
        app->GetCamera()->increaseMoveSpeed(-1.0f);
    }
}

void Application::onWindowResize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

}
