all: tests run

run:
	./bin/test_main

tests:
	mkdir -p bin
	g++ src/test_main.cpp -o bin/test_main


