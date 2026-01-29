#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera {
    private:
        glm::vec3 front;
        glm::vec3 worldup;
        float aspect_ratio;
        
        public:
        glm::vec3 position;
        float FOV;
        float pitch;
        float yaw;

        Camera(glm::vec3 position, glm::vec3 worldup, float aspect_ratio);
        Camera(glm::vec3 position, glm::vec3 worldup, float aspect_ratio, float FOV);
        Camera(glm::vec3 position, glm::vec3 worldup, float aspect_ratio, float FOV, float pitch, float yaw);

        void update();
        
        void moveFront(float speed);
        void moveBack(float speed);
        void moveLeft(float speed);
        void moveRight(float speed);

        glm::mat4 getView();
        glm::mat4 getProj();
};

#endif