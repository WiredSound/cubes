#pragma once

#include <string>

namespace gfx {
    class Texture {
    public:
        Texture(const std::string& path, bool generate_mipmap = false);

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        ~Texture();
        
        unsigned int operator*() const;
        void bind() const;

    private:
        unsigned int id;
    };
}
