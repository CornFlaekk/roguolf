#include <raylib.h>

class Ball{
    public:
        void update();
        void draw();
        void setSpeed(int p_speed);
        void setTexture(Texture p_texture);
    private:
        int x = 0;
        int y = 0;
        int speed = 5;
        int x_accel = 0;
        int y_accel = 0;
        Texture texture;
};