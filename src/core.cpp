#include "basic.h"
#include "ball.h"
#include "border.h"
#include "bricks.h"
#include "field.h"
#include "platform.h"
#include "core.h"

Context gContext;

int valueInRange(int value, int min, int max)
{
    return (value >= min) && (value <= max);
}

int objectsOverlap(SDL_Rect *A, SDL_Rect *B)
{
    int xOverlap =
        valueInRange(A->x, B->x, B->x + B->w) || valueInRange(B->x, A->x, A->x + A->w);
    int yOverlap =
        valueInRange(A->y, B->y, B->y + B->h) || valueInRange(B->y, A->y, A->y + A->h);
    return xOverlap && yOverlap;
}

bool checkObjectMoving(SDL_Rect *A, SDL_Rect *B)
{
    SDL_Rect rBall = {};
    if (objectsOverlap(A, B))
    {
        rBall = getBallRect();
        rBall.x += getBallVelocityX();
        if (objectsOverlap(&rBall, B))
        {
            revBallVelocityX();
        }

        rBall = getBallRect();
        rBall.y += getBallVelocityY();
        if (objectsOverlap(&rBall, B))
        {
            revBallVelocityY();
        }

        A->x = rBall.x + getBallVelocityX();
        A->y = rBall.y + getBallVelocityY();
        return true;
    }
    return false;
}

void moveBall()
{
    SDL_Rect rBall = getBallRect();
    rBall.x += getBallVelocityX();
    rBall.y += getBallVelocityY();

    SDL_Rect wo = getPlatformRect();
    checkObjectMoving(&rBall, &wo);

    for (int i = 0; i < 4; i++)
    {
        SDL_Rect wo = getBorderRect(i);
        if (checkObjectMoving(&rBall, &wo) && getBorderStatus(i))
        {
            decLivesCount();
        }
    }

    int count = BRICKS_LINE_COUNT * BRICKS_ROWS;
    for (int i = 0; i < count; i++)
    {
        SDL_Rect wo = getBrickRect(i);
        if (getBrickStatus(i))
        {
            if (checkObjectMoving(&rBall, &wo))
            {
                setBrickStatus(i, false);
                incScoreCount();
                decActiveBricks();
                ;
            }
        }
    }

    setBallRect(rBall);
}

void mainloop(void *arg)
{
    SDL_Renderer *render = getGContextRender();
    renderField(render);
    renderBricks(render);
    renderBall(render);
    renderPlatform(render);
    renderBorders(render);
    if (getGameActive() && getActiveBricks() && getLivesCount())
    {
        moveBall();
    }
}

SDL_Renderer *getGContextRender()
{
    return gContext.renderer;
}

void runLoop()
{
    const int simulate_infinite_loop = 1;
    const int fps = -1;
    emscripten_set_main_loop_arg(mainloop, &gContext, fps, simulate_infinite_loop);
}

void renderWindow()
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(getFieldWidth(), getFieldHeight(), 0, &window, &renderer);
    gContext.renderer = renderer;
    gContext.window = window;
}

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void gameRestart()
    {
        setLivesCount(GAME_LIVES_COUNT);
        initBall();
        initBricks();
        setGameActive(false);
        setScoreCount(0);
    }

    EMSCRIPTEN_KEEPALIVE
    void gameStart()
    {
        setGameActive(true);
    }

    EMSCRIPTEN_KEEPALIVE
    void gameStop()
    {
        setGameActive(false);
    }

    EMSCRIPTEN_KEEPALIVE
    int getLivesCount()
    {
        return gContext.countLives;
    }

    EMSCRIPTEN_KEEPALIVE
    int getScoreCount()
    {
        return gContext.countScore;
    }
}

int decLivesCount()
{
    gContext.countLives--;
    setLivesCount(gContext.countLives);
    return gContext.countLives;
}

void setLivesCount(int lives)
{
    gContext.countLives = lives;
    char buffer[50];
    sprintf(buffer, "jsSetLives(%d);", lives);
    emscripten_run_script(buffer);
}

int incScoreCount()
{
    gContext.countScore++;
    setScoreCount(gContext.countScore);
    return gContext.countScore;
}

void setScoreCount(int score)
{
    gContext.countScore = score;
    char buffer[50];
    sprintf(buffer, "jsSetScore(%d);", score);
    emscripten_run_script(buffer);
}

bool getGameActive()
{
    return gContext.gameActive;
}

void setGameActive(bool status)
{
    gContext.gameActive = status;
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    initField();
    initPlatform();
    gameRestart();
    initBorders();
    renderWindow();
    runLoop();

    SDL_DestroyRenderer(gContext.renderer);
    SDL_DestroyWindow(gContext.window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
