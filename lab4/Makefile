.PHONY: build_main build_tests run_main run_tests clean_main clean_tests main tests

build_main:
	gcc main.c tree.c -o main

build_tests:
	gcc tests.c tree.c -o tests

run_main: build_main
	./main

run_tests: build_tests
	./tests

clean_main:
	rm -f main

clean_tests:
	rm -f tests

clean:
	rm -f main tests

main: build_main run_main clean_main
tests: build_tests run_tests clean_tests