#include "shader.h"

#include <glad/gl.h>

#include <stdlib.h>
#include <stdio.h>

static char *ReadFile(char *path) {
    FILE *f = fopen(path, "r");
    if (f) {
        fseek(f, 0, SEEK_END);
        uint32_t size = ftell(f);
        rewind(f);

        size += 1;

        char *buffer = (char *)malloc(size);
        fread(buffer, size, 1, f);
        buffer[size - 1] = '\0';

        fclose(f);

        return buffer;
    }

    printf("Failed to read file: %s\n", path);

    return NULL;
}

static uint32_t CompileShader(char *path, GLenum type) {
    char *code = ReadFile(path);
    uint32_t shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar **)&code, NULL);
    glCompileShader(shader);

    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("%s shader error: %s\n", type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", infoLog);
        exit(1);
    }

    free(code);

    return shader;
}

void LoadShader(Shader *shader, char *vertPath, char *fragPath) {
    uint32_t vertShader = CompileShader(vertPath, GL_VERTEX_SHADER);
    uint32_t fragShader = CompileShader(fragPath, GL_FRAGMENT_SHADER);
    shader->id = glCreateProgram();
    
    glAttachShader(shader->id, vertShader);
    glAttachShader(shader->id, fragShader);
    glLinkProgram(shader->id);
    glValidateProgram(shader->id);
}