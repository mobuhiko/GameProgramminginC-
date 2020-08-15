#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game() :
    mWindow(nullptr),
    mIsRunning(true),
    mRenderer(nullptr),
    mTicksCount(0),
    mPaddleDir(0)
{
    ;
}

bool Game::Initialize()
{
    /* initialization of program */
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    /* initialize window */
    mWindow =
        SDL_CreateWindow(
            // window title
            "Game Programming in C++ (Chapter 1)",
            // top left x-coordinate of window
            100,
            // top left y-coordinate of window
            100,
            // width of window
            1024,
            // height of window
            768,
            // flags (0 for no flags set)
            0
        );

    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    /* initialize render */
    mRenderer =
        SDL_CreateRenderer(
            mWindow, // window to create renderer for
            -1, // usually -1
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );

    if (!mRenderer)
    {
        SDL_Log("Failed to create render: %s", SDL_GetError());
        return false;
    }

    /* initialize game objects */
    /* ball */
    mBallPos.x = 1024.0f / 2.0f;
    mBallPos.y = 768.0f / 2.0f;
    mBallVel.x = -200.0f;
    mBallVel.y = 235.0f;

    /* paddle */
    mPaddlePos.x = 10.0f;
    mPaddlePos.y = 768.0f / 2.0f;

    return true;
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::ProcessInput()
{
    /* keyboard input for exit */
    SDL_Event event;
    // while there are still events in the queue
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    // get state of keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // if escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }

    /* keyboard input for game objects*/
    /* paddle */
    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W]) // if move up
        mPaddleDir -= 1; // negative y
    if (state[SDL_SCANCODE_S]) // if move down
        mPaddleDir += 1; // positive y
}

void Game::UpdateGame()
{
    /* Game Time */
    // frame limiting
    // wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    // delta time is the difference in ticks from last frame
    // (converted to seconds)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    // clamp maximum delta time value
    if (deltaTime > 0.05f)
        deltaTime = 0.05f;
    // update tick counts for next frame
    mTicksCount = SDL_GetTicks();

    /* updating game objects */

    /*

    (0,0) is at the top left

    |--------------------------> x
    |(0,0) (1,0) (2,0) (3,0)
    |(0,1) (1,1) (2,1) (3,1)
    |(0,2) (1,2) (2,2) (3,2)
    |(0,3) (1,3) (2,3) (3,3)
    |
    V
    y

    */

    /* paddle */
    if (mPaddleDir != 0)
    {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
        // make sure paddle does not move off screen
        if (mPaddlePos.y < (paddleH / 2.0f + thickness))
            mPaddlePos.y = paddleH / 2.0f + thickness;
        else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
            mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
    }

    /* ball */
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;

    /* collision */
    /* ball & wall */
    // (1) if collides with the wall
    // (2) avoid keep stucking with the top wall
    if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
        mBallVel.y *= -1;
    // the ball collide with the bottom wall?
    else if (mBallPos.y >= (768 - thickness) && mBallVel.y > 0.0f)
        mBallVel.y *= -1;
    // Did the ball collide with the right wall?
    else if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
        mBallVel.x *= -1.0f;

    /* ball & paddle */
    float diff = mPaddlePos.y - mBallPos.y;
    if (diff < 0.0f)
        diff = -diff;
    else
        diff = diff;

    if (
        // y-diff is small enough
        diff <= paddleH / 2.0f &&
        // ball is at the correct x-position
        mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
        // the ball is moving to the left
        mBallVel.x < 0.0f
        )
    {
        mBallVel.x *= -1.0f;
    }
    // Did the ball go off the screen? (if so, end game)
    else if (mBallPos.x <= 0.0f)
    {
        mIsRunning = false;
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        0, // R
        0, // G
        255, // B
        255 // A
        // (0,0,255,255) is blue
    );

    // clear back buffer
    SDL_RenderClear(mRenderer);

    /* draw entire game scene */

    // color the top wall
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255); // white color
    // draw the top wall
    SDL_Rect top_wall
    {
        0, // top left x
        0, // top left y
        1024, // width
        thickness // height
    };
    SDL_RenderFillRect(mRenderer, &top_wall); // fill the rectangle with the color

    // color the bottom wall
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255); // white color
    // draw the bottom wall
    SDL_Rect bottom_wall
    {
        0, // x
        768 - thickness, // y
        1024, // width
        thickness // height
    };
    SDL_RenderFillRect(mRenderer, &bottom_wall); // fill the rectangle with the color

    // draw the right wall
    SDL_Rect right_wall
    {
        1024 - thickness, // x
        0, // y
        thickness, // width
        1024 // height
    };
    SDL_RenderFillRect(mRenderer, &right_wall); // fill the rectangle with the color

    // draw the ball
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 0); // yellow
    SDL_Rect ball
    {
        static_cast<int>(mBallPos.x - thickness / 2),
        static_cast<int>(mBallPos.y - thickness / 2),
        thickness,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &ball);

    // draw the paddle
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 0); // red
    SDL_Rect paddle
    {
        static_cast<int>(mPaddlePos.x),
        static_cast<int>(mPaddlePos.y - paddleH / 2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(mRenderer, &paddle);

    // swap front buffer and back buffer
    SDL_RenderPresent(mRenderer);
}
