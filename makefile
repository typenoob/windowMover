all: main.exe

main.exe: main.c resource.o
	gcc $< -o $@ resource.o

resource.o: resource.rc
	windres.exe -i resource.rc -o resource.o
