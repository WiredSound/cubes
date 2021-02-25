#pragma once

#include <glm/glm.hpp>

enum class Direction { Forward, Backward, Left, Right };

class Camera {
public:
    Camera(float fov = 90.0f, float near = 0.001f, float far = 1000.0f);
    const glm::mat4& get_projection_matrix() const;
    glm::mat4 get_view_matrix() const;
    void move_towards(Direction d, float delta);
    void rotate(float xchange, float ychange);

private: 
    void update_vectors();

    glm::mat4 projection;
    glm::vec3 position, front, up, right;
    const glm::vec3 world_up;
    float yaw = -90.0f, pitch = 0.0f;
};
