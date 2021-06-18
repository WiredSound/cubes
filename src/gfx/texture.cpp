#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "gfx/texture.hpp"
#include "util/log.hpp"

namespace gfx {
    Texture::Texture(const std::string& path, bool generate_mipmap) {
        glGenTextures(1, &id);
        bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        if(data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            if(generate_mipmap) glGenerateMipmap(GL_TEXTURE_2D);

            LOG("Loaded texture " << id << " from: " << path);
        }
        else {
            LOG_ERROR("Failed to load texture from: " << path);
        }

        stbi_image_free(data);
    }

    Texture::~Texture() {
        if(id) {
            glDeleteTextures(1, &id);
            LOG("Deleted texture " << id);
        }
    }

    unsigned int Texture::operator*() const {
        return id;
    }

    void Texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, id);
    }
}
