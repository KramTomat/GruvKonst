#include <SDL.h>
#include <stdio.h>
#include <random>
#include <math.h>
#include "Player.h"
#include <unordered_map>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

void MoveRectangleAround(SDL_Surface*, SDL_Window*);

void RandomColour(Uint8& red, Uint8& green, Uint8& blue);
void ColourStep(Uint8& red, Uint8& green, Uint8& blue);

Player* player;
std::unordered_map<int, bool> keysPressed = {
	{SDL_SCANCODE_UP, false},
	{SDL_SCANCODE_DOWN, false},
	{SDL_SCANCODE_RIGHT, false},
	{SDL_SCANCODE_LEFT, false}
	};

double _acceleration = 0.2;
double _gravity = 0.1;

Uint8 Colours[][3] =
{
	{ 0xFF, 0xFF, 0xFF},
	{ 0x00, 0x00, 0x00},
	{ 0x83, 0x12, 0xF4},
	{ 0x21, 0x99, 0xA2}
};

int main(int argc, char *args[])
{
	SDL_Window* window = NULL;
	
	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initilize. SDL error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	window = SDL_CreateWindow(
		"SDL Tutorial", 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		WINDOW_WIDTH, 
		WINDOW_HEIGHT, 
		SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	
	player = new Player();

	screenSurface = SDL_GetWindowSurface(window);

	MoveRectangleAround(screenSurface, window);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void MoveRectangleAround(SDL_Surface* surface, SDL_Window* window)
{
	SDL_Rect* rectangle = new SDL_Rect();
	bool quit = false, draw = false;
	Uint8 red, green, blue;
	short goUp = 0;
	red = green = blue = 0x00;
	while (!quit)
	{
		RandomColour(red, green, blue);
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				keysPressed.insert_or_assign(event.key.keysym.scancode, true);
				break;
			case SDL_KEYUP:
				keysPressed.insert_or_assign(event.key.keysym.scancode, false);
				break;
			case SDL_QUIT:
				quit = true;
				break;
			default:
				break;
			}
		}

		if (keysPressed.at(SDL_SCANCODE_UP)) player->Position->Y -= _acceleration;
		if (keysPressed.at(SDL_SCANCODE_DOWN)) player->Position->Y += _acceleration;
		if (keysPressed.at(SDL_SCANCODE_RIGHT)) player->Position->X += _acceleration;
		if (keysPressed.at(SDL_SCANCODE_LEFT)) player->Position->X -= _acceleration;

		rectangle->h = 5;
		rectangle->w = 5;
		rectangle->x = (int)player->Position->X;
		rectangle->y = (int)player->Position->Y;
		
		SDL_FillRect(surface, rectangle, SDL_MapRGB(surface->format, red, green, blue));

		SDL_UpdateWindowSurface(window);
	}
}

void RandomColour(Uint8& red, Uint8& green, Uint8& blue)
{
	red = rand() % 256;
	green = rand() % 256;
	blue = rand() % 256;
}

void ColourStep(Uint8& red, Uint8& green, Uint8& blue)
{
	// Step up down or stay
	red += rand() % 3 - 1;
	green += rand() % 3 - 1;
	blue += rand() % 3 - 1;

	red = SDL_max(red, 0);
	green = SDL_max(green, 0);
	blue = SDL_max(blue, 0);
	red = SDL_min(red, 255);
	green = SDL_min(green, 255);
	blue = SDL_min(blue, 255);
}
