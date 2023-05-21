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
#include <stdint.h>
#include <SDL.h>
#ifdef BTWASM
#include <emscripten.h>
#endif

#define UNUSED __attribute__((unused))

#define SCREEN_XDIM 640
#define SCREEN_YDIM 480

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Surface *surface;

void main_loop(void)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, 0, 0, SCREEN_XDIM - 1, SCREEN_YDIM - 1);
	SDL_RenderDrawLine(renderer, 0, SCREEN_YDIM, SCREEN_XDIM - 1, 0);
	SDL_RenderPresent(renderer);
}

static int init_sdl2(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Unable to initialize SDL (Video):  %s\n", SDL_GetError());
		return 1;
	}
	if (SDL_Init(SDL_INIT_EVENTS) != 0) {
		fprintf(stderr, "Unable to initialize SDL (Events):  %s\n", SDL_GetError());
		return 1;
	}
	if (SDL_CreateWindowAndRenderer(SCREEN_XDIM, SCREEN_YDIM, 0, &window, &renderer) != 0) {
		fprintf(stderr, "Unable to create window/renderer: %s\n", SDL_GetError());
		return 1;
	}
	surface = SDL_CreateRGBSurface(0, SCREEN_XDIM, SCREEN_YDIM, 32, 0, 0, 0, 0);
	if (!surface) {
		fprintf(stderr, "Unable to create RGB surface: %s\n", SDL_GetError());
		return 1;
	}
	return 0;
}

int main(UNUSED int argc, UNUSED char *argv[])
{
	if (init_sdl2())
		return -1;
#ifdef BTWASM
	emscripten_set_main_loop(main_loop, 60, 1);
#else
	do {
		main_loop();
		usleep(16);
	} while (1);
#endif
}

