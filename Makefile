test: test.c templates/bst_base.c templates/list_base.c templates/list_base.h
	python scripts/new_list_type.py int int
	python scripts/new_bst_type.py int int
	gcc -g -std=gnu11 -Wall -Werror -ggdb -o test test.c int_bst.c int_list.c intmath.c