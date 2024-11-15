flags = -Wall -O2 -std=c2x
ldflags =

all: clean tree # 1st clean if binaries then make tree

tree: tree.o # tree dept on tree.o and the command uses `cc` compiler with flags expanded to -Wall blah blah, $^ expnads the prereqs, $@ expands to target i.e tree
	cc ${flags} $^ -o $@ ${ldflags}


tree.o: tree.c # tree.o dept on tree.c and the command uses `cc` compiler with flags expanded to -Wall blah blah
	cc ${flags} -c $^	

clean: # remove intermediate object files everytime
	rm -f *.o tree 







