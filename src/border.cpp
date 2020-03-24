#include "basic.h"
#include "border.h"

Borders gBorders;

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void setBorderColor(Color color)
    {
        gBorders.color = color;
    }
}

bool getBorderStatus(int number)
{
    return gBorders.border[number].status;
}

SDL_Rect getBorderRect(int number)
{
    return gBorders.border[number].rect;
}

void renderBorders(SDL_Renderer *renderer)
{
    for (int i = 0; i < 4; i++)
    {
        SDL_SetRenderDrawColor(renderer, gBorders.color.r, gBorders.color.g, gBorders.color.b, gBorders.color.a);
        SDL_RenderFillRect(renderer, &(gBorders.border[i].rect));
        SDL_RenderPresent(renderer);
    }
}

Borders *initBorders()
{
    setBorderColor(BORDER_COLOR);
    int fieldSizeW = getFieldWidth();
    int fieldSizeH = getFieldHeight();

    gBorders.border = new Border[4];
    gBorders.border[0].rect = {0, 0, BORDER_SIZE, fieldSizeH};
    gBorders.border[1].rect = {fieldSizeW - BORDER_SIZE, 0, BORDER_SIZE, fieldSizeH};
    gBorders.border[2].rect = {0, 0, fieldSizeW, BORDER_SIZE};
    gBorders.border[3].rect = {0, fieldSizeH - BORDER_SIZE, fieldSizeW, BORDER_SIZE};

    gBorders.border[0].status = false;
    gBorders.border[1].status = false;
    gBorders.border[2].status = false;
    gBorders.border[3].status = true;

    return &gBorders;
}