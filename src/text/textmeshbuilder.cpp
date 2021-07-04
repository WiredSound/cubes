#include "text/textmeshbuilder.hpp"
#include "util/coords.hpp"

namespace text {
    TextMeshBuilder::TextMeshBuilder(
        const std::string& text, int window_width, int window_height, unsigned int image_width_pixels,
        unsigned int image_height_pixels, unsigned int char_width_pixels, unsigned int char_height_pixels,
        unsigned int chars_per_row, float draw_scale_factor
    ) {
        float x_draw_position = 0.0;

        const float char_draw_width = (static_cast<float>(char_width_pixels) * draw_scale_factor / static_cast<float>(window_width)),
                    char_draw_height = (static_cast<float>(char_height_pixels) * draw_scale_factor / static_cast<float>(window_height));

        const float char_texture_width = static_cast<float>(char_width_pixels) / static_cast<float>(image_width_pixels),
                    char_texture_height = static_cast<float>(char_height_pixels) / static_cast<float>(image_height_pixels);

        for(const char& character : text) {
            auto ascii_code = static_cast<unsigned int>(character);
            // Subtract 32 (or set to 0 if outside correct bounds) as first 32 ASCII characters are non-printable:
            auto char_offset = ascii_code < 32 || ascii_code > 127 ? 0 : ascii_code - 32;

            // Calculate the pixel coordinates of the required character:
            auto char_texture_x_pixels = char_offset % chars_per_row * char_width_pixels;
            auto char_texture_y_pixels = image_height_pixels - (char_offset / chars_per_row + 1) * char_height_pixels;

            // Calculate the position of the required character relative to the size of the font image:
            auto char_texture_x = static_cast<float>(char_texture_x_pixels) / static_cast<float>(image_width_pixels);
            auto char_texture_y = static_cast<float>(char_texture_y_pixels) / static_cast<float>(image_height_pixels);

            auto bottom_left = require_vertex(util::Position2Texel2 {
                glm::vec2(x_draw_position, 0.0),
                glm::vec2(char_texture_x, char_texture_y)
            });
            auto bottom_right = require_vertex(util::Position2Texel2 {
                glm::vec2(x_draw_position + char_draw_width, 0.0),
                glm::vec2(char_texture_x + char_texture_width, char_texture_y)
            });
            auto top_left = require_vertex(util::Position2Texel2 {
                glm::vec2(x_draw_position, char_draw_height),
                glm::vec2(char_texture_x, char_texture_y + char_texture_height)
            });
            auto top_right = require_vertex(util::Position2Texel2 {
                glm::vec2(x_draw_position + char_draw_width, char_draw_height),
                glm::vec2(char_texture_x + char_texture_width, char_texture_y + char_texture_height)
            });

            unsigned int new_vertices[] = {
                top_right, bottom_right, top_left,
                bottom_right, bottom_left, top_left
            };
            add_indices(new_vertices);

            x_draw_position += char_draw_width;
        }
    }

    std::string TextMeshBuilder::vertex_to_string(const util::Position2Texel2& vertex) {
        return "pos: " + util::coords_to_string(vertex.position) + " texel: " + util::coords_to_string(vertex.texture_coords);
    }


    std::array<float, 4> TextMeshBuilder::vertex_to_data(const util::Position2Texel2& vertex) {
        return {
            vertex.position.x, vertex.position.y,
            vertex.texture_coords.x, vertex.texture_coords.y
        };
    }
}
