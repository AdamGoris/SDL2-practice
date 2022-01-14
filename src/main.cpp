#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>

const int W_WIDTH = 800;
const int W_HEIGHT = 600;

int main(int argv, char** args) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	bool isRunning = true;
	SDL_Event event;

	const int RADIUS = 50;
	const int DIAMETER = RADIUS * 2;
	int C_CENTER_X = W_WIDTH / 2;
	int C_CENTER_Y = W_HEIGHT / 2;

	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						isRunning = false;
					}
					if (event.key.keysym.sym == SDLK_SPACE) {
						// On space, move circle to random x,y
						// Ensure no part of the circle is outside the window

						C_CENTER_X = (rand() % (W_WIDTH - DIAMETER)) + RADIUS;
						C_CENTER_Y = (rand() % (W_HEIGHT - DIAMETER)) + RADIUS;
					}
			}
		}

		// Clear the renderer

    SDL_RenderClear(renderer);

		// Draw the circle in white 

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		int x = RADIUS;
		int y = 0;
		int p = 1 - RADIUS;
		while (x > y) {
			// Render a point on each octant of the circle

			SDL_RenderDrawPoint(renderer, C_CENTER_X + x, C_CENTER_Y - y);
			SDL_RenderDrawPoint(renderer, C_CENTER_X + x, C_CENTER_Y + y);
			SDL_RenderDrawPoint(renderer, C_CENTER_X - x, C_CENTER_Y - y);
			SDL_RenderDrawPoint(renderer, C_CENTER_X - x, C_CENTER_Y + y);

			SDL_RenderDrawPoint(renderer, C_CENTER_X + y, C_CENTER_Y - x);
			SDL_RenderDrawPoint(renderer, C_CENTER_X + y, C_CENTER_Y + x);
			SDL_RenderDrawPoint(renderer, C_CENTER_X - y, C_CENTER_Y - x);
			SDL_RenderDrawPoint(renderer, C_CENTER_X - y, C_CENTER_Y + x);

			y++;
			if (p <= 0) {
				p = p + (2 * y) + 1;
			} else {
				x--;
				p = p + (2 * y) - (2 * x) + 1;
			}
		}

		// Draw the background in black

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		// Render updated renderer 

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
