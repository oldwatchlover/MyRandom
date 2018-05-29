
/*
 * test.c
 *
 * Test my random functions
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
 * compile with all output code removed, better for peformance testing
 *
#define PERF_TESTING
 */

#include "myrandom.h"

#define PROGRAM_NAME	"test"
#define PROGRAM_VERSION	"1.0"

//#define TEST_MAX	1024000
#define TEST_MAX	4096



/*
 * main routine.
 *
 */
int
main(int argc, char *argv[])
{
    char        usage_string[256];
    int		i, use_fast = 0;
    float	a, b, minval=100.0f, maxval=-100.0f;
    clock_t	begin, end;
    double	elapsed;

    sprintf(usage_string,"usage : %s [-c]", PROGRAM_NAME);

    while ((argc > 1) && (argv[1][0] == '-')) {
        switch(argv[1][1]) {

          case 'f':
	    use_fast = 1;
            break;
            
          default:
            fprintf(stderr,"ERROR : %s : program option [%s] not recognized.\n", __FILE__,argv[1]);
            fprintf(stderr,"%s\n",usage_string);
            break;

        }
        argc--;
        argv++;
    }

    fprintf(stderr,"%s : Version %s, dated %s\n",
            PROGRAM_NAME, PROGRAM_VERSION, __DATE__);
    if (use_fast)
        fprintf(stderr,"%s : using fast rand algorithm\n",PROGRAM_NAME);

    begin = clock();

    for (i=0; i<TEST_MAX; i++) {

	if (use_fast) {
	    a = my_randomFAST();
            b = my_randomFAST();
	} else {
	    a = my_random();
            b = my_random();
	}

#ifndef PERF_TESTING
	/* skip this for performance testing... if you are really picky
 	 * you could compile versions with the different rand calls rather than
	 * leaving the if test above...
	 */
	if (a < minval)
	    minval = a;
	if (a > maxval)
	    maxval = a;

	if (b < minval)
	    minval = b;
	if (b > maxval)
	    maxval = b;

	fprintf(stdout,"%f, %f,\n",a,b);
#endif
    }

    end = clock();

    elapsed = (double)(end - begin) / CLOCKS_PER_SEC;

    fprintf(stderr,"%s : generated %d random pairs in %lf seconds.\n",
	PROGRAM_NAME,TEST_MAX,elapsed);

    fprintf(stderr,"%s : generated %d random pairs, min = %f max = %f\n",
	PROGRAM_NAME,TEST_MAX,minval,maxval);


    exit(EXIT_SUCCESS);
}


