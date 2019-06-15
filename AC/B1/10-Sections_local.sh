#!/bin/bash
#Se asigna al trabajo el nombre 10-SumaVectoresSections
#PBS -N 10-SumaVectoresSections
#Se asigna al trabajo la cola ac
#PBS -q ac
#Se imprime información del trabajo usando variables de entorno de PBS
#echo "Id. usuario del trabajo: $PBS_O_LOGNAME"
#echo "Id. del trabajo: $PBS_JOBID"
#echo "Nombre del trabajo especificado por usuario: $PBS_JOBNAME"
#echo "Nodo que ejecuta qsub: $PBS_O_HOST"
#echo "Directorio en el que se ha ejecutado qsub: $PBS_O_WORKDIR"
#echo "Cola: $PBS_QUEUE"
#echo "Nodos asignados al trabajo:"
#cat $PBS_NODEFILE
#Se ejecuta 10-SumaVectoresSections, que está en el directorio en el que se ha ejecutado qsub,
#para N potencia de 2 desde 2^16 a 2^26
export OMP_DYNAMIC=FALSE
for ((N=16384;N<67108865;N=N*2))
do
   #$PBS_O_WORKDIR/10-SumaVectoresSections $N
   ./10-SumaVectoresSections $N
done
