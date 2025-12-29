/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <iostream>   // printing, debugging
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

int main ()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	//initialize variables
	int screenWidth = 1280;
	int screenHeight = 800;
	Vector2 playerPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
	Vector2 zombiePosition = {25,25};
	Vector2 zombieSpawn[3] = {25,25};
	std::vector<Vector2> zombiePositions;
	zombiePositions.push_back({ 100, 100 });
	zombiePositions.push_back({ 300, 200 });
	zombiePositions.push_back({ 600, 400 });

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "Window 1");

	//fps target
	SetTargetFPS(60);


	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	//Texture wabbit = LoadTexture("wabbit_alpha.png");
	//--------------------------------------------------------------------------------------


	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// Update
		//----------------------------------------------------------------------------------
		if (IsKeyDown(KEY_D)) playerPosition.x += 2.0f;
		if (IsKeyDown(KEY_A)) playerPosition.x -= 2.0f;
		if (IsKeyDown(KEY_W)) playerPosition.y -= 2.0f;
		if (IsKeyDown(KEY_S)) playerPosition.y += 2.0f;
		// get zombie to follow player 
		//----------------------------------------------------------------------------------
		if (zombiePosition.x < playerPosition.x) {
			zombiePosition.x += 1.5f; 
		}
		if (zombiePosition.x > playerPosition.x) {
			zombiePosition.x -= 1.5f;
		}
		if (zombiePosition.y > playerPosition.y) {
			zombiePosition.y -= 1.5f;
		}
		if (zombiePosition.y < playerPosition.y) {
			zombiePosition.y += 1.5f;
		}
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

			ClearBackground(BROWN);
			DrawCircleV(playerPosition, 15.0f, SKYBLUE);
			DrawCircleV(zombieSpawn[0], 25.0f, BLACK);
			DrawCircleV(zombiePosition, 15.0f, RED);
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
