#include "camera.h"

AFei::Camera::Camera()
{
    _position = glm::vec3(0.0f, 0.0f, 3.0f);
    _target = glm::vec3(0.0f, 0.0f, 2.0f);
    _up = glm::vec3(0.0f, 1.0f, 0.0f);
    _direction = glm::normalize(_target - _position);

    is_keyboard_move = false;
    is_mouse_move = false;
    is_scroll = false;
}

AFei::Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
    _position = position;
    _target = target;
    _up = up;
    _direction = glm::normalize(_target - _position);

    is_keyboard_move = false;
    is_mouse_move = false;
    is_scroll = false;
}

AFei::Camera::Camera(AFei::Camera &obj)
{
    _position = obj._position;
    _target = obj._target;
    _up = obj._up;
    _direction = obj._direction;

    is_keyboard_move = obj.is_keyboard_move;
    is_mouse_move = obj.is_mouse_move;
    is_scroll = obj.is_scroll;
}

// Error method
// bool AFei::Camera::setPosition(glm::vec3 position)
// {
//     bool res = false;
//     _position = position;
//     _direction = glm::normalize(_target - _position);
//     res = true;
//     return res;
// }

bool AFei::Camera::setPosition(glm::vec3 position)
{
    bool res = false;
    _position = position;
    _target += _direction;
    res = true;
    return res;
}

glm::vec3 AFei::Camera::getPosition()
{
    return _position;
}

bool AFei::Camera::setTarget(glm::vec3 target)
{
    bool res = false;
    _target = target;
    res = true;
    return res;
}

glm::vec3 AFei::Camera::getTarget()
{
    return _target;
}

bool AFei::Camera::setUp(glm::vec3 up)
{
    bool res = false;
    _up = up;
    res = true;
    return res;
}

glm::vec3 AFei::Camera::getUp()
{
    return _up;
}

bool AFei::Camera::setDirection(glm::vec3 direction)
{
    bool res = false;
    _direction = direction;
    _target = _direction + _position;
    res = true;
    return res;
}

glm::vec3 AFei::Camera::getDirection()
{
    return _direction;
}
