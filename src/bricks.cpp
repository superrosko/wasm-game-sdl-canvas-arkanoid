#include "basic.h"
#include "bricks.h"

Bricks gBricks;

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void setBricksCount(int rowCount, int lineCount)
    {
        gBricks.rowCount = rowCount;
        gBricks.lineCount = lineCount;
    }

    EMSCRIPTEN_KEEPALIVE
    void setBricksColor(Color color)
    {
        gBricks.color = color;
    }
}

void setBricksSize()
{
    gBricks.width = (int)((getFieldWidth() - 2 * BRICKS_PADDING + BRICKS_SPACE) / gBricks.lineCount) - BRICKS_SPACE;
    gBricks.height = BRICKS_HEIGHT;
}

void setBrickStatus(int number, bool status)
{
    gBricks.brick[number].status = status;
}

bool getBrickStatus(int number)
{
    return gBricks.brick[number].status;
}

int getActiveBricks()
{
    return gBricks.countActiveBricks;
}

int incActiveBricks()
{
    gBricks.countActiveBricks++;
    return gBricks.countActiveBricks;
}

int decActiveBricks()
{
    gBricks.countActiveBricks--;
    return gBricks.countActiveBricks;
}

SDL_Rect getBrickRect(int number)
{
    return gBricks.brick[number].rect;
}

void renderBricks(SDL_Renderer *renderer)
{
    for (int i = 0; i < gBricks.countAllBricks; i++)
    {
        if (getBrickStatus(i))
        {
            SDL_SetRenderDrawColor(renderer, gBricks.color.r, gBricks.color.g, gBricks.color.b, gBricks.color.a);
            SDL_RenderFillRect(renderer, &(gBricks.brick[i].rect));
            SDL_RenderPresent(renderer);
        }
    }
}

Bricks *initBricks()
{
    gBricks.countAllBricks = BRICKS_LINE_COUNT * BRICKS_ROWS;
    gBricks.countActiveBricks = gBricks.countAllBricks;

    setBricksCount(BRICKS_ROWS, BRICKS_LINE_COUNT);
    setBricksSize();
    setBricksColor(BRICKS_COLOR);

    gBricks.brick = new Brick[gBricks.countAllBricks];
    for (int i = 0; i < BRICKS_ROWS; i++)
    {
        for (int j = 0; j < BRICKS_LINE_COUNT; j++)
        {
            SDL_Rect r;
            r.x = BRICKS_PADDING + (BRICKS_SPACE + gBricks.width) * j;
            r.y = BRICKS_PADDING + (BRICKS_SPACE + gBricks.height) * i;
            r.w = gBricks.width;
            r.h = gBricks.height;
            gBricks.brick[i * BRICKS_LINE_COUNT + j].status = true;
            gBricks.brick[i * BRICKS_LINE_COUNT + j].rect = r;
        }
    }

    return &gBricks;
}
