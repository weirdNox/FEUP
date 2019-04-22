# Makefile
#
ppa: ppa.c
	cc -Wall ppa.c du.c -o ppa -pthread
ppb: ppb.c
	cc -Wall ppb.c du.c -o ppb -pthread
ppc: ppc.c
	cc -Wall ppc.c du.c -o ppc -pthread
ppd: ppd.c
	cc -Wall ppd.c du.c -o ppd -pthread

clean:
	rm -f ppa ppb ppc ppd du.o
