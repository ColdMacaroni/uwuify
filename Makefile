uwufy-linux64:
	clang -m64 -Wall -Wextra -pedantic -o uwufy uwuify.c

uwufy-linux32:
	clang -m32 -Wall -Wextra -pedantic -o uwufy32 uwuify.c

clean:
	rm uwufy*
