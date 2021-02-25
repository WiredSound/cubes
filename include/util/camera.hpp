#pragma once

#include <glm/glm.hpp>

namespace util {
    enum class Direction { Forward, Backward, Left, Right };

    class Camera {
    public:
        Camera(float move_speed = 2.0f, float look_speed = 1000.0f, float fov = 90.0f, float near = 0.001f, float far = 1000.0f);
        const glm::mat4& get_projection_matrix() const;
        glm::mat4 get_view_matrix() const;
        void move_towards(Direction d, float delta);
        void rotate(float xchange, float ychange);

    private: 
        void update_vectors();

        const float move_speed, look_speed;

        glm::mat4 projection;
        glm::vec3 position, front, up, right;
        const glm::vec3 world_up;
        float yaw = -90.0f, pitch = 0.0f;
    };
}
