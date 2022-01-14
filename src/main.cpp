#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <circle.hpp>

const int W_WIDTH = 800;
const int W_HEIGHT = 600;

int main(int argv, char** args) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	bool isRunning = true;
	SDL_Event event;

	Circle my_circle(W_WIDTH / 2, W_HEIGHT / 2, 50);

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
						// On space, move circle

						my_circle.move(W_WIDTH, W_HEIGHT);
					}
			}
		}

		// Clear the renderer

    SDL_RenderClear(renderer);

		// Draw the circle in white 

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		my_circle.draw(renderer);

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
