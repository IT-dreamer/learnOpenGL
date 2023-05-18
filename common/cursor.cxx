#include "cursor.h"

AFei::Cursor::Cursor()
{
    _x = 0.0f;
    _y = 0.0f;
    cursorSpeed = 0.05f;
}

bool AFei::Cursor::setX(float x)
{
    bool res = false;
    _x = x;
    res = true;
    return res;
}

float AFei::Cursor::getX()
{
    return _x;
}

bool AFei::Cursor::setY(float y)
{
    bool res = false;
    _y = y;
    res = true;
    return res;
}

float AFei::Cursor::getY()
{
    return _y;
}