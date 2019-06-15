#include <iostream>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]){
	double t_lectura1, t_escritura1, t_lectura2, t_escritura2, t_lectura, t_escritura;
	int i, hebra = -1;
	string line1, line2, line3, line4;
	char file1[100];
	char file2[100];
	char file3[100];
	char file4[100];

	strcpy(file1, argv[1]);	strcat(file1, "file1.txt");
	strcpy(file2, argv[1]);	strcat(file2, "file2.txt");
	strcpy(file3, argv[1]);	strcat(file3, "file3.txt");
	strcpy(file4, argv[1]);	strcat(file4, "file4.txt");

	cout << file1 << endl;
	cout << file2 << endl;
	cout << file3 << endl;
	cout << file4 << endl;

	omp_set_num_threads(4);

	ofstream output_file1(file1);
	ofstream output_file2(file2);
	ofstream output_file3(file3);
	ofstream output_file4(file4);

	#pragma omp parallel private(i)
	{
	//Medida de tiempo
	#pragma omp single
	{
	t_escritura1 = omp_get_wtime();
	}
	#pragma omp for
	for(i=0;i<25000000; i++){
		hebra = omp_get_thread_num();
		switch(hebra)
		{
	   case 0:
		output_file1 << "Iteracion " << i << " ABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789 * Hebra 0 \n";
		break;
	   case 1:
		output_file2 << "Iteracion " << i << " ABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789 * Hebra 1 \n";
		break;
	   case 2:
		output_file3 << "Iteracion " << i << " ABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789 * Hebra 2 \n";
		break;
	   case 3:
		output_file4 << "Iteracion " << i << " ABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789 * Hebra 3 \n";
		break;
		}
	}
	//Medida de tiempo
	#pragma omp single
	{
	t_escritura2 = omp_get_wtime();
	}
	}

	output_file1.close();
	output_file2.close();
	output_file3.close();
	output_file4.close();

	ifstream input_file1(file1);
	ifstream input_file2(file2);
	ifstream input_file3(file3);
	ifstream input_file4(file4);

	#pragma omp parallel private(i)
	{
	//Medida de tiempo
	#pragma omp single
	{
	t_lectura1 = omp_get_wtime();
	}
	hebra = omp_get_thread_num();
	switch(hebra)
	{
	case 0:
	while(getline(input_file1, line1))
		line1.size();
	break;
	case 1:
	while(getline(input_file2, line2))
		line2.size();
	break;
	case 2:
	while(getline(input_file3, line3))
		line3.size();
	break;
	case 3:
	while(getline(input_file4, line4))
		line4.size();
	break;
	}
	//Medida de tiempo
	#pragma omp single
	{
		t_lectura2 = omp_get_wtime();
	}
	}

	input_file1.close();
	input_file2.close();
	input_file3.close();
	input_file4.close();

	t_escritura = t_escritura2 - t_escritura1;
	t_lectura = t_lectura2 - t_lectura1;

	cout << "Tiempo de escritura en segundos: " << t_escritura << endl;
	cout << "Tiempo de lectura en segundos: " << t_lectura << endl;

	return 0;
}
