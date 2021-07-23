uwufy: linux64
	$(info Defaulted to Linux64)

linux64:
	clang -m64 -Wall -Wextra -pedantic -o uwufy64 uwuify.c

linux32:
	clang -m32 -Wall -Wextra -pedantic -o uwufy32 uwuify.c

win64:
	x86_64-w64-mingw32-gcc -o uwufy64.exe uwuify.c  

win32:
	i686-w64-mingw32-gcc -o uwufy32.exe uwuify.c

clean:
	rm uwufy*
