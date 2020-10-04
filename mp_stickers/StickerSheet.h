/**
 * @file StickerSheet.h
 * Contains your declaration of the unsignederface for the StickerSheet class.
 */
#pragma once
#include <iostream>
using namespace  std;
#include <string>
#include "Image.h"

class StickerSheet {
  public :
    StickerSheet (const Image &picture, unsigned max);
    ~StickerSheet ();
    StickerSheet (const StickerSheet &other);
    const StickerSheet & 	operator= (const StickerSheet &other);

    void 	changeMaxStickers (unsigned max_);
    unsigned 	addSticker (Image &sticker, unsigned x, unsigned y);

    bool 	translate (unsigned index, unsigned x, unsigned y);
    void 	removeSticker (unsigned index);

    Image * 	getSticker (unsigned index);

    Image 	render () const;
//
  private:

    void _copy(const StickerSheet &);
    void _destroy();
    unsigned max;
    Image * basepicture;
    Image ** array;
    unsigned* xarray;
    unsigned* yarray;
    unsigned nb_sticker;



};
