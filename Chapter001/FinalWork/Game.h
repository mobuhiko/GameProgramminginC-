#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>

struct Vector2
{
    float x;
    float y;
};

class Game
{
public:
    Game();
    bool Initialize(); // initialize the game
    void RunLoop(); // runs the game loop until the game is over
    void Shutdown(); // shutdown the game
private:
    // helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // window created by SDL
    SDL_Window* mWindow;

    // game should continue to run
    bool mIsRunning;

    // render
    SDL_Renderer* mRenderer;

    // game time
    Uint32 mTicksCount;

    // paddle movement
    Vector2 mPaddlePos;
    int mPaddleDir; // direction
    
    // ball movement
    Vector2 mBallPos;
    Vector2 mBallvel; // velocity
};
#endif // GAME_H_INCLUDED
