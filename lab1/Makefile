.PHONY: build_main build_tests run_main run_tests clean_main clean_tests main tests

build_main:
	gcc main.c -o main

build_tests:
	gcc tests.c -o tests

run_main: build_main
	./main

run_tests: build_tests
	./tests

clean_main:
	rm -f main

clean_tests:
	rm -f tests

main: build_main run_main clean_main
tests: build_tests run_tests clean_tests

