#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>

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
    SDL_Renderer* mRenderer;
};
#endif // GAME_H_INCLUDED
