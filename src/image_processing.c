#include "../include/image_processing.h"
#include "../include/error_handling.h"

int main(int argc, const char **argv) {
    /*
        Read an image.
    */
    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, input_file);
    if (status == MagickFalse)
        ThrowWandException(magick_wand);
    
    if (thumbnail_fx) {
        MagickResetIterator(magick_wand);
        while (MagickNextImage(magick_wand) != MagickFalse)
            MagickResizeImage(magick_wand, 106, 80, LanczosFilter);
    }
    /*
        Write the image then destroy it.
    */
    status = MagickWriteImages(magick_wand, output_file, MagickTrue);
    if (status == MagickFalse)
        ThrowWandException(magick_wand);
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    return(0);
}