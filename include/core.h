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

    EMSCRIPTEN_KEEPALIVE
    void jsSetScore(int score);

    EMSCRIPTEN_KEEPALIVE
    void jsSetLives(int lives);
}

SDL_Renderer *getGContextRender();
int decLivesCount();
void setLivesCount(int lives);
int incScoreCount();
void setScoreCount(int score);
bool getGameActive();
void setGameActive(bool status);