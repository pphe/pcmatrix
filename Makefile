CC=gcc
CFLAGS=-pthread -I. -Wall -Wno-int-conversion -D_GNU_SOURCE
SOURCE=src
TEST=test

binaries=pcMatrix counter matrix prodcons

all: $(binaries)

pcMatrix: $(SOURCE)/counter.c $(SOURCE)/prodcons.c $(SOURCE)/matrix.c $(SOURCE)/pcmatrix.c 
	$(CC) $(CFLAGS) $^ -o $@

prodcons: $(SOURCE)/counter.c $(SOURCE)/matrix.c $(SOURCE)/prodcons.c $(TEST)/test_prodcons.c
	$(CC) $(CFLAGS) $^ -o $@
	
counter: $(SOURCE)/counter.c $(TEST)/test_counter.c
	$(CC) $(CFLAGS) $^ -o $@

matrix: $(SOURCE)/matrix.c $(TEST)/test_matrix.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -f $(binaries) *.o


 
