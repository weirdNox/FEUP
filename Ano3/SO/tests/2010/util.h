#include <pthread.h>

#define NT 2

/* Type of variable shared by all threads */
typedef struct {
    int *array; /* pointer to the array to be initialized */
    int len;	/* length of "array" */
    int next;	/* index of the next element of the array array
	         *   to be initialized */
    int cnt[NT]; /* array that keeps track of how many
		  *  elements each thread has initialized so far*/
    pthread_mutex_t lock; /* for concurrency control */
} vector_t;

/* Type of argument to pass to the checker thread */
typedef struct {
    int argc;          // to be initialized with argc of main()
    char **argv;       // to be initialized with argv of main()
    vector_t *vector;  // to be initialized with address of shared structure
} chkr_arg_t;

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
int parse_int(char *str, int *n, int i);

/* Description:
 *	Prints struct to be shared by initialization threads
 * Inputs:
 *	vp - pointer to shared variable to print
 * Returns:
 *      Not applicable
 */
void print_vector(vector_t *vp);

/* Description:
 *	Shows how to invoke the program
 * Inputs:
 *	name: program name (argv[0])
 * Returns:
 *      Not applicable
 */
void print_usage(char *name);

/* Description:
 *	Checks invariants
 * Inputs:
 *	address of previously initialized struct of type chk_arg_t
 * Returns:
 *      Not applicable
 */
void *checker(void *);
