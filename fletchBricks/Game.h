
#pragma once
#include "SDL2/SDL.h"
#include "ball.cpp"
#include "paddle.cpp"
#include "brick.cpp"


class Game
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
    int windowWidth;
    int windowHeight;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	
	Paddle paddle;
	Ball ball;
	Brick bricks[5];
};
