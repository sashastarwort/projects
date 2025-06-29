.PHONY: greet build rebuild run clean
greet:
	@echo " build : fast rebuild / build"
	@echo " rebuild : full rebuild"
	@echo " run : run after fast rebuild / build"
	@echo " clean : perform full clean"

build: main
rebuild: clean main
run: main
	./main

clean:
	rm -rvf *.o main

main: main.c
	gcc -o main main.c -pthread -lm
