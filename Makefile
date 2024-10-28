build:
	gcc -g -o tema3 main.c functiiTask1.c genericGraf.c

run: 
	./tema3 $(ARGS)

clean:
	rm tema3

valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema3 1