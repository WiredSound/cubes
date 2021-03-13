#pragma once

#include "gfx/mesh.hpp"

namespace text {
    class TextMesh : public gfx::Mesh {
    public:
        TextMesh();

    private:
        void prepare_attributes(std::size_t stride) override;
    };
}
