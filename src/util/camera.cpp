#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

#include "util/camera.hpp"

namespace util {
    Camera::Camera(float move_speed, float look_speed, float fov, float near, float far) :
        move_speed(move_speed), look_speed(look_speed),
        projection(glm::perspective(glm::radians(fov), 800.0f / 600.0f, near, far)),
        position(0.0f, 0.0f, 0.0f), world_up(0.0f, 1.0f, 0.0f) {
        update_vectors();
    }

    const glm::mat4& Camera::get_projection_matrix() const {
        return projection;
    }

    glm::mat4 Camera::get_view_matrix() const {
        return glm::lookAt(
            position, // camera position
            position + front, // direction the camera is facing
            up // up relative to camera rotations
        );
    }

    void Camera::move_towards(Direction d, float delta) {
        float movement = move_speed * delta;

        switch(d) {
        case Direction::Forward:
            position += front * movement;
            break;
        case Direction::Backward:
            position -= front * movement;
            break;
        case Direction::Left:
            position -= right * movement;
            break;
        case Direction::Right:
            position += right * movement;
            break;
        }
    }

    void Camera::rotate(float xchange, float ychange) {
        yaw += xchange * look_speed;
        pitch += ychange * look_speed;
        pitch = std::clamp(pitch, -89.0f, 89.0f);

        update_vectors();
    }

    void Camera::update_vectors() {
        // Calculate a new front vector based on Euler angles:

        float yaw_rad = glm::radians(yaw);
        float pitch_rad = glm::radians(pitch);

        glm::vec3 new_front(
            glm::cos(yaw_rad) * glm::cos(pitch_rad),
            glm::sin(pitch_rad),
            glm::sin(yaw_rad) * glm::cos(pitch_rad)
        );

        front = glm::normalize(new_front);

        // Recalculate right and up vectors based on new front vector:

        right = glm::normalize(glm::cross(front, world_up));
        up = glm::normalize(glm::cross(right, front));
    }
}
