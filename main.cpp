/*
  ===========================================================================

  Copyright (C) 2016 Emvivre

  This file is part of IMAGE_VIEWER.

  IMAGE_VIEWER is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  IMAGE_VIEWER is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with IMAGE_VIEWER.  If not, see <http://www.gnu.org/licenses/>.

  ===========================================================================
*/

#include <iostream>
#include "image.h"
#include <cmath>
#include <SDL/SDL.h>
#include <stdint.h>

// affiche une image en plein écrant en gardant le aspect ratio
// interpolation nearest neighbor

static const int MAX_SCREEN_WIDTH = 1360;
static const int MAX_SCREEN_HEIGHT = 768;

int main(int argc, char** argv)
{
	if ( argc < 2 ) {
		std::cout << "Usage: " << argv[0] << " <IMAGE>\n";
		return 1;
	}
	int i = 0;
	std::string image_file = argv[ ++i ];
	Image im( image_file );
	double ratio_x = MAX_SCREEN_WIDTH * 1. / im.width();
	double ratio_y = MAX_SCREEN_HEIGHT * 1. / im.height();
	int window_w;
	int window_h;
	double ratio_pixscr_per_pixim;
	if ( ratio_x < ratio_y ) {
		window_w = MAX_SCREEN_WIDTH;
		ratio_pixscr_per_pixim = ratio_x;
		window_h = ratio_pixscr_per_pixim * im.height();
	} else 	{
		window_h = MAX_SCREEN_HEIGHT;
		ratio_pixscr_per_pixim = ratio_y;
		window_w = ratio_pixscr_per_pixim * im.width();
	}
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* sdl_screen = SDL_SetVideoMode(window_w, window_h, 32, SDL_DOUBLEBUF | SDL_SWSURFACE);
	if ( sdl_screen == NULL ) {
		std::cout << "ERROR: Unable to create SDL screen !!!\n";
		return 1;
	}
        SDL_WM_SetCaption("Image Viewer", NULL);

	double ratio_pixim_per_pixscr = 1 / ratio_pixscr_per_pixim;
	while( true ) { 		
		SDL_PumpEvents();
		unsigned char *keyboard = SDL_GetKeyState(NULL);
		if ( keyboard[ SDLK_ESCAPE ] || keyboard[ SDLK_q ] ) {
			break;
		}				
		
		SDL_LockSurface( sdl_screen );
		uint32_t* p_scr = (uint32_t*) sdl_screen->pixels;
		for ( int y = 0; y < window_h; y++ ) {
			for ( int x = 0; x < window_w; x++ ) {
				int x_im = ratio_pixim_per_pixscr * x;
				int y_im = ratio_pixim_per_pixscr * y;
				unsigned char r = im.red(x_im, y_im);
				unsigned char g = im.green(x_im, y_im);
				unsigned char b = im.blue(x_im, y_im);
				*p_scr++ = r << 16 | g << 8 | b << 0;
			}
		}
		SDL_UnlockSurface( sdl_screen );
		SDL_Flip( sdl_screen );
		SDL_Delay(100);		 
	}	
	SDL_FreeSurface(sdl_screen);
	SDL_Quit();			
	
	return 0; 
}
