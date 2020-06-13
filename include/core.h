struct Context
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    int countLives;
    int countScore;
    int gameActive;
};

const int GAME_LIVES_COUNT = 5;

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void gameRestart();

    EMSCRIPTEN_KEEPALIVE
    void gameStart();

    EMSCRIPTEN_KEEPALIVE
    void gameStop();

    EMSCRIPTEN_KEEPALIVE
    int getLivesCount();

    EMSCRIPTEN_KEEPALIVE
    int getScoreCount();
}

int valueInRange(int value, int min, int max);
int objectsOverlap(SDL_Rect *A, SDL_Rect *B);
bool checkObjectMoving(SDL_Rect *A, SDL_Rect *B);
void moveBall();
void mainloop(void *arg);
SDL_Renderer *getGContextRender();
void runLoop();
void renderWindow();
int decLivesCount();
void setLivesCount(int lives);
int incScoreCount();
void setScoreCount(int score);
bool getGameActive();
void setGameActive(bool status);
