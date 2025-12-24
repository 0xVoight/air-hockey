#include "GlfwWindow.h"

#include <GLFW/glfw3.h>
#include <stdexcept>

GlfwWindow::GlfwWindow(int width, int height, const char* title)
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);


    m_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_handle) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(1);
}

GlfwWindow::~GlfwWindow()
{
    if (m_handle) {
        glfwDestroyWindow(m_handle);
        glfwTerminate();
    }
}

void GlfwWindow::pollEvents()
{
    glfwPollEvents();
    m_input.up    = glfwGetKey(m_handle, GLFW_KEY_W) == GLFW_PRESS;
    m_input.down  = glfwGetKey(m_handle, GLFW_KEY_S) == GLFW_PRESS;
    m_input.left  = glfwGetKey(m_handle, GLFW_KEY_A) == GLFW_PRESS;
    m_input.right = glfwGetKey(m_handle, GLFW_KEY_D) == GLFW_PRESS;
}

void GlfwWindow::swapBuffers()
{
    glfwSwapBuffers(m_handle);
}

bool GlfwWindow::shouldClose() const
{
    return glfwWindowShouldClose(m_handle);
}

int GlfwWindow::width() const
{
    int w, h;
    glfwGetFramebufferSize(m_handle, &w, &h);
    return w;
}

int GlfwWindow::height() const
{
    int w, h;
    glfwGetFramebufferSize(m_handle, &w, &h);
    return h;
}
