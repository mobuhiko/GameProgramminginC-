#include <game.h>

void Game::Initialze()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if(sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow =
    SDL_CreateWindow
    (
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

    if(!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    return true;

    mRender =
    SDL_CreateRenderer
    (
        mWindow, // window to create renderer for
        -1, // usually -1
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if(!mRenderer)
    {
        SDL_Log("Failed to create render: %s", SDL_GetError());
        return false;
    }

}

void Game::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::RunLoop()
{
    while(mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    // while there are still events in the queue
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    // get state of keyboard
    // const Uint8*
    const uint8_t* state = SDL_GetKeyboardState(NULL);
    // if escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

Game::GenerateOutput()
{
    SDL_SetRenderDrawColor
    (
        mRenderer,
        0, // R
        0, // G
        255, // B
        255 // A
    );

    SDL_RenderClear(mRenderer);

    // draw entire game scene

    SDL_RenderPresent(mRenderer);
}
