#include <raylib.h>
#include <vector>

class Enemy{
    public:
        void setTexture(Texture tex);
        void draw();
        void animate(int i);
        void setPosition(int x, int y);
        void clearPositions();
        void setTextureCollisionRectangle(Rectangle collision);
        std::vector<Rectangle> getOnScreenCollisionRectangles();
        void setLife(int val);
        int getLife();
        void hit(int damage);
    private:
        std::vector<std::vector<int>> positions;
        Texture texture;
        std::vector<Rectangle> textureCollisionRectangles;
        std::vector<Rectangle> onScreenCollisionRectangles;
};