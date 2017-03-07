#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *workFile;
    workFile = fopen("./work.txt", "r");
    if(!workFile)
    {
        puts("Error opening file!");
        exit(-1);
    }

    int numberOfDays = 0;
    int numberOfJobsInDay[30] = {0};
    int numberOfTerminatedJobsInDay[30] = {0};
    char jobWithMostWorkers[100] = "";
    int maxNumOfWorkers = 0;
    for(;;)
    {
        char name[100];
        if(fscanf(workFile, "%99s", name) < 1)
        {
            break;
        }

        int totalNumOfWorkers = 0;
        for(int day = 0;; ++day)
        {
            int numberOfWorkers;
            fscanf(workFile, "%d", &numberOfWorkers);
            if(numberOfWorkers == -1)
            {
                ++numberOfTerminatedJobsInDay[day-1];
                break;
            }

            if(day+1 > numberOfDays)
            {
                numberOfDays = day+1;
            }

            if(numberOfWorkers)
            {
                totalNumOfWorkers += numberOfWorkers;
                ++numberOfJobsInDay[day];
            }
        }

        if(totalNumOfWorkers > maxNumOfWorkers)
        {
            maxNumOfWorkers = totalNumOfWorkers;
            strcpy(jobWithMostWorkers, name);
        }
    }
    fclose(workFile);

    int dayWithMostJobs = 0;
    int dayWithMostTerminations = 0;
    for(int day = 1; day < numberOfDays; ++day)
    {
        if(numberOfJobsInDay[day] > numberOfJobsInDay[dayWithMostJobs])
        {
            dayWithMostJobs = day;
        }
        if(numberOfTerminatedJobsInDay[day] > numberOfTerminatedJobsInDay[dayWithMostTerminations])
        {
            dayWithMostTerminations = day;
        }
    }

    printf("Dia com mais tarefas: %d\n", dayWithMostJobs+1);
    printf("Dia com mais tarefas acabadas: %d\n", dayWithMostTerminations+1);
    printf("Tarefa com mais trabalhadores: %s\n", jobWithMostWorkers);

    return 0;
}
