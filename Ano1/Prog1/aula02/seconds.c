#include <stdio.h>

int main()
{
    long startSeconds;
    printf("Insira um numero: ");
    scanf("%ld", &startSeconds);

    int days, hours, minutes, seconds;
    seconds = startSeconds;
    minutes = seconds / 60;
    seconds -= minutes*60;
    hours = minutes / 60;
    minutes -= hours * 60;
    days = hours / 24;
    hours -= days * 24;

    printf("%ld segundo%s corresponde%s a %d dia%s, %d hora%s, %d minuto%s e %d segundo%s.\n",
           startSeconds, startSeconds == 1? "" : "s", startSeconds == 1? "" : "m",
           days, days == 1? "" : "s", hours, hours == 1? "" : "s", minutes, minutes == 1? "" : "s",
           seconds, seconds == 1? "" : "s");

    return 0;
}
