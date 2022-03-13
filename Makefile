cflags = -O3

all: tests benchmarks run_tests run_benchmarks

run_tests: tests
	./bin/run_tests

tests:
	mkdir -p bin
	g++ $(cflags) src/test_main.cpp -o bin/run_tests

run_benchmarks: benchmarks
	./bin/run_benchmarks

benchmarks:
	mkdir -p bin
	g++ $(cflags) src/benchmark_main.cpp -o bin/run_benchmarks

