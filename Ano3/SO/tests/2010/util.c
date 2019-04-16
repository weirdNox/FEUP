#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "util.h"

/* Description: 
 *	Parses a "str", supposedly a command line argument, 
 *        to an integer in base 10.
 * Inputs:
 *      str - string to parse;
 *      np  - address of memory location where to put the integer;
 *      i   - indice of the command line argument being parsed
 * Returns:
 *      0 - in case of error
 *      1 - in case of success (in this case the memory location at
 *            address np will contain the integer
 */
int parse_int(char *str, int *n, int i) {
    char *endptr;

    *n = strtol(str,&endptr, 10);
    if( (endptr == str) || (*endptr != '\0')) {
	printf("argv[%d] is not a number \n", i);
	return 0;
    } else if( *n <= 0 ) {
	    printf("argv[%d] is not positive \n", i);
	    return 0;
    } else
	return 1;
}

/* Description:
 *	Shows how to invoke the program
 * Inputs:
 *	name: program name (argv[0])
 * Returns:
 *      Not applicable
 */

void print_usage(char *name) {
	printf("Usage: %s <n1> <n2> \n"
	       "       where <n1> <n2> are positive integers\n", name);
}

/* Description:
 *	Prints struct to be shared by initialization threads
 * Inputs:
 *	vp - pointer to shared variable to print
 * Returns:
 *      Not applicable
 */

void print_vector(vector_t *vp) {
		int i;
    printf("vp(array = %p, len = %d, next = %d) @ %p\n",
	   vp->array, vp->len, vp->next, vp );
    for( i = 0; i < NT; i++)
	printf("\t vp->cnt[%d] = %d\n", i, vp->cnt[i]);
}


/* Description:
 *	Checks invariants
 * Inputs:
 *	address of previously initialized struct of type chk_arg_t
 * Returns:
 *      Not applicable
 */

#define SLEEP_s		0
#define SLEEP_ns	100000000

#define MAX_IDLE	50

void *checker( void *a) {
    chkr_arg_t *arg = a;
    struct timespec period = {SLEEP_s, SLEEP_ns}; /* 100 ms */

    int nt = NT;	/* Number of threads ; evita int nt = arg->argc - 1; ! */
    int ccnt[NT];		/* Array of no. of elements per thread */
    int cnt[2][NT];		/* For array snapshot */
    int i;
    int asize;			/* Array size */
    int next, cnext;		/* Array snapshot and our own */
    int idle = 0;		/* For detecting inactivity */

    /* Validate arguments */

    asize = 0;
    for( i = 0; i < nt; i++) {
	if( parse_int(arg->argv[i+1], &ccnt[i], i+1) == 0) {
	    printf("checker: exiting.\n");
	    pthread_exit(NULL);
	}
	ccnt[i] *=1000;        /* input arguments are in 1000s */
	asize += ccnt[i];
	cnt[0][i] = cnt[1][i] = 0;
    }

    if( asize != arg->vector->len ) {
	printf("checker: computed size of array does not match len field "
	       "in vector. Exiting \n");
	pthread_exit(NULL);
    }

    /* Endless loop for checking */

    while( 1 ) {
	int activity;		/* For detecting inactivity */

	/* Take a snapshot of the state of the array */

	pthread_mutex_lock(&(arg->vector->lock));
	for( i = 0; i < nt; i++ ) {
	    cnt[1][i] = arg->vector->cnt[i];
	    next = arg->vector->next;
	}
	pthread_mutex_unlock(&(arg->vector->lock));

	/* Check whether the state has changed since the last time */

	for( activity = 0, i = 0; i < nt; i++) {
	    activity |= (cnt[0][i] != cnt[1][i]);
	}
	if (! activity ) {
	    idle++;
	    if( idle >= MAX_IDLE ) {
		printf("Array state: \n");
		printf("\t next = %d\n", next);
		for(i = 0; i < nt; i++)
		    printf("\t cnt[%d] = %d\n", i, cnt[1][i]);
		printf("Has not changed for some time\n");
		break;
	    }
	} else {
	    idle = 0;
	}

	/* Check the invariants */

	for( cnext = 0, i = 0; i < nt; i++ ) {
	    if( cnt[1][i] < 0 )
		printf("Checker: counter of thread %d is negative\n", i);
	    if( cnt[1][i] > ccnt[i] )
		printf("Checker: counter of thread %d is too large\n", i);
	    cnext += cnt[1][i];
	}
	if( cnext != next )
	    printf("Checker: pointer to next element to initialize inconsistent\n");
	if( next < 0 )
		printf("Checker: next field of vector is negative\n");

	if( next > asize )
		printf("Checker: next field of vector is too large\n");

	/* Save the current state of the vector */
	for( i = 0; i < nt; i++ )
	    cnt[0][i] = cnt[1][i];

	nanosleep(&period, NULL);
    }

    /* Final check: have the threads initialized correctly */
    for(i = 0; i < nt; i++ ) {
	cnt[0][i] = 0;
    }

    for(i = 0; i < asize; i++ ) {
	int el = arg->vector->array[i];
	if( el < 0 || el >= nt ) {
	    printf("Checker: element %i of array out of bounds (%d)\n",
		   i, el);
	} else
	    cnt[0][el]++;
    }

    for( i = 0; i < nt; i++) {
	if( cnt[0][i] != ccnt[i] ) {
	    printf("Checker: thread %d initialized %d rather than %d\n",
		   i, cnt[0][i], ccnt[i]);
	} else
	    printf("Checker: thread %d initialized %d as expected\n",
		   i, cnt[0][i]);
    }
    printf("Checker: exiting\n");
    return NULL;
}

