#include "basic.h"
#include "platform.h"

Platform gPlatform;

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void setPlatformSize(int width, int height)
    {
        gPlatform.rect.w = width;
        gPlatform.rect.h = height;
    }

    EMSCRIPTEN_KEEPALIVE
    void setPlatformPosition(int x, int y, bool fixX = true, bool fixY = true)
    {
        if (!fixX)
        {
            gPlatform.rect.x = getPlatformVerifiedPoint(getFieldWidth(), gPlatform.rect.w, x);
        }

        if (!fixY)
        {
            gPlatform.rect.y = getPlatformVerifiedPoint(getFieldHeight(), gPlatform.rect.h, y);
        }
    }

    EMSCRIPTEN_KEEPALIVE
    void setPlatformColor(Color color)
    {
        gPlatform.color = color;
    }
}

int getPlatformVerifiedPoint(int sizeField, int sizePlatform, int point)
{
    point -= sizePlatform / 2;
    if (sizeField < (point + sizePlatform))
    {
        return sizeField - sizePlatform;
    }
    if (point < 0)
    {
        return 0;
    }
    return point;
}

SDL_Rect getPlatformRect()
{
    return gPlatform.rect;
}

void renderPlatform(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, gPlatform.color.r, gPlatform.color.g, gPlatform.color.b, gPlatform.color.a);
    SDL_RenderFillRect(renderer, &gPlatform.rect);
    SDL_RenderPresent(renderer);
}

Platform *initPlatform()
{
    setPlatformSize(PLATFORM_WIDTH, PLATFORM_HEIGHT);
    setPlatformColor(PLATFORM_COLOR);
    setPlatformPosition(getFieldWidth() / 2, getFieldHeight() - PLATFORM_TOP_LINE, false, false);
    return &gPlatform;
}
