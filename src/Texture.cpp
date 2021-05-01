//
// Created by dragos on 01.05.21.
//

#include "Texture.h"
#include "../vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path)
:m_filePath(path), m_localBuffer(nullptr), m_height(0), m_width(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(true);
    m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &m_RendererId);
    glBindTexture(GL_TEXTURE_2D, m_RendererId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_localBuffer) {
        stbi_image_free(m_localBuffer);
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &m_RendererId);
}

void Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererId);

}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);

}

