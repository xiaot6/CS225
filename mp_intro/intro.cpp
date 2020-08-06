#include <iostream>
#include <cmath>
#include <cstdlib>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "intro.h"

#include <string>

using cs225::HSLAPixel;
using cs225::PNG;


void rotate(std::string inputFile, std::string outputFile) {
  PNG png_in;
  png_in.readFromFile(inputFile);
  PNG png_out(png_in);
  for (unsigned x = 0; x < png_in.width(); x++) {
    for (unsigned y = 0; y < png_in.height(); y++) {
      HSLAPixel & pixel = png_out.getPixel(x, y);
      pixel = png_in.getPixel(png_in.width()-1-x,png_in.height()-1-y);

    }
  }
  png_out.writeToFile(outputFile);

}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      if (x< 1./3. *png.width()){
        pixel.h=191.;
        pixel.s=1.;
        pixel.l=0.8;
        pixel.a=1.;
      } else if (x >=1./3.*png.width() && x<= 2./3. *png.width()){
        pixel.h=240.;
        pixel.s=1.;
        pixel.l=0.8;
        pixel.a=1.;
      } else {
        pixel.h=313.;
        pixel.s=1.;
        pixel.l=0.82;
        pixel.a=1.;
      }
    }
  }

  return png;
}
