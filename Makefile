all:
	windres icon/resource.rc -o resource.o
	g++ src/*.cpp resource.o -o task-manager.exe
