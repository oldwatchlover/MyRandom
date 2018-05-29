
/*
 * myrandom.c
 *
 * (c) Copyright 2018, Steve Anderson. All rights reserved.
 *
 * This file contains some (unix) portable random number functions.
 *
 * Written in simple C with few system dependencies, it has been easily ported and run
 * on countless computers and embedded systems I've worked on.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "myrandom.h"

/*
 * you can enable this define, BE_SAFE and it will add tests/clamps around 0.0 and 1.0
 *
 * I've turned this on/off when adding this to code on new systems... after I'm convinced
 * it's performing properly, I turn it off, just to save a few CPU cycles.
 *
#define BE_SAFE
 */

/*
 * a wrapper around random() that returns values between 0.0 - 1.0
 *
 * self-seeding... the first time it calls it sets the seed.
 * uses a call to time() as the seed (pretty common)
 *
 */
static int my_randinit = 0;
float
my_random(void)
{
    double      dval;

    if (!my_randinit) {    /* seed random number generator the first time it gets called */
        srandom(time(NULL));
        my_randinit = 1;
    }

    dval = (double)random()/(double)RAND_MAX;
#ifdef BE_SAFE
    dval = (dval < 0.0f) ? 0.0f : dval; /* paranoid clamp */
    dval = (dval > 1.0f) ? 1.0f : dval; /* paranoid clamp */
#endif

    return((float) dval);
}

/*
 * my_randomFAST()
 *
 * Returns a random float value between 0.0 and 1.0
 *
 * I wrote this *years* ago for a system that did not have C stdlib on it...
 * It is faster than the version above that calls random() (about twice as fast on 
 * some systems I've tested)
 *
 * I don't remember it's origins... Knuth or comp.lang.c or something similar on the 
 * "old" internet... I am quite sure I didn't derrive it from first principles... :-)
 *
 * I've kept it around as I've occasionally had use for it on embedded systems.
 *
 * It has not been rigorously tested... it does pass the "visual test" (a very large
 * cloud of points plotted, creates no discerable patterns.
 *
 * It does repeat from run to run - it starts with the same seed. This makes it VERY
 * unusable for some applications... for most of mine (3D graphics "noise") it has 
 * served me well. Enable the FAST_USE_TIME_SEED to cure that problem (at the cost
 * of the time(NULL) system call.
 *
 */
#define FAST_USE_TIME_SEED

#define BIG_PRIME (179424691)		 /* the 10000001st prime number */;
#define EIGHTH_MERSENNE	(2147483647.0f)  /* 2^31 - 1, the eighth Mersenne prime number */
static int my_fastrandinit = 0;

float
my_randomFAST(void)
{
    static unsigned int xseed = BIG_PRIME; 
    unsigned int 	x;
    float		fval;

#ifdef FAST_USE_TIME_SEED
    if (!my_fastrandinit) {
	xseed = (unsigned int) time(NULL);
	my_fastrandinit = 1;
    }
#endif

    x = (xseed<<2) + 2;

    x *= (x+1);
    x = x >> 1;
    fval = (float) ((float)x / EIGHTH_MERSENNE);
    x = x >> 1;
    xseed = x; /* for next call */

#if BE_SAFE
    fval = (fval < 0.0f) ? 0.0f : fval; /* paranoid clamp */
    fval = (fval > 1.0f) ? 1.0f : fval; /* paranoid clamp */
#endif

    return(fval);
}


