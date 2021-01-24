all:
	cc main.c serwer.c APIdecoder.c mapa.c -o main -lcurl ../../cJSON/cJSON.o -Wno-stringop-overflow

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

test-reset: all
	./main qwerty_22 reset

test-gra-whole:
	valgrind ./main qwerty_22 E M E M E M E M E M E M E M E M E M E Rright M E M E M E Rright M E M E M E Rleft M E M E Rleft M E M E M E Rright M E Rright Rright M Rleft M M Rleft M E Rright M E M E M E Rright M E Rleft M E M E M E M E Rleft M E Rleft M E Rleft M Rright M M M M M Rleft M M Rleft M E M E M E M E M E M E Rright M E M E M E

test-gra-memory:
	valgrind --leak-check=full ./main qwerty_22 E M E M E M E M E M E M E M E M E M E

test-memory:
	valgrind ./main qwerty_22

test-mapa:
	cc mapa_test.c mapa.c -o mapa_test
	./mapa_test
	
clean:
	rm -f main