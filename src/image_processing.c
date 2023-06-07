#include "../include/image_processing.h"
#include "../include/error_handling.h"

int main(int argc, const char **argv) {
    char *input_file = NULL;
    char *output_file = NULL;
    int thumbnail_fx = 0;
    int flags_init = 0;

    // Define the command line options
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_STRING('i', "input", &input_file, "Input file"),
        OPT_STRING('o', "output", &output_file, "Output file"),
        OPT_BOOLEAN('t', "thumbnail", &thumbnail_fx, "Turn the images into a thumbnail sequence"),
        OPT_END(),
    };
    const char *const usages[] = {
        "aestheticfx [options] <input_file> <output_file>",
        NULL
    };

    // Define the argument parser
    struct argparse argparse;
    argparse_init(&argparse, options, usages, flags_init);
    argparse_describe(&argparse, "\nA program for image processing and manipulation.", NULL);
    argparse_parse(&argparse, argc, argv);

    // Check if the required arguments are missing
    if (input_file == NULL || output_file == NULL) {
        fprintf(stderr, "Invalid command-line arguments. See usage:\n");
        argparse_usage(&argparse);
        return(-1);
    }

    MagickBooleanType
        status;

    MagickWand
        *magick_wand;
    /*
        Read an image.
    */
    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, input_file);
    if (status == MagickFalse)
        ThrowWandException(magick_wand);
    
    // Turn the image into a thumbnail sequence
    if (thumbnail_fx) {
        MagickResetIterator(magick_wand);
        while (MagickNextImage(magick_wand) != MagickFalse)
            MagickResizeImage(magick_wand, 106, 80, LanczosFilter);
    }
    else {
        fprintf(stderr, "Invalid command-line arguments. See usage:\n");
        argparse_usage(&argparse);
        return(-1);
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