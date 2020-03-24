struct Field
{
    int width;
    int height;
    Color color;
};

const int FIELD_WIDTH = 420;
const int FIELD_HEIGHT = 600;
const Color FIELD_COLOR = {1, 41, 95, 255};

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void setFieldSize(int width, int height);

    EMSCRIPTEN_KEEPALIVE
    void setFieldColor(Color color);
}

int getFieldWidth();
int getFieldHeight();
void renderField(SDL_Renderer *renderer);
Field *initField();