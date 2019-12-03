swig -python -Isrc AVL.i
gcc -c -fPIC src/AVL.c AVL_wrap.c -I/usr/include/python3.8
gcc -shared -fPIC AVL.o AVL_wrap.o -o _AVL.so
