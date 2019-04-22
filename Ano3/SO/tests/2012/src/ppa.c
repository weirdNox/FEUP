/* ppa.c
 *  The Hungry Birds Problem - create threads without arguments and wait for their finishing (no values received)!

 Program invocation:
 ./ppa <n. babybirds> <n. food portions> <n. refills>

 Invocation example:
 ./ppa 3 5 10000
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define MAXBABIES 100

int finish = 0;	// termination of simulation (flagged by parent bird)
int foodbits = 0;	// is the current number of bits of food in the "food-teat"

struct parentarg {	// conveys info to parent bird
	int f;	// number of bits of food of each refill
	long r;	// number of refills - parent bird can then retire!
	int *working;	// ptr to binary state of parent bird
};
struct babyarg {	// conveys info to baby birds
	int id;	// baby identification
	int *eating;	// ptr to number of babies that are eating at a time
};

void *parent(void *);	// parent thread
void *baby(void *);	// baby thread

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
	int BabyCount, FoodCap;
	long RefillCount;
    int Working = 0;
    int Eating = 0;
    struct parentarg ParentArg;
	struct babyarg BabyArgs[MAXBABIES];
	pthread_t ParentThread, BabyThreads[MAXBABIES];

    if(argc != 4) {
        printf("Program invoked with wrong number of arguments.\n");
        printf("Program usage: %s <n. babybirds> <n. food portions> <n. refills>\n", argv[0]);
        exit(-1);
    }
    else {
        BabyCount = atoi(argv[1]);
        FoodCap = atoi(argv[2]);
        RefillCount = atoi(argv[3]);
	}

    printf("\nSimulation started\n");

    pthread_create(&ParentThread, 0, parent, 0);
    for(int I = 0; I < BabyCount; ++I) {
        pthread_create(BabyThreads + I, 0, baby, 0);
    }

    pthread_join(ParentThread, 0);
    for(int I = 0; I < BabyCount; ++I) {
        pthread_join(BabyThreads[I], 0);
    }

    printf("\nSimulation finished\n");
    exit (0);
}


void *parent(void *arg) {
    printf ("\n\tParent starting");
    printf ("\n\tParent finishing");
    return NULL;
}


void *baby(void *arg) {
    printf ("\n   Baby bird beginning");
    printf ("\n   Baby bird finishing");
    return (NULL);
}
