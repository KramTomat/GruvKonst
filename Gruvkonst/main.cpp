#include <SDL.h>
#include <stdio.h>
#include <random>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

void MoveRectangleAround(SDL_Surface*, SDL_Window*);

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
	
	screenSurface = SDL_GetWindowSurface(window);

	MoveRectangleAround(screenSurface, window);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void MoveRectangleAround(SDL_Surface* surface, SDL_Window* window)
{
	SDL_Rect* rectangle = new SDL_Rect();
	{
		int x, y;
		bool quit = false;
		Uint8 red, green, blue;
		red = green = blue = 0x00;
		while (!quit)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_EventType::SDL_MOUSEMOTION)
				{
					red = rand() % 255;
					green = rand() % 255;
					blue = rand() % 255;
				}
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			SDL_SetCursor(NULL);
			SDL_GetMouseState(&x, &y);

			rectangle->h = 50;
			rectangle->w = 100;
			rectangle->x = x;
			rectangle->y = y;

			SDL_FillRect(surface, rectangle, SDL_MapRGB(surface->format, red, green, blue));

			SDL_UpdateWindowSurface(window);

		}
	}
}
