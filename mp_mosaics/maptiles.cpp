/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
   vector<Point<3>> AllPoints;
     map<Point<3>, TileImage*> Maps;
     for (auto iter = theTiles.begin(); iter != theTiles.end(); iter++) {
     	LUVAPixel averagePixel = iter->getAverageColor();
     	Point<3> p_ = convertToXYZ(averagePixel);
     	AllPoints.push_back(p_);
     	Maps[p_] = &*iter;
     }
     KDTree<3> kdt_avgcolor(AllPoints);

     for (int i = 0; i < canvas->getRows(); i++) {
     	for (int j = 0; j < canvas->getColumns(); j++) {
     		Point<3> Regioncolor = convertToXYZ(theSource.getRegionColor(i, j));
     		Point<3> nearestPoint = kdt_avgcolor.findNearestNeighbor(Regioncolor);
     		TileImage* Tile = Maps[nearestPoint];
     		canvas->setTile(i, j, Tile);
      }
     }
     return canvas;



}
