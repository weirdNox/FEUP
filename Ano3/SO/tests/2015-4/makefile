# Makefile
#
ppa: ppa.c
	cc -Wall ppa.c match_line.c -o ppa -pthread
ppb: ppb.c
	cc -Wall ppb.c match_line.c -o ppb -pthread
ppc: ppc.c
	cc -Wall ppc.c match_line.c -o ppc -pthread
ppd: ppd.c
	cc -Wall ppd.c match_line.c -o ppd -pthread

clean:
	rm -f ppa ppb ppc ppd match_line.o
