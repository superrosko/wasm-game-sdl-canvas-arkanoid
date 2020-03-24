struct Ball
{
    int velocityX;
    int velocityY;
    SDL_Rect rect;
    Color color;
};

const int BALL_SPAWN_LINE_WPADDING = 20;
const int BALL_SPAWN_LINE = 40;
const int BALL_WIDTH = 10;
const int BALL_HEIGHT = 10;
const int BALL_VELOCITY_X = 5;
const int BALL_VELOCITY_Y = 5;
const Color BALL_COLOR = {253, 21, 27, 255};

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void setBallSize(int width, int height);

    EMSCRIPTEN_KEEPALIVE
    void setBallPosition(int x, int y);

    EMSCRIPTEN_KEEPALIVE
    void setBallColor(Color color);

    EMSCRIPTEN_KEEPALIVE
    void setRndBallPosition();

    EMSCRIPTEN_KEEPALIVE
    void setBallVelocity(int velocityX, int velocityY);
}

extern int getFieldWidth();
extern int getFieldHeight();

int getBallVerifiedPoint(int sizeField, int sizeBall, int point);
int getBallVelocityX();
int revBallVelocityX();
int getBallVelocityY();
int revBallVelocityY();
void setBallRect(SDL_Rect rect);
SDL_Rect getBallRect();
void renderBall(SDL_Renderer *renderer);
Ball *initBall();