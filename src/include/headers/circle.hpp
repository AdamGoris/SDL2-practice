#include <SDL2/SDL.h>

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
		void move(int max_x, int max_y);
		void draw(SDL_Renderer* renderer);
};

void Circle::move(int max_x, int max_y) {
	// move x and y to random location
	// Ensure no part of the circle is beyond the max

	center_x = (rand() % (max_x - diameter)) + radius;
	center_y = (rand() % (max_y - diameter)) + radius;
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
