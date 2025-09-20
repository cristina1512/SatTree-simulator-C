build:
	gcc -o sattree main.c fct.c
run:
	./sattree $(tasknr) $(file_in) $(file_out)
clean:
	rm -f sattree
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./sattree