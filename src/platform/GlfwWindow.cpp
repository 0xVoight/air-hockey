#include "GlfwWindow.h"

#include <GLFW/glfw3.h>
#include <stdexcept>

GlfwWindow::GlfwWindow(int width, int height, const char* title)
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

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
    m_input.player1.up    = glfwGetKey(m_handle, GLFW_KEY_W) == GLFW_PRESS;
    m_input.player1.down  = glfwGetKey(m_handle, GLFW_KEY_S) == GLFW_PRESS;
    m_input.player1.left  = glfwGetKey(m_handle, GLFW_KEY_A) == GLFW_PRESS;
    m_input.player1.right = glfwGetKey(m_handle, GLFW_KEY_D) == GLFW_PRESS;

    m_input.player2.up    = (glfwGetKey(m_handle, GLFW_KEY_UP)    == GLFW_PRESS);
    m_input.player2.down  = (glfwGetKey(m_handle, GLFW_KEY_DOWN)  == GLFW_PRESS);
    m_input.player2.left  = (glfwGetKey(m_handle, GLFW_KEY_LEFT)  == GLFW_PRESS);
    m_input.player2.right = (glfwGetKey(m_handle, GLFW_KEY_RIGHT) == GLFW_PRESS);
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
