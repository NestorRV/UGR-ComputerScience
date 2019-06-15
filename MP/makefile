folders = obj bin

all : make_folders bin/constructivo

make_folders : 
		mkdir -p ${folders}
bin/constructivo : obj/main.o obj/conjunto.o obj/cdconjuntos.o
		@echo Modificando bin/constructivo
		g++ -o bin/constructivo obj/main.o obj/conjunto.o obj/cdconjuntos.o
obj/main.o : src/main.cpp include/conjunto.h include/cdconjuntos.h
		@echo Modificando obj/main.o
		g++ -c -I./include -o obj/main.o src/main.cpp
obj/conjunto.o : src/conjunto.cpp include/conjunto.h
		@echo Modificando obj/conjunto.o
		g++ -c -I./include -o obj/conjunto.o src/conjunto.cpp
obj/cdconjuntos.o : src/cdconjuntos.cpp include/conjunto.h include/cdconjuntos.h include/conjunto.h
		@echo Modificando obj/cdconjuntos.o
		g++ -c -I./include -o obj/cdconjuntos.o src/cdconjuntos.cpp
clean:
		@echo Borrando obj/* y bin/*
		rm obj/* bin/*
