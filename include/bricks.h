struct Brick
{
    bool status;
    SDL_Rect rect;
};

struct Bricks
{
    int rowCount;
    int lineCount;
    int width;
    int height;
    int countAllBricks;
    int countActiveBricks;
    Brick *brick;
    Color color;
};

const int BRICKS_LINE_COUNT = 6;
const int BRICKS_ROWS = 10;
const int BRICKS_PADDING = 30;
const int BRICKS_SPACE = 10;
const int BRICKS_HEIGHT = 10;
const Color BRICKS_COLOR = {255, 179, 15, 255};

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void setBricksCount(int rowCount, int lineCount);

    EMSCRIPTEN_KEEPALIVE
    void setBricksColor(Color color);
}

extern int getFieldWidth();
extern int getFieldHeight();

void setBrickStatus(int number, bool status);
bool getBrickStatus(int number);
int getActiveBricks();
int incActiveBricks();
int decActiveBricks();
SDL_Rect getBrickRect(int number);
void renderBricks(SDL_Renderer *renderer);
Bricks *initBricks();
