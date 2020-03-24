struct Border
{
    bool status;
    SDL_Rect rect;
};

struct Borders
{
    Border *border;
    Color color;
};

const int BORDER_SIZE = 10;
const Color BORDER_COLOR = {181, 112, 61, 255};

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void setBorderColor(Color color);
}

extern int getFieldWidth();
extern int getFieldHeight();

bool getBorderStatus(int number);
SDL_Rect getBorderRect(int number);
void renderBorders(SDL_Renderer *renderer);
Borders *initBorders();