#pragma once

#include <glm/glm.hpp>

namespace util {
    enum class Direction : unsigned char { Forward, Backward, Left, Right, Up, Down };

    class Camera {
    public:
        Camera(
            float forward_backward_speed = 2.0f, float strafe_speed = 1.8f, float vertical_speed = 1.0f,
            float look_speed = 1000.0f, bool lock_y = true, float fov = 90.0f, float near = 0.001f, float far = 1000.0f
        );

        const glm::mat4& get_projection_matrix() const;
        glm::mat4 get_view_matrix() const;

        void move_towards(Direction d, float delta);
        void rotate(float xchange, float ychange);

    private: 
        void update_vectors();

        const float forward_backward_speed, strafe_speed, vertical_speed, look_speed;
        const bool lock_y;

        glm::mat4 projection;
        glm::vec3 position, front, up, right;
        const glm::vec3 world_up;
        float yaw = -90.0f, pitch = 0.0f;
    };
}
