# Patrick Carra
# make is used to compile binary
# make clean is used to remove all binaries and object files
#
# T1: T1.c
# 	gcc -o T1 T1.c

CC = gcc
CFLAGS = -Wall

all: proj1

proj1: driver.o liblog.a
	$(CC) $(CFLAGS) driver.c -L. -llog -o proj1

driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c liblog.h

clean:
	rm -rf *o  proj1 
