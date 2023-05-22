#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#define ThrowWandException(wand) \
{ \
    char \
        *description; \
 \
    ExceptionType \
        severity; \
 \
    description = MagickGetException(wand, &severity); \
    (void) fprintf(stderr, "%s %s %lu %s\n", GetMagickModule(), description); \
    description = (char *) MagickRelinquishMemory(description); \
    exit(-1); \
}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <MagickWand/MagickWand.h>

#endif