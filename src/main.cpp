#include <SDL2/SDL.h>
#include <iostream>

const int W_WIDTH = 800;
const int W_HEIGHT = 600;

int main(int argv, char** args) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("DVD Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	bool isRunning = true;
	SDL_Event event;

	// Variables for animating rect

	float r_x = 0;
	float r_y = 0;
	bool moving_right = true;
	const float SIDE = 50.0;
	float x_speed = 0.05;
	float y_speed = 0.05;

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
		rect.y = r_y;
		rect.w = SIDE;
		rect.h = SIDE;
		SDL_RenderFillRect(renderer, &rect);

		// Move the rectangle

		r_x += x_speed;
		r_y += y_speed;

		// Check for x axis collisions against width

		if (r_x >= (W_WIDTH - SIDE) || r_x <= 0) {
			x_speed *= -1;
		}

		// Check for y axis collisions against height

		if (r_y >= (W_HEIGHT - SIDE) || r_y <= 0) {
			y_speed *= -1;
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
