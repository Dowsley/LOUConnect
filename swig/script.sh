swig -python -Isrc AVL.i
gcc -c -fPIC src/AVL.c AVL_wrap.c -I/usr/include/python3.7m
gcc -shared -fPIC AVL.o AVL_wrap.o -o _AVL.so
