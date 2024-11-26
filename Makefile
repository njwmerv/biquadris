CXX = g++-14.2.0
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -g
EXEC = main
SOURCES = $(wildcard *.cc)			# source files (*.cc)
OBJECTS = ${SOURCES:.cc=.o}			# object files forming executable
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

${OBJECTS} : ${MAKEFILE_NAME}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}