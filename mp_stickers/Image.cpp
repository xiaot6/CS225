#include<iostream>
using namespace std;
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <math.h>

      void Image::lighten(){
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = getPixel(x, y);
                if ((pixel.l+0.1) >= 1) {
                  pixel.l = 1;
                } else {
                  pixel.l = pixel.l + 0.1;
                }
            }
        }
      }

      void Image::lighten(double amount){
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = getPixel(x, y);
                if ((pixel.l+amount) >= 1) {
                  pixel.l = 1;
                } else {
                  pixel.l = pixel.l + amount;
                }
            }
        }
      }

      void Image::darken(){
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = getPixel(x, y);
                if ((pixel.l-0.1) <= 0) {
                  pixel.l = 0;
                } else {
                  pixel.l = pixel.l -0.1;
                }
            }
        }
      }


      void Image::darken(double amount){
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = getPixel(x, y);
                if ((pixel.l-amount) <= 0) {
                  pixel.l = 0;
                } else {
                  pixel.l = pixel.l -amount;
                }
            }
        }
      }

      void Image::saturate(){
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = getPixel(x, y);
                if ((pixel.s+0.1) >= 1) {
                  pixel.s = 1;
                } else {
                  pixel.s = pixel.s + 0.1;
                }
            }
        }
      }

      void Image::saturate(double amount){
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = getPixel(x, y);
                if ((pixel.s+amount) >= 1) {
                  pixel.s = 1;
                } else {
                  pixel.s = pixel.s + amount;
                }
            }
        }
      }

      void Image::desaturate(){
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = getPixel(x, y);
                if ((pixel.s-0.1) <= 0) {
                  pixel.s = 0;
                } else {
                  pixel.s = pixel.s -0.1;
                }
            }
        }
      }

      void Image::desaturate(double amount){
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = getPixel(x, y);
                if ((pixel.s-amount) <= 0) {
                  pixel.s = 0;
                } else {
                  pixel.s = pixel.s -amount;
                }
            }
        }
      }

      void Image::grayscale(){
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = getPixel(x, y);
                pixel.s = 0;
            }
        }
      }


      void Image::rotateColor(double degrees){
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = getPixel(x, y);

                if ((pixel.h + degrees) <= 360 && (pixel.h + degrees) >= 0 ) {
                  pixel.h = pixel.h + degrees;
                }
                while ((pixel.h + degrees) > 360) {
                  pixel.h = pixel.h + degrees -360;
                }
                while ((pixel.h + degrees) < 0){
                  pixel.h = pixel.h + degrees +360;
                }
            }
          }
      }


      void Image::illinify(){
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = getPixel(x, y);
                if(pixel.h <=113.5 || pixel.h >=293.5) {
                  pixel.h = 11;
                } else {
                  pixel.h = 216;
                }
            }
          }
      }



      void Image::scale(double factor){
        if (factor == 1) {
          return;
        }
        Image oldimage = (*this);
        double oldwidth = this->width();
        double oldheight = this->height();
        unsigned int newwidth = this->width() * factor;
        unsigned int newheight = this->height() * factor;
        this->resize(newwidth,newheight);
        for (unsigned x = 0; x < newwidth; x++) {
            for (unsigned y = 0; y < newheight; y++) {
                cs225::HSLAPixel & newpixel = this->getPixel(x, y);
                newpixel = oldimage.getPixel(floor(x/factor), floor(y/factor));
            }
          }
      }

      void Image::scale(unsigned w, unsigned h){
        double w_factor = w / (double)this->width();
        double h_factor = h / (double)this->height();
        if (w_factor == 1 && h_factor == 1) {
          return;
        }
        if (w_factor < h_factor) {
          this->scale(w_factor);
        } else {
          this->scale(h_factor);
        }

      }
