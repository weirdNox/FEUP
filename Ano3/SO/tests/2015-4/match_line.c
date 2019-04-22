/*** TO THE TEST: since here ***/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int match_line(int fd, char *str) {
	/* fd	- file descriptor of already open file
	 * str	- string to search in file, line by line
	 *
	 * returns:
	 *	- number of line that contains str;
	 * 		// new string search (from following line) can begin if function is called again
	 * 	- 0 // meaning End Of File
	 */
#define _MAXLINE__ 32768	// long! Because we don't want buffer to fill!
	char buff[_MAXLINE__] = {'\0'};	// line buffer
	char *pc;	// char pointer in buff
	struct fileslines {
		int fd;
		int linenum;
	};
#define _MAXFILES__ 512
	static struct fileslines fl[_MAXFILES__] = {{0,0}};	// for counting of lines --> stateful function!
	int linenum = 1;	// local counter of lines
	char eol = 0;
	char eof = 0;	// indication of End-Of-Line or End-Of-File

	int nfd = 1;	// new file descriptor?
	int f;
for (f=0; f< _MAXFILES__; f++) {
	if (fl[f].fd == fd) {	// fd was called previously
		linenum = fl[f].linenum;
		nfd = 0;
		break;
		}
	}
if (nfd == 1) {	// first call of fd
	for (f=0; f< _MAXFILES__; f++) {
		if (fl[f].fd == 0) {	// a free slot!
			fl[f].fd = fd;
			fl[f].linenum = 1;
			linenum = 1;
			break;
			}
		}
	}
// IMP: f is fl[] index for current call!
while (1) {
	for (pc = buff; pc != &buff[_MAXLINE__-1]; ++pc) {
		if (read(fd, pc, 1) != 1) {
			*pc = '\0';
			eof = 1;
			break;
			}
		if (*pc == '\n') {
			++pc;
			*pc = '\0';
			eol = 1;
			break;
			}
		} // for()
	// Here when: 1-EOF; 2-EOL; //3- buff full!! - not considered!
	if (eof) {
		if (strstr (buff, str) == NULL) {
			fl[f].linenum = 0;
			return 0;
			}
		else {
			fl[f].linenum = linenum;
			return linenum;
			}
		}
	if (eol) {
		if (strstr (buff, str) == NULL) {
			(fl[f].linenum)++;
			linenum++;
			continue;
			}
		else {
			(fl[f].linenum)++;
			return linenum++;
			}
		}
	else {
		buff[_MAXLINE__-1] = '\0';
		fprintf(stderr, "\nCritical error: line buffer too small!\n");
		exit(-1);
		}
	} // while()
} // match_line()
/*** TO THE TEST: up till here ***/
