#include <SDL2/SDL.h>
#include <iostream>

const int W_WIDTH = 800;
const int W_HEIGHT = 600;

int main(int argv, char** args) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	bool isRunning = true;
	SDL_Event event;

	// Variables for animating rect

	float r_x = 0;
	float r_y = 0;
	bool hit_right = false;
	bool hit_left = true;	// start hit_left true to force moving right initially

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
			}
		}

		// Clear the renderer

		SDL_RenderClear(renderer);

		// Draw the rectangle in purple

		SDL_SetRenderDrawColor(renderer, 110, 20, 255, 255);

		// Draw a rectangle

		SDL_Rect rect;
		rect.x = r_x;
		rect.y = W_HEIGHT/2;
		rect.w = 150;
		rect.h = 150;
		SDL_RenderFillRect(renderer, &rect);
		
		// Check for x-axis collisions

		if (r_x >= W_WIDTH - 150) {
			hit_right = true;
			hit_left = false;
		}
		if (r_x <= 0) {
			hit_right = false;
			hit_left = true;
		}

		// Move the rect in the direction of travel

		if (hit_right) {
			r_x -= 0.01;
		}
		if (hit_left) {
			r_x += 0.01;
		}

		// Draw the background in black

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		// Render updated renderer 

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
