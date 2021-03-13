#include "gfx/mesh.hpp"
#include "util/log.hpp"

namespace gfx {
    Mesh::Mesh(std::size_t values_per_vertex, bool dynamic)
        : vertices_vbo(GL_ARRAY_BUFFER, dynamic), indices_vbo(GL_ELEMENT_ARRAY_BUFFER, dynamic),
          values_per_vertex(values_per_vertex) {}

    Mesh::~Mesh() {}

    void Mesh::create(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
        vertices_count = vertices.size() / values_per_vertex;
        indices_count = indices.size();
        
        vao.bind();

        vertices_vbo.data(vertices);
        indices_vbo.data(indices);

        std::size_t stride = values_per_vertex * sizeof(float);
        prepare_attributes(stride);

        LOG("Created mesh containing " << vertices_count << " vertices (" << vertices.size() <<
            " floating-point values) and " << indices_count << " indices");
    }
    
    void Mesh::bind_and_draw() const {
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);
    }
}
