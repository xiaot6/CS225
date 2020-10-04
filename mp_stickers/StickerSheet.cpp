#include "StickerSheet.h"
#include <iostream>
using namespace  std;
#include <string>

void StickerSheet::_copy(const StickerSheet &other){
  // _destroy();
  max  = other.max;
  basepicture = new Image(*(other.basepicture));
  array = new Image*[max];
  xarray = new unsigned[max];
  yarray = new unsigned[max];
  nb_sticker = other.nb_sticker;
  for (unsigned i =  0; i < max; i++)  {

      array[i] = NULL;

  }
  for (unsigned i =  0; i < nb_sticker; i++)  {
    array[i] = new Image();
    *array[i] = *other.array[i];
    xarray[i] = other.xarray[i];
    yarray[i] = other.yarray[i];
  }
}


void StickerSheet::_destroy(){
  for (unsigned i = 0; i < nb_sticker; i++) {
    if (array[i] != NULL) {
      delete array[i];
      array[i] = NULL;
    }
  }

  if (array != NULL) {
    delete [] array;
    array = NULL;
  }
  if (xarray != NULL) {
    delete [] xarray;
    xarray = NULL;
  }

  if (yarray != NULL) {
    delete [] yarray;
    yarray = NULL;
  }
  if (basepicture != NULL) {
    delete basepicture;
    basepicture = NULL;
  }

}


StickerSheet::StickerSheet(const Image &picture, unsigned setmax){
    //std::cout<<"ctor"<<std::endl;
  // _destroy();
  max = setmax;
  array = new Image*[max];
  xarray = new unsigned [max];
  yarray = new unsigned [max];
  for (unsigned i = 0; i < max; i++) {
    array[i] = NULL;
    xarray[i] = -1;
    yarray[i] = -1;
  }
  basepicture = new Image(picture);
  nb_sticker  = 0;

}


StickerSheet::~StickerSheet (){
      //std::cout<<"dtor"<<std::endl;
  _destroy();
}


StickerSheet::StickerSheet (const StickerSheet &other){
      //std::cout<<"copy"<<std::endl;
  _copy(other);

}

const StickerSheet & 	StickerSheet::operator= (const StickerSheet &other){
      //std::cout<<"operator"<<std::endl;

  if (&other != this) {
    _destroy();
    _copy(other);
  }
// std::cout<<"debug*"<<std::endl;
  return *this;

}

void 	StickerSheet::changeMaxStickers (unsigned max_new){
  Image ** n_array = array;
  unsigned  *n_xarray = this-> xarray;
  unsigned  * n_yarray = this-> yarray;
  array = NULL;
  xarray = NULL;
  yarray = NULL;
  array = new Image*[max_new];
  xarray = new unsigned [max_new];
  yarray = new unsigned [max_new];
  if (max_new > max) {
    for (unsigned i = 0; i < max; i++) {
      array[i] = n_array[i];
      xarray[i] = n_xarray[i];
      yarray[i] = n_yarray[i];
    }
    for (unsigned i = max; i < max_new; i++) {
      array[i] = NULL;
      xarray[i] = -1;
      yarray[i] = -1;
    }
  }
  if (max_new <= max) { //max_new < max
          for (unsigned i = 0; i < max_new; i++) {
            array[i] = n_array[i];
            xarray[i] = n_xarray[i];
            yarray[i] = n_yarray[i];
          }
          for (unsigned i = max_new; i < max; i++) {
            delete n_array[i];
            // xarray[i] = n_xarray[i];
            // yarray[i] = n_yarray[i];
          }

  }
  if (nb_sticker > max_new) {
    nb_sticker = max_new;

  }
  delete []n_array;
  delete []n_xarray;
  delete []n_yarray;
  max = max_new;

}


unsigned  	StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
 //    //std::cout<<"addSticker"<<std::endl;
 // for (unsigned i = 0; i <max; i ++) {
 //   if (array[i] == NULL) {
 //     array[i] = & sticker;
 //     xarray[i] = x;
 //     yarray[i] = y;
 //     this->nb_sticker ++;
 //     return i;
 //   }
 // }
 // return -1;


  //method work 2
  // array[nb_sticker] = & sticker;
  array[this->nb_sticker] = new Image(sticker);

  xarray[this->nb_sticker] = x;
  yarray[this->nb_sticker] = y;
  this->nb_sticker ++;
  return nb_sticker - 1;
}

bool 	StickerSheet::translate (unsigned index, unsigned x, unsigned y){
    //std::cout<<"translate"<<std::endl;

  if (array[index] == NULL) {
    return false;
  } else {
    xarray[index] = x;
    yarray[index] = y;
  }

  return true;

}
void 	StickerSheet::removeSticker (unsigned index) {

//method work:
  if(index < nb_sticker){
    for(unsigned i = index; i < (nb_sticker - 1); i++){
      *array[i] =  *array[i + 1];
      xarray[i] = xarray[i + 1];
      yarray[i] = yarray[i + 1];
    }
    delete array[nb_sticker - 1];
    array[nb_sticker-1] = NULL;
    nb_sticker--;
  }

  // for (unsigned i = 0; i <max;i++) {
  //   if (i == index) {
  //     array[index] = NULL;
  //     xarray[index] = -1;
  //     yarray[index] = -1;
  //     nb_sticker--;
  //   }
  // }

}

Image * 	StickerSheet::getSticker (unsigned index){
    //std::cout<<"get"<<std::endl;

  if (index > max || array[index] == NULL) {
    return NULL;
  }

  return array[index];

}


Image 	StickerSheet::render () const{

	  Image toreturn = *basepicture;
	  unsigned int width_max = basepicture->width();
	  unsigned int height_max = basepicture->height();

	  for (unsigned int i = 0; i <nb_sticker; i++) {
	          if (xarray[i] + array[i]->width()> width_max) {
	            width_max = xarray[i] + array[i]->width();
	          }
	          if ((yarray[i] + array[i]->height()) > height_max) {
	            height_max = yarray[i] + array[i]->height();
	          }
	  }
		toreturn.resize(width_max, height_max);
		for (unsigned i=0; i<nb_sticker ; i++){
	    if (array[i] != NULL) {
			for (unsigned x = xarray[i]; x < xarray[i] + array[i]->width() ; x++)
			  for (unsigned y = yarray[i]; y < yarray[i] + array[i]->height() ; y++) {
	  			cs225::HSLAPixel & pixel = array[i]->getPixel(x-xarray[i], y-yarray[i]);
	  			cs225::HSLAPixel & pixel_out = toreturn.getPixel(x, y);
	  			if (pixel.a != 0)
	    			{
	    				pixel_out = pixel;
	    			}
	        }
			}
		}

		return toreturn;
	}
