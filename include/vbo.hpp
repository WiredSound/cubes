#pragma once

#include <glad/glad.h>

#include <vector>

class VertexBufferObject {
public:
    VertexBufferObject(GLenum type, bool dynamic);
    ~VertexBufferObject();
    unsigned int operator*() const;
    void bind() const;

    template <typename T>
    void data(const std::vector<T>& vertices) {
        bind();
        glBufferData(type, vertices.size() * sizeof(T), vertices.data(), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }

private:
    unsigned int id;
    GLenum type;
    /// Whether buffer data should be created with `GL_DYNAMIC_DRAW` or `GL_STATIC_DRAW` (i.e. whether the buffer data
    /// will modified frequently or not).
    bool dynamic;
};
