//
// Created by apgra on 11/27/2023.
//

#ifndef FLUID_SIM_APPLICATION_H
#define FLUID_SIM_APPLICATION_H


#include <memory>
#include "../Engine/Camera.h"
#include "../Engine/Window.h"

class GLFWwindow;

class Application {
public:
    void Run();

private:
    void onStart();
    void onTick();
    void onRender();
    void onImGUIRender();
    void onClose();

public:
    Camera* GetCamera() {return m_Camera.get();}

private:
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    int frameCount = 0;


    std::unique_ptr<Camera> m_Camera;
    std::unique_ptr<Window> m_Window;


private:
    static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void onScroll(GLFWwindow *window, double xoffset, double yoffset);
    static void onWindowResize(GLFWwindow* window, int width, int height);

    void processInput(GLFWwindow *window);
};


#endif //FLUID_SIM_APPLICATION_H
