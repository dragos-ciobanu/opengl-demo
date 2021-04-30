//
// Created by dragos on 28.04.21.
//
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include "VertexBuffer.h"
#include "Shader.h"
#include "IndexBuffer.h"

#else
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#ifndef HAND_RENDERER_H
#define HAND_RENDERER_H

class Renderer {
private:

public:
    void Clear() const;
    void Draw(const VertexBuffer& vb, const IndexBuffer& ib, const Shader& shader) const;
};
#endif //HAND_RENDERER_H
