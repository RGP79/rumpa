all:
	cc main.c serwer.c APIdecoder.c mapa.c -o main -lcurl ../../cJSON/cJSON.o

test: all
	./main qwerty_22

test-mov:
	./main qwerty_22 M

test-exp:
	./main qwerty_22 E

test-rotR:
	./main qwerty_22 Rright

test-rotL:
	./main qwerty_22 Rleft

test-reset:
	./main qwerty_22 reset reset

test-gra:
	./main qwerty_22 E M E M E M E M E M E M E M E M E M E 

test-memory:
	valgrind ./main qwerty_22

test-mapa:
	cc mapa_test.c mapa.c -o mapa_test -lm
	./mapa_test
	
clean:
	rm -f main