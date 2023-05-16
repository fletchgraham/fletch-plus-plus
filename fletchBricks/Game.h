
#pragma once
#include "SDL2/SDL.h"

struct Vec2
{
    float x;
    float y;
};

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
	
	// Direction of paddle
	int mPaddleDir;
	// Position of paddle
	Vec2 mPaddlePos;
	// Position of ball
	Vec2 mBallPos;
	// Velocity of ball
	Vec2 mBallVel;
};