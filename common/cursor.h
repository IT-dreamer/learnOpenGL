#ifndef CURSOR_H_
#define CURSOR_H_

namespace AFei
{
    class Cursor
    {
        private:
            float _x;
            float _y;
        
        public:
            float cursorSpeed;
        
        public:
            Cursor();
        
        public:
            bool setX(float x);
            float getX();
            bool setY(float y);
            float getY();
    };
}

#endif