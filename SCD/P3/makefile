.SUFFIXES:
.PHONY:    pc,pc2,f,f2,clean

compilador := mpicxx
flagsc     := -g -Wall 

pc: prodcons
	mpirun -np  3 ./prodcons

pc2: prodcons2
	mpirun -np  10 ./prodcons2

f: filosofos
	mpirun -np 10 ./filosofos

f2: filosofos2
	mpirun -np 11 ./filosofos2

%: %.cpp
	$(compilador) $(flagsc) -o $@ $<

clean:
	rm -f prodcons prodcons2 filosofos filosofos2
