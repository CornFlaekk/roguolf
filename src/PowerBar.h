#include <raylib.h>

class PowerBar{
    public:
        void draw(float ball_accel, float ball_accel_preview);
        void setEmptyTexture(Texture tex);
        void setColorsTexture(Texture tex);
        int getHeight();
    private:
        Texture empty_texture;
        Texture colors_texture;
};