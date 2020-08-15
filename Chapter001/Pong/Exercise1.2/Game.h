#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include <iostream>
#include <vector>

struct Vector2
{
    float x;
    float y;
};

struct Ball
{
    // ball movement
    Vector2 mBallPos;
    Vector2 mBallVel; // velocity
};
/*
mBall0.mBallPos.x = 1024.0f / 2.0f;
mBall0.mBallPos.y = 768.0f / 2.0f;
mBall0.mBallVel.x = -200.0f;
mBall0.mBallVel.y = 235.0f;
*/

//Ball ball0 = { {1024.0f / 2.0f, 768.0f / 2.0f},{-200.0f,235.0f} };

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

    // paddle1 movement
    Vector2 mPaddle1Pos;
    int mPaddle1Dir; // direction

    // paddle2 movement
    Vector2 mPaddle2Pos;
    int mPaddle2Dir; // direction

    // ball
    Ball mBall0 = { {1024.0f / 2.0f, 768.0f / 2.0f},{-200.0f,235.0f} };
    std::vector<Ball> mBall;
};

#endif // GAME_H_INCLUDED
