#include "basic.h"
#include "field.h"

Field gField;

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void setFieldSize(int width, int height)
    {
        gField.width = width;
        gField.height = height;
    }

    EMSCRIPTEN_KEEPALIVE
    void setFieldColor(Color color)
    {
        gField.color = color;
    }
}

int getFieldWidth()
{
    return gField.width;
}

int getFieldHeight()
{
    return gField.height;
}

void renderField(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, gField.color.r, gField.color.g, gField.color.b, gField.color.a);
    SDL_RenderClear(renderer);
}

Field *initField()
{
    setFieldSize(FIELD_WIDTH, FIELD_HEIGHT);
    setFieldColor(FIELD_COLOR);
    return &gField;
}