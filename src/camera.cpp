#include "camera.hpp"

#define DEFAULT_FOV 45.0f
#define DEFAULT_PITCH 0.0f
#define DEFAULT_YAW -90.0f
#define DEFAULT_FRONT glm::vec3(0.0f, 0.0f, -1.0f)

Camera::Camera(glm::vec3 position, glm::vec3 worldup, float aspect_ratio) : Camera(position, worldup, aspect_ratio, DEFAULT_FOV) {
}
Camera::Camera(glm::vec3 position, glm::vec3 worldup, float aspect_ratio, float FOV) : Camera(position, worldup, aspect_ratio, FOV, DEFAULT_PITCH, DEFAULT_YAW) {
}
Camera::Camera(glm::vec3 position, glm::vec3 worldup, float aspect_ratio, float FOV, float pitch, float yaw) : position(position), worldup(worldup), aspect_ratio(aspect_ratio), FOV(FOV), pitch(pitch), yaw(yaw), front(DEFAULT_FRONT) {
}

void Camera::update() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(direction);
}

void Camera::moveFront(float speed) {
    this->position += speed * this->front;
}
void Camera::moveBack(float speed) {
    this->position -= speed * this->front;
}
void Camera::moveLeft(float speed) {
    this->position += speed * glm::normalize(glm::cross(worldup, this->front));
}
void Camera::moveRight(float speed) {
    this->position -= speed * glm::normalize(glm::cross(worldup, this->front));
}

glm::mat4 Camera::getView() {
    return glm::lookAt(this->position, this->position + this->front, this->worldup);
}

glm::mat4 Camera::getProj() {
    return glm::perspective(glm::radians(this->FOV), this->aspect_ratio, 0.1f, 100.0f);
}