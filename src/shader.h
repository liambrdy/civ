#ifndef SHADER_H
#define SHADER_H

#include <stdint.h>

typedef struct {
    uint32_t id;
} Shader;

void LoadShader(Shader *shader, char *vertPath, char *fragPath);

#endif