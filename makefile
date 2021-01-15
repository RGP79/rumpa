all:
	cc main.c -o main -lcurl ../../cJSON/cJSON.o

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
	valgrind ./main qwerty_22 E M E M E M E M E M E M E M E M E M E

test-memory:
	valgrind ./main qwerty_22
	
clean:
	rm -f main