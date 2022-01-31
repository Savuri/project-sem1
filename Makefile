default:
	@ echo This is the help
	@ echo all   - build project
	@ echo clean - remove all objects

all: main.c fun.asm 
	@ gcc -Wall -m32 -std=c99 -c -o main.o main.c
	@ nasm -Wall -f elf32 -o fun.o fun.asm
	@ gcc -Wall -m32 -o main main.o fun.o -lm

clean:
	@ rm main.o
	@ rm fun.o