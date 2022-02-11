# base macro
CC = g++
CFLAGS = -g -Wall -std=c++14
MAKE = make


# recursive make
.PHONY: subdirs ${SUBDIRS} cleansubdirs

subdirs: ${SUBDIRS}

${SUBDIRS}:
	@${MAKE} -C $@ all


# recursive make clean
cleansubdirs:
	@for dir in ${SUBDIRS}; do \
		${MAKE} -C $$dir clean; \
	done


# dependence
%.o: %.cpp
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@
	
%.o: %.cc
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@	