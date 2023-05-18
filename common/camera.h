#ifndef CAMERA_H_
#define CAMREA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace AFei
{
    class Camera
    {
        private:
            glm::vec3 _position;
            glm::vec3 _target;
            glm::vec3 _up;
            glm::vec3 _direction;
        
        public:
            bool is_keyboard_move;
            bool is_mouse_move;
            bool is_scroll;

        public:
            Camera();
            Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);
            Camera(AFei::Camera &obj);
        
        public:
            bool setPosition(glm::vec3 position);
            glm::vec3 getPosition();
            bool setTarget(glm::vec3 target);
            glm::vec3 getTarget();
            bool setUp(glm::vec3 up);
            glm::vec3 getUp();
            bool setDirection(glm::vec3 direction);
            glm::vec3 getDirection();
    };
}

#endif