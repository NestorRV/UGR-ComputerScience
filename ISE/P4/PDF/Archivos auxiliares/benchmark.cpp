#include <iomanip>
#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

double t1secuencial, t2secuencial, t1paralelo, t2paralelo, t1, t2;
double M1[1000][1000], M2[1000][1000], M3[1000][1000];

double media(const vector<double> &elementos){
	double suma=0;
	for(int i=0; i<elementos.size(); i++)
		suma+=elementos[i];
	return suma/elementos.size();
}

void producto_secuencial(){
	int i, j, k;
	t1secuencial = omp_get_wtime();
	for (i=0; i<1000; i++){
		for(j=0; j<1000; j++){
			for (k=0; k<1000; k++){
				M1[i][j] = M1[i][j] + (M2[i][k]*M3[k][j]);
			}
		}
	}
	t2secuencial=omp_get_wtime();
}

void producto_paralelo(){
	int i, j, k;
	#pragma omp parallel shared(M1,M2,M3) private(i,j,k)
	{
		//Medida de tiempo
		#pragma omp single
		{
			t1paralelo = omp_get_wtime();
		}
		#pragma omp for schedule (runtime)
		for(i=0;i<1000; i++){
			for(j=0;j<1000; j++){
				for(k=0;k<1000; k++){
					M1[i][j] = M1[i][j] + M2[i][k] * M3[k][j];
				}
			}
		}
		//Medida de tiempo
		#pragma omp single
		{
			t2paralelo = omp_get_wtime();
		}
	}
}

int main(int argc, char *argv[]){
	vector<double> vtsecuencia, vtparalelo;
	int i, j, iteraciones = 0;
	cout << "Número de repeticiones del cálculo (n > 0): ";
	cin >> iteraciones;

	for (i=0; i<1000; i++){
		for (j=0; j<1000; j++){
			M1[i][j] = 0;
			M2[i][j] = 2;
			M3[i][j] = 2;
		}
	}

	for(int i=0; i<iteraciones; i++){
		producto_secuencial();
		vtsecuencia.push_back(t2secuencial - t1secuencial);
	}

	for (i=0; i<1000; i++){
		for (j=0; j<1000; j++){
			M1[i][j] = 0;
			M2[i][j] = 2;
			M3[i][j] = 2;
		}
	}

	for(int i=0; i<iteraciones; i++){
		producto_paralelo();
		vtparalelo.push_back(t2paralelo - t1paralelo);
	}

	t1 = media(vtsecuencia);
	t2 = media(vtparalelo);

	//Para evitar que el compilador suprima codigo:
	M1[0][0]++; M1[0][0]--;
	M2[0][0]++; M2[0][0]--;
	M3[0][0]++; M3[0][0]--;

	cout << "Tiempo secuencial en segundos: " << t1 << ". Puntuacion secuencial: " << 10000/t1 << endl;
	cout << "Tiempo paralelo en segundos: " << t2 << ". Puntuacion paralelo: " << 10000/t2 << endl;

	return 0;
}
