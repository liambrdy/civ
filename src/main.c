#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#ifndef  M_PI
#define  M_PI  3.1415926535897932384626433
#endif

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Civ", NULL, NULL);
    assert(window);
    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);

    uint32_t vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void *)(2 * sizeof(float)));

    uint32_t vbo, ibo;
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    float bufferData[6 * 5];
    int index = 0;

    for (int i = 0; i < 6; i++) {
        bufferData[index++] = cosf((M_PI / 3) * (i + 1));
        bufferData[index++] = sinf((M_PI / 3) * (i + 1));

        bufferData[index++] = 1.0f;
        bufferData[index++] = 1.0f;
        bufferData[index++] = 1.0f;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}