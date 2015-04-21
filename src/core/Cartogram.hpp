//=======================================================================
// Author: Alexander Keddy
//
// Copyright 2015 Alexander Keddy
//
// This file is part of GenGIS.
//
// GenGIS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// GenGIS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GenGIS.  If not, see <http://www.gnu.org/licenses/>.
//=======================================================================

#ifndef _GENGIS_CARTOGRAM_
#define _GENGIS_CARTOGRAM_

#include "../core/Precompiled.hpp"
#include "../utils/StringTools.hpp"

#include "../utils/cart.h"

namespace GenGIS
{
	class Cartogram
	{
	public:
		explicit Cartogram();
		explicit Cartogram(float x, float y);

	private:
		int xsize;
		int ysize;
		std::vector<float> gridx;
		std::vector<float> gridy;
		std::vector<std::vector<float>> grid;
	
	};
}
#endif