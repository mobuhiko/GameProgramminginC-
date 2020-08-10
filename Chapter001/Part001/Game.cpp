#include <Game.h>

void Game::Initialze()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if(sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError);
        return false;
    }

    mWindow =
    SDL_CreteWindow(
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
        SDL_Log("Failed to create window: %s", SDL_GetErrot);
        return false;
    }

    return true;
}

void Game::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::RunLoop()
{
    while(mIsRunning)
    {
        ProcessInput();
        UpdatefGame();
        GenerateOutput();
    }
}
