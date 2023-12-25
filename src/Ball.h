#include <raylib.h>
#include <vector>

class Ball{
    public:
        const int radius = 8;
        void update();
        void draw();
        void calcAnimation();
        void drawGuidingCircles();
        void calcAccelPreview();
        void setX(int val);
        void setY(int val);
        void setSpeed(int p_speed);
        void setTexture(Texture p_texture);
        void setPowerBarHeight(int value);
        void setMaxAccel();
        float getPreviewAccel();
        float getAccel();
        void invertAccelX();
        void invertAccelY();
        Vector2 getCenter();
        int getDamage();
    private:
        int MAX_ACCEL_X;
        int MAX_ACCEL_Y;
        int x = 0;
        int y = 0;
        int speed = 5;
        int x_accel_preview = 0;
        int y_accel_preview = 0;
        int x_accel = 0;
        int y_accel = 0;
        int powerbar_height = 0;

        int damage = 1;

        int animation_id = 0;
        int animation_frame = 0;
        const static int MAX_ANIMATIONS = 15;
        std::vector<double> distance_multipliers;
        Texture texture;
};