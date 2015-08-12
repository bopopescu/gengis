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
#include "../core/MapView.hpp"

//#include "../utils/cart.h"
//#include "../utils/Cart.hpp"
extern "C" {
//	#include <cart.h>
	#include "../utils/cart.h"
}
/* The parameter OFFSET specifies a small amount to be added the density in
 * every grid square, as a Fraction of the mean density on the whole
 * lattice.  This prevents negative densities from being generated by
 * numerical errors in the FFTs which can cause problems for the
 * integrator.  If the program is giving weird behavior, particularly at
 * the beginning of a calculation, try increasing this quantity by a factor
 * of 10.
 */

#define OFFSET 0.005

namespace GenGIS
{
	class Cartogram
	{
	public:
		explicit Cartogram();
		explicit Cartogram(int buff);

		void MakeCartogram();
		void UndoCartogram();

	private:
		// number of rows in map
		const int ysize;
		// number of columns in map
		const int xsize;
		const int buffer;
		double valFudge;
		int areaFudge;

		/* X and Z coordinates for the un-distorted grid and location set. */
		Point3D* m_originalGrid;
		Point3D* m_originalLocations;
		Point3D** m_originalVector;

		/** Copied directly from MapView. See class for more information. */
		MapControllerPtr m_mapController;
		
		/** Translate the first location set Lat/Lon to Raster Grid coordinates. */
		std::map<int,boost::array<int,4>> TranslateLocations();
		
		/** Function which creates the cartogram. */
		void StdMain();
		
		/** Template to write out some sort of generic matrix **/
		template< typename Matrix >
		void WriteMatrix(Matrix rho, int row, int col, std::string name);
		int readpop(FILE *stream, double **rho, int xsize, int ysize);
		void writepoints(FILE *stream, double *gridx, double *gridy, int npoints);
		template< typename Matrix >
		int readpoints(FILE *stream, Matrix &gridx, Matrix &gridy, int xsize, int ysize);

		/** Create the density matrix for input into Cart. */
		void MakeRho();

		/** Get the average density value for all locations.
			This will be used to fill in empty spots in the grid*/
		int GetMapAverage(std::map<int,boost::array<int,4>> map);

		/** Create grid of density values. */
		void CreateGrid(double *gridx, double *gridy, int xsize, int ysize);

		/** Populate the grid of density values.*/
	//	void PopulateRho( double ** rho );
		std::vector<std::vector<double>> PopulateRho( );
		
		/** Interpolate between standard Raster coordinates and the cartogram.*/
		template< typename Matrix >
		void Interpolate(Matrix gridx, Matrix gridy);

		/** Interpolate locations from standard raster to cartogram coordinates. */
		template< typename Matrix >
		void InterpolateLocations(Matrix gridx, Matrix gridy);
		
		/** Interpolate between standard Raster coordinates and the cartogram for all Vector layers.*/
		template< typename Matrix >
		void InterpolateVector(Matrix gridx, Matrix gridy);

		/** Transform a 1D array to a 2D array in order to move between Cart and Interp steps. */
		std::vector<std::vector<double>> ArrayTransform(double * grid);
		template< typename Matrix >
		void ArrayTransform(double * grid, Matrix &transGrid);

		/** Set the Area Fudge value for the Cartogram. */
		void SetAreaFudge(int val){ areaFudge = val;}

		/** Set the Value Fudge value for the Cartogram. */
		void SetValueFudge(int val){ valFudge = val;}

		/** Store the original grid and and location coordiantes. */
		void SaveOriginalProjection();
	};
}
#endif