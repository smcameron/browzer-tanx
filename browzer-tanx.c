/*
	Copyright (C) 2023 Stephen M. Cameron
	Author: Stephen M. Cameron

	This file is part of Browzer-Tanx.

	Browzer-Tanx is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	Browzer-Tanx is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Browzer-Tanx; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdio.h>
#include <unistd.h>
#include <SDL.h>
#ifdef BTWASM
#include <emscripten.h>
#endif

#define UNUSED __attribute__((unused))

void main_loop(void)
{

}

int main(UNUSED int argc, UNUSED char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Unable to initialize SDL (Video):  %s\n", SDL_GetError());
		return 1;
	}
	if (SDL_Init(SDL_INIT_EVENTS) != 0) {
		fprintf(stderr, "Unable to initialize SDL (Events):  %s\n", SDL_GetError());
		return 1;
	}
#ifdef BTWASM
	emscripten_set_main_loop(main_loop, 60, 1);
#else
	do {
		main_loop();
		usleep(16);
	} while (1);
#endif
}

