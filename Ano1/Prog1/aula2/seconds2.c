#include <stdio.h>

int main()
{
    long startSeconds;
    printf("Insira um numero: ");
    scanf("%ld", &startSeconds);

    int days, hours, minutes, seconds;
    days = startSeconds / (24*60*60);
    hours = startSeconds / (60*60) - days*24;
    minutes = startSeconds / (60) - days*24*60 - hours*60;
    seconds = startSeconds % 60;

    printf("%ld segundo%s corresponde%s a %d dia%s, %d hora%s, %d minuto%s e %d segundo%s.\n",
           startSeconds, startSeconds == 1? "" : "s", startSeconds == 1? "" : "m",
           days, days == 1? "" : "s", hours, hours == 1? "" : "s", minutes, minutes == 1? "" : "s",
           seconds, seconds == 1? "" : "s");

    return 0;
}
