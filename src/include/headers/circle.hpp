#include <SDL2/SDL.h>
#ifndef CIRCLE_HPP
#define CIRCLE_HPP

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

#endif
