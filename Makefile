# target, subdir, objects in current dir
TARGET	= ToyRayTracing
PPM = ToyRayTracing
SUBDIRS	= src
OBJECTS	= 

# get the ppm file
all: build clean generate-ppm

# get the executable file
build: subdirs ${OBJECTS} 
	${CC} -o ${TARGET} $$(find ./${SUBDIRS} -name '*.o')

clean: cleansubdirs
	rm -f ${OBJECTS}

generate-ppm: $(TARGET)
	./$(TARGET) > ./output/$(PPM).ppm
	@echo -e "\nDone! See $(PPM).ppm."


# path of "make global scripts"
# NOTE, use absolute path. export once, use in all subdirs
export PROJECTPATH=${PWD}
export MAKEINCLUDE=${PROJECTPATH}/Makefile.inc

# include "make global scripts"
include ${MAKEINCLUDE}
