#pragma once

#include <array>

#include "util/log.hpp"
#include "util/coords.hpp"

namespace util {
    template <typename Vertex, typename Mesh, unsigned int stride>
    class MeshBuilder {
    public:
        Mesh build() {
            Mesh mesh;
            mesh.create(vertices, indices);
            return mesh;
        }

    protected:
        /// Will either create a new vertex with the specified colour and return its index, or will provide the index
        /// of an exist vertex should one already exist at the specified coordinates and with the specified colour.
        unsigned int require_vertex(const Vertex& vertex) {
            auto search = past_vertex_to_index.find(vertex);

            if(search != past_vertex_to_index.end()) {
                // Return index of existing vertex:

                auto existing_index = search->second;

                LOG_TRACE("Required vertex " << util::coords_to_string(vertex.position) << " found to already exist at index " << existing_index);

                return existing_index;
            }
            else {
                // Create and store new vertex:

                auto new_vertex_data = vertex_to_data(vertex);
                vertices.insert(vertices.end(), new_vertex_data.begin(), new_vertex_data.end());

                auto index = vertex_count;
                vertex_count++;

                LOG_TRACE("Created new vertex " << util::coords_to_string(vertex.position) << " at index " << index);

                past_vertex_to_index.emplace(vertex, index);

                return index;
            }
        }

        virtual std::array<float, stride> vertex_to_data(const Vertex& vertex) = 0;

        std::vector<unsigned int> indices;

    private:
        unsigned int vertex_count = 0;

        std::vector<float> vertices;

        std::unordered_map<Vertex, unsigned int> past_vertex_to_index;
    };
}
