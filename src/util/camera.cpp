#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

#include "util/camera.hpp"

namespace util {
    Camera::Camera(
        float forward_backward_speed, float strafe_speed, float vertical_speed, float look_speed, bool lock_y,
        float fov, float near, float far
    ) : forward_backward_speed(forward_backward_speed), strafe_speed(strafe_speed), vertical_speed(vertical_speed),
        look_speed(look_speed), lock_y(lock_y),
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
        float forward_backward_movement = forward_backward_speed * delta,
              strafe_movement = strafe_speed * delta,
              vertical_movement = vertical_speed * delta;

        float y = position.y;

        switch(d) {
        case Direction::Forward:
            position += front * forward_backward_movement;
            break;
        case Direction::Backward:
            position -= front * forward_backward_movement;
            break;
        case Direction::Left:
            position -= right * strafe_movement;
            break;
        case Direction::Right:
            position += right * strafe_movement;
            break;
        default: break;
        }

        switch(d) {
        case Direction::Up:
            position += world_up * vertical_movement;
            break;
        case Direction::Down:
            position -= world_up * vertical_movement;
            break;
        default:
            if(lock_y) position.y = y;
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
