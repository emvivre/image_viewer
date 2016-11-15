/*
  ===========================================================================

  Copyright (C) 2014 Emvivre

  This file is part of IMAGE.

  IMAGE is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  IMAGE is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with IMAGE.  If not, see <http://www.gnu.org/licenses/>.

  ===========================================================================
*/

#include "image.h"
#include "string_util.h"
#include <map>

typedef gdImagePtr (*GdImageCreatePtrFct)(FILE*);
std::map<std::string, GdImageCreatePtrFct> img_init = { 
	{ "png", gdImageCreateFromPng },
	{ "gif", gdImageCreateFromGif },
	{ "wbmp", gdImageCreateFromWBMP },
	{ "jpeg", gdImageCreateFromJpeg },
	{ "jpg", gdImageCreateFromJpeg },
	{ "webp", gdImageCreateFromWebp },
	{ "tiff", gdImageCreateFromTiff },
	{ "tga", gdImageCreateFromTga },
	{ "bmp", gdImageCreateFromBmp },
};

Image::Image(std::string file)
{
	std::string ext = StringUtil::extension(file);
	if ( img_init.find(ext) == img_init.end() ) throw UnknownExtension();
	FILE* f = fopen(file.c_str(), "r");
	if ( f == NULL ) throw UnableToOpenFile();
	gdImagePtr gd = img_init[ext](f);
	this->w = gdImageSX(gd);
	this->h = gdImageSY(gd);
	fclose(f);
	this->img = new int[this->w * this->h];
	for ( int y = 0; y < h; y++ ) {
		for ( int x = 0; x < w; x++ ) {
			this->img[y * w + x] = gdImageGetTrueColorPixel(gd, x, y);
		}
	}
	gdImageDestroy(gd);
}
