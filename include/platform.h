struct Platform
{
    SDL_Rect rect;
    Color color;
};

const int PLATFORM_TOP_LINE = 50;
const int PLATFORM_WIDTH = 100;
const int PLATFORM_HEIGHT = 10;
const Color PLATFORM_COLOR = {150, 150, 150, 255};

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void setPlatformSize(int width, int height);

    EMSCRIPTEN_KEEPALIVE
    void setPlatformPosition(int x, int y, bool fixX, bool fixY);

    EMSCRIPTEN_KEEPALIVE
    void setPlatformColor(Color color);
}

extern int getFieldWidth();
extern int getFieldHeight();

int getPlatformVerifiedPoint(int sizeField, int sizePlatform, int point);
SDL_Rect getPlatformRect();
void renderPlatform(SDL_Renderer *renderer);
Platform *initPlatform();
