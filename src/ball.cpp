#include "basic.h"
#include "ball.h"

Ball gBall;

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void setBallSize(int width, int height)
    {
        gBall.rect.w = width;
        gBall.rect.h = height;
    }

    EMSCRIPTEN_KEEPALIVE
    void setBallPosition(int x, int y)
    {
        gBall.rect.x = getBallVerifiedPoint(getFieldWidth(), gBall.rect.w, x);
        gBall.rect.y = getBallVerifiedPoint(getFieldHeight(), gBall.rect.h, y);
    }

    EMSCRIPTEN_KEEPALIVE
    void setBallColor(Color color)
    {
        gBall.color = color;
    }

    EMSCRIPTEN_KEEPALIVE
    void setRndBallPosition()
    {
        srand(time(NULL));
        int x = rand() % (getFieldWidth() - BALL_SPAWN_LINE_WPADDING) + BALL_SPAWN_LINE_WPADDING / 2;
        int y = rand() % BALL_SPAWN_LINE + getFieldHeight() / 2 - gBall.rect.h;
        setBallPosition(x, y);
    }

    EMSCRIPTEN_KEEPALIVE
    void setBallVelocity(int velocityX, int velocityY)
    {
        gBall.velocityX = velocityX;
        gBall.velocityY = velocityY;
    }
}

int getBallVerifiedPoint(int sizeField, int sizeBall, int point)
{
    if (sizeField < (point + sizeBall))
    {
        return sizeField - sizeBall;
    }
    if (point < 0)
    {
        return 0;
    }
    return point;
}

int getBallVelocityX()
{
    return gBall.velocityX;
}

int revBallVelocityX()
{
    return gBall.velocityX *= -1;
}

int getBallVelocityY()
{
    return gBall.velocityY;
}

int revBallVelocityY()
{
    return gBall.velocityY *= -1;
}

void setBallRect(SDL_Rect rect)
{
    gBall.rect = rect;
}

SDL_Rect getBallRect()
{
    return gBall.rect;
}

void renderBall(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, gBall.color.r, gBall.color.g, gBall.color.b, gBall.color.a);
    SDL_RenderFillRect(renderer, &gBall.rect);
    SDL_RenderPresent(renderer);
}

Ball *initBall()
{
    setBallVelocity(BALL_VELOCITY_X, BALL_VELOCITY_Y);
    setBallSize(BALL_WIDTH, BALL_HEIGHT);
    setBallColor(BALL_COLOR);
    setRndBallPosition();
    return &gBall;
}
