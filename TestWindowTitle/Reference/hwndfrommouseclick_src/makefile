all: main.exe

main.res: main.rc
	rc main.rc
	
main.exe: main.c main.res
	cl main.c main.res user32.lib