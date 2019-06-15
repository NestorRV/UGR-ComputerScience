folders = obj bin Resultados
all: make_folders bin/main

make_folders:
	mkdir -p ${folders}
bin/main : obj/main.o obj/Utilidades.o obj/PreparacionDatos.o obj/K-NN.o obj/Relief.o obj/LocalSearch.o obj/Evolutivos.o obj/EnfriamientoSimulado.o obj/ILS.o
	g++ -g -O2 -std=c++11 -o bin/main obj/main.o obj/Utilidades.o obj/PreparacionDatos.o obj/K-NN.o obj/Relief.o obj/LocalSearch.o obj/Evolutivos.o obj/EnfriamientoSimulado.o obj/ILS.o
obj/main.o : src/main.cpp
	g++ -g -O2 -std=c++11 -c -I./include -o obj/main.o src/main.cpp
obj/Utilidades.o : src/Utilidades.cpp include/Utilidades.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/Utilidades.o src/Utilidades.cpp
obj/PreparacionDatos.o : src/PreparacionDatos.cpp include/PreparacionDatos.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/PreparacionDatos.o src/PreparacionDatos.cpp
obj/K-NN.o : src/K-NN.cpp include/K-NN.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/K-NN.o src/K-NN.cpp
obj/Relief.o : src/Relief.cpp include/Relief.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/Relief.o src/Relief.cpp
obj/LocalSearch.o : src/LocalSearch.cpp include/LocalSearch.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/LocalSearch.o src/LocalSearch.cpp
obj/Evolutivos.o : src/Evolutivos.cpp include/Evolutivos.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/Evolutivos.o src/Evolutivos.cpp
obj/EnfriamientoSimulado.o : src/EnfriamientoSimulado.cpp include/EnfriamientoSimulado.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/EnfriamientoSimulado.o src/EnfriamientoSimulado.cpp
obj/ILS.o : src/ILS.cpp include/ILS.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/ILS.o src/ILS.cpp
clean:
	rm -r obj/ bin/ Resultados/
