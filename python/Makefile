
HEADERS  =   ../include/regions.h
HEADERS +=   ../include/weights.h
HEADERS +=   ../include/auto_infer.h

DATA     =   ../data/weights_float.bin

.PHONY: all clean

all:
	python make_weights.py
	mv weights.h ../include	
	mv regions.h ../include
	mv auto_infer.h ../include
	mv weights_float.bin ../data

clean: 
	rm -rf $(HEADERS) $(DATA)
