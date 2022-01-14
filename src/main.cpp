#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>

const int W_WIDTH = 800;
const int W_HEIGHT = 600;

class Circle {
	private:
		int center_x;
		int center_y;
		int radius;
		int diameter;
	public:
		Circle(int x, int y, int r) {
			center_x = x;
			center_y = y;
			radius = r;
			diameter = 2 * radius;
		}
		void move();
		void draw(SDL_Renderer* renderer);
};

void Circle::move() {
	// move x and y to random location
	// Ensure no part of the circle is outside the window

	center_x = (rand() % (W_WIDTH - diameter)) + radius;
	center_y = (rand() % (W_HEIGHT - diameter)) + radius;
};

void Circle::draw(SDL_Renderer* renderer) {
		int x = radius;
		int y = 0;
		int p = 1 - radius;
		while (x > y) {
			// Render a point on each octant of the circle

			SDL_RenderDrawPoint(renderer, center_x + x, center_y - y);
			SDL_RenderDrawPoint(renderer, center_x + x, center_y + y);
			SDL_RenderDrawPoint(renderer, center_x - x, center_y - y);
			SDL_RenderDrawPoint(renderer, center_x - x, center_y + y);

			SDL_RenderDrawPoint(renderer, center_x + y, center_y - x);
			SDL_RenderDrawPoint(renderer, center_x + y, center_y + x);
			SDL_RenderDrawPoint(renderer, center_x - y, center_y - x);
			SDL_RenderDrawPoint(renderer, center_x - y, center_y + x);

			y++;
			if (p <= 0) {
				p = p + (2 * y) + 1;
			} else {
				x--;
				p = p + (2 * y) - (2 * x) + 1;
			}
		}
}

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

						my_circle.move();
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
