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

	// Variables for rect object location
	// Initial location is the center of the window

	const int SIDE = 50;
	int r_x = (W_WIDTH / 2) - (SIDE / 2);
	int r_y = (W_HEIGHT / 2) - (SIDE / 2);
	int r_w = SIDE;
	int r_h = SIDE;

	// Variables to determine if the object is being moved
	// Initially, the object is not moving in any direction

	bool move_right = false;
	bool move_left = false;
	bool move_up = false;
	bool move_down = false;

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

		// Draw the rect in orange

		SDL_SetRenderDrawColor(renderer, 230, 70, 20, 255);
		SDL_Rect rect;
		rect.x = r_x;
		rect.y = r_y;
		rect.w = r_w;
		rect.h = r_h;
		SDL_RenderFillRect(renderer, &rect);

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
