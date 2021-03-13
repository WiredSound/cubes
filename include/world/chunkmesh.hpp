#pragma once

#include "gfx/mesh.hpp"

namespace world {
    class ChunkMesh : public gfx::Mesh {
    public:
        ChunkMesh();

    private:
        void prepare_attributes(std::size_t stride) override;
    };
}
