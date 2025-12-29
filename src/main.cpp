/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/
//------------------------------------------------------------------------------------
// Includes
#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <iostream>   // printing, debugging
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
//------------------------------------------------------------------------------------
struct Zombie {
	Vector2 position;
	int health = 100;
	int damage = 5;
	float speed = 1.5f;
};
Zombie MakeZombie(Vector2 spawnPos, int round)
{
	Zombie z;
	z.position = spawnPos;
	z.health = 100 + (round - 1) * 20; 
	return z;
}
void SpawnOneZombie(std::vector<Zombie>& zombies, Vector2 spawns[4], GameStats& stats)
{
	int idx = GetRandomValue(0, 3);            
	zombies.push_back(MakeZombie(spawns[idx], stats.round));
	stats.zombiesRendered++;
	stats.zombiesUnrendered--;
}
struct GameStats {
	int round = 1;
	int score = 0;
	int zombiesKilled = 0;
	int zombiesLeft = 6;
	int zombiesRendered = 0;
	int zombiesUnrendered = 6;
};
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	//initialize variables
	int screenWidth = 1280;
	int screenHeight = 800;
	int playerHealth = 100;
	Vector2 playerPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
	Vector2 zombieSpawn[4] = {{ 25,25 }, { 1255,25 }, { 1255, 775 }, { 25, 775 }};
	std::vector<Vector2> zombiePositions;
	std::vector<Zombie> zombies;
	//zombiePositions.push_back({ 25, 25 });
	//zombiePositions.push_back({ 1255, 25 });
	//zombiePositions.push_back({ 1255, 775 });
	//zombiePositions.push_back({ 25, 775});
	bool startGame = false;
	int framesCounter = 0; 
	GameStats stats;

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "Window 1");
	GameScreen currentScreen = LOGO;
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
		switch (currentScreen) {
			case LOGO:
			{
				if (IsKeyPressed(KEY_ENTER)) startGame = true;
				if (startGame == true) {
					framesCounter++;
				}
				if (framesCounter > 360)
				{
					currentScreen = TITLE;
					framesCounter = 0;
				}
			} break;
			// In title screen
			case TITLE:
			{
				if (IsKeyPressed(KEY_ENTER)) currentScreen = GAMEPLAY;
			} break;
			// In da game
			case GAMEPLAY:
			{	
				//Round Logic here
				//Spawn the zombies 
				//check if we need to spawn more zombies
				while (stats.zombiesRendered < 30 && stats.zombiesUnrendered !=0) {
					SpawnOneZombie(zombies, zombieSpawn, stats);
				}
				//Check if zombies are dead
				if (stats.zombiesLeft == 0) {
					//incriment round
					stats.round++;
					//spawn new zombies
					stats.zombiesLeft = stats.round * 5 ;
				}
		
				
				// Player Movement
				if (IsKeyDown(KEY_D)) playerPosition.x += 2.0f;
				if (IsKeyDown(KEY_A)) playerPosition.x -= 2.0f;
				if (IsKeyDown(KEY_W)) playerPosition.y -= 2.0f;
				if (IsKeyDown(KEY_S)) playerPosition.y += 2.0f;
				//----------------------------------------------------------------------------------
				for (Vector2& zombiePosition : zombiePositions) {
					// Move zombies toward player
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
					// Add some random movement
					zombiePosition.x += (rand() % 3) - 1;
					zombiePosition.y += (rand() % 3) - 1;
					//zombie collision with themselves
				}

			} break;
			case ENDING:
			{
			
			} break;
			default: break;
		}
		
		
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
			switch (currentScreen)
			{
			case LOGO:
			{
				ClearBackground(RAYWHITE);
				DrawText("Project : Frostbite", 400, 100, 50, SKYBLUE);
				if (framesCounter < 1)
				DrawText("Press Enter To Start", 360, 400, 50, SKYBLUE);
				if (framesCounter >= 60 && framesCounter < 120)
				DrawText("5", 600, 400, 50, SKYBLUE);
				if (framesCounter >= 120 && framesCounter < 180)
				DrawText("4", 600, 400, 50, SKYBLUE);
				if (framesCounter >= 180 && framesCounter < 240)
				DrawText("3", 600, 400, 50, SKYBLUE);
				if (framesCounter >= 240 && framesCounter < 300)
				DrawText("2", 600, 400, 50, SKYBLUE);
				if (framesCounter >= 300 && framesCounter < 360)
				DrawText("1", 600, 400, 50, SKYBLUE);

			} break;
			case TITLE:
			{
				ClearBackground(RAYWHITE);
				DrawText("Press Enter To Start", 360, 400, 50, SKYBLUE);;

			} break;
			case GAMEPLAY:
			{
				ClearBackground(BROWN);
				DrawCircleV(playerPosition, 15.0f, SKYBLUE);
				//draw spawn points
				for (int i = 0; i < 4; i++) {
					DrawCircleV(zombieSpawn[i], 25.0f, BLACK);
				}
				//draw zombies
				for (Vector2& zombiePosition : zombiePositions) {
					DrawCircleV(zombiePosition, 15.0f, RED);
				}
				DrawText("Prototype - Frostbite", 540, 20, 20, LIGHTGRAY);
				//dufault 1280 x 800
				DrawText(TextFormat("Round: %i", stats.round), 600, 750, 20, BLACK);
				DrawText(TextFormat("Zombies Left: %i", stats.zombiesLeft), 600, 725, 20, BLACK);
				DrawText(TextFormat("Zombies Killed: %i", stats.zombiesKilled), 600, 700, 20, BLACK);


			} break;
			case ENDING:
			{
				// TODO: Draw ENDING screen here!
				DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
				DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
				DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

			} break;
			default: break;
			}

			
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
