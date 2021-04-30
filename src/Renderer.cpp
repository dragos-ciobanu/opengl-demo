//
// Created by dragos on 28.04.21.
//
#include "Renderer.h"

void Renderer::Draw(const VertexBuffer &vb, const IndexBuffer &ib, const Shader &shader) const {
    shader.Bind();
    ib.Bind();
    vb.Bind();

    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);

}

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT);

}

