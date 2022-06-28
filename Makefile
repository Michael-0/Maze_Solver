#usage:
#	@echo "Usage:"
#	@echo "	    1) dependencies:	Download the EasyBMP library sources."
#	@echo "	    2) easyexec:	Compile and link the 'easyexec' executable."
#	@echo "	    3) clean:		Removes dependencies and compiled files."

# linking
maze_solver: maze_solver.o
	g++ -g -o maze_solver maze_solver.o includes/EasyBMP.o queue.o
# compilation
maze_solver.o: maze_solver.cpp includes/EasyBMP.o queue.o
	g++ -std=c++11 -c -g maze_solver.cpp -Iincludes

# Easy BMP library compilation
includes/EasyBMP.o:
	g++ -c -g includes/EasyBMP.cpp -o includes/EasyBMP.o
# queue Compilation
includes/queue.o:
	g++ -c -g queue.cpp -o includes/queue.o

# Download and unzip the EasyBMP library.
.PHONY: dependencies
dependencies: includes
	wget http://prdownloads.sourceforge.net/easybmp/EasyBMP_1.06.zip
	unzip EasyBMP_1.06.zip -d includes && rm EasyBMP_1.06.zip

# Creates the includes subdirectory if it does not exist
includes:
	mkdir -p includes

.PHONY: clean
clean:
	-rm -r easyexev *.o *.bmp *.zip *.tar.gz includes 2> /dev/null || true

.PHONY: archive
archive:
	tar -cvzf $(USER)_maze_solver.tar.gz maze_solver.cpp queue.h queue.cpp Makefile
