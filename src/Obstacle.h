#include <raylib.h>
#include <vector>

class Obstacle{
    public:
        void setTexture(Texture tex);
        void draw();
        void setPosition(int x, int y);
        void setPositionFromCenter(int x, int y);
        void clearPositions();
        void setTextureCollisionRectangle(Rectangle collision);
        std::vector<Rectangle> getOnScreenCollisionRectangles();
    private:
        std::vector<std::vector<int>> positions;
        Texture texture;
        std::vector<Rectangle> textureCollisionRectangles;
        std::vector<Rectangle> onScreenCollisionRectangles;
};