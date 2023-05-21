#include "Game.h"

const int thickness = 15;
const float paddleW = 100.0f;

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
{
	
}

bool Game::Initialize()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
    
    windowWidth = 640;
    windowHeight = 480;
	
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Fletch Bricks",
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		windowWidth,
		windowHeight,
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	//


	paddle.pos.x = windowWidth / 2.0f;
	paddle.pos.y = windowHeight - 30.0f;
	paddle.leftLimit = thickness;
	paddle.rightLimit = windowWidth - thickness;

	ball.radius = thickness / 2;
	ball.pos.x = windowWidth/2.0f;
	ball.pos.y = windowHeight/2.0f;
	ball.vel.x = 0.0f;
	ball.vel.y = 200.0f;

	float courtWidth = windowWidth - thickness * 2;
	float topEdge = thickness;
	float leftEdge = thickness;
	float brickGap = 20.0f;
	int numRows = 3;
	int maxBricksPerRow = 5;

	int numBricks;
	int bricksInTwoRows = maxBricksPerRow * 2 - 1;

	if (numRows % 2 == 0) {
		numBricks = numRows / 2 * bricksInTwoRows;
	} else {
		numBricks = (numRows - 1) / 2 * bricksInTwoRows + maxBricksPerRow;
	}

	float brickWidth = (courtWidth - brickGap * (maxBricksPerRow + 1)) / maxBricksPerRow;
	float brickHeight = 50.0f;

	float startY = topEdge + brickGap + brickHeight / 2;
	float startX = leftEdge + brickGap + brickWidth / 2;
	int curBrickIndex = 0;
	float nudge;
	int bricksPerRow;
	for (int rowIndex=0; rowIndex < numRows; rowIndex++) { 
		nudge = 0;
		bricksPerRow = maxBricksPerRow;
		if (rowIndex % 2 != 0) { // odd
			bricksPerRow = maxBricksPerRow - 1;
			nudge = (brickWidth + brickGap) / 2;
		}

		for (int localBrickIndex = 0; localBrickIndex < bricksPerRow; localBrickIndex++) {
			float posX = startX + nudge + localBrickIndex * (brickGap + brickWidth);
			float posY = startY + rowIndex * (brickGap + brickHeight);

			bricks[curBrickIndex].pos.x = posX;
			bricks[curBrickIndex].pos.y = posY;
			bricks[curBrickIndex].w = brickWidth;
			bricks[curBrickIndex].h = brickHeight;
			bricks[curBrickIndex].hitRadius = ball.radius;
			curBrickIndex += 1;
		}
	}

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

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	SDL_GetMouseState(&mouseX, &mouseY);

}

void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	
	paddle.Update(mouseX);
	ball.Update(deltaTime);

	paddle.HandleBall(ball);

	bool allBroken = true;
	for (Brick &b : bricks) {
		b.HandleBall(ball);
		if (!b.broken) {
			allBroken = false;
		}
	}

	if (allBroken) {
		SDL_Log("YOU WIN!");
	}

	// Did the ball go off the screen? (if so, end game)
	if (ball.pos.y >= windowHeight)
	{
		mIsRunning = false;
	}
	// Did the ball collide with the right wall?
	else if (ball.pos.x >= (windowWidth - thickness) && ball.vel.x > 0.0f)
	{
		ball.vel.x *= -1.0f;
	}
	// Did the ball collide with the left wall?
	else if (ball.pos.x <= thickness && ball.vel.x < 0.0f)
	{
		ball.vel.x *= -1.0f;
	}
	
	// Did the ball collide with the top wall?
	if (ball.pos.y <= thickness && ball.vel.y < 0.0f)
	{
		ball.vel.y *= -1;
	}
}

void Game::GenerateOutput()
{
	// Set draw color
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		180,	// G
		0,	    // B
		255		// A
	);
	
	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		windowWidth,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw right wall
	wall.x = windowWidth - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = windowHeight;
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw left wall
	wall.x = 0;
	wall.y = 0;
	wall.w = thickness;
	wall.h = windowHeight;
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw paddle
	SDL_Rect paddleRect{
		static_cast<int>(paddle.pos.x - paddleW / 2),
		static_cast<int>(paddle.pos.y),
		static_cast<int>(paddleW),
		thickness
	};
	SDL_RenderFillRect(mRenderer, &paddleRect);
	
	// Draw ball
	SDL_Rect ballRect{	
		static_cast<int>(ball.pos.x - thickness/2),
		static_cast<int>(ball.pos.y - thickness/2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ballRect);

	// Draw bricks
	for (Brick &b : bricks)
	{
		if (!b.broken)
		{
			SDL_Rect brickRect{
				static_cast<int>(b.pos.x - b.w/2),
				static_cast<int>(b.pos.y - b.h/2),
				static_cast<int>(b.w),
				static_cast<int>(b.h)
			};
			SDL_RenderFillRect(mRenderer, &brickRect);
			SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
		}
	}
	
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
