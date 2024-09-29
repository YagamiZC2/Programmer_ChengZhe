#pragma once
#include "system.h"

unsigned int LoadTexture(const char *FileName, GLint param = GL_LINEAR);
void UnloadTexture(unsigned int Texture);
void SetTexture(unsigned int Texture);


