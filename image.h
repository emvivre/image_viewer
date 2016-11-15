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

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <gd.h>
#include <string>
#include <glm/glm.hpp>

class Image
{
	int* img;
	int w, h;
public:
	class UnknownExtension {};
	class UnableToOpenFile {};

	~Image() { delete[] img; }
	Image(std::string file);
	int width() const { return w; }
	int height() const { return h; }
	const int* ptr() const { return img; }
	int at(int x, int y) const { return img[y * w + x]; }
	glm::vec3 operator()(int x, int y) const { return glm::vec3(red(x,y), green(x,y), blue(x,y)); }
	unsigned char red(int x, int y) const { return gdTrueColorGetRed(this->at(x,y)); }
	unsigned char green(int x, int y) const { return gdTrueColorGetGreen(this->at(x,y)); }
	unsigned char blue(int x, int y) const { return gdTrueColorGetBlue(this->at(x,y)); }
};

#endif /* !_IMAGE_H_ */
