/*
* PP2 - SO-E, May2016 	-	file size evaluation
*
* du : calculate file size (the long way, not by acessing fstat)
*/

#include <unistd.h>

long long du(int fd) {
	char c;
	long long ll = 0;
	while (read (fd, &c, 1) == 1) {
		ll++;
	}
return (ll);
}