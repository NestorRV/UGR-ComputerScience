#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <vector>

using namespace std;

const int UMBRAL_QS = 50;

static void insercion_lims(int T[], int inicial, int final){
   int i, j;
   int aux;
   for (i = inicial + 1; i < final; i++) {
      j = i;
      while ((T[j] < T[j-1]) && (j > 0)) {
         aux = T[j];
         T[j] = T[j-1];
         T[j-1] = aux;
         j--;
      };
   };
}

static void dividir_qs(int T[], int inicial, int final, int & pp){
  int pivote, aux;
  int k, l;

  pivote = T[inicial];
  k = inicial;
  l = final;
  do {
    k++;
  } while ((T[k] <= pivote) && (k < final-1));
  do {
    l--;
  } while (T[l] > pivote);
  while (k < l) {
    aux = T[k];
    T[k] = T[l];
    T[l] = aux;
    do k++; while (T[k] <= pivote);
    do l--; while (T[l] > pivote);
  };
  aux = T[inicial];
  T[inicial] = T[l];
  T[l] = aux;
  pp = l;
};

static void quicksort_lims(int T[], int inicial, int final){
  int k;
  if (final - inicial < UMBRAL_QS) {
    insercion_lims(T, inicial, final);
  } else {
    dividir_qs(T, inicial, final, k);
    quicksort_lims(T, inicial, k);
    quicksort_lims(T, k + 1, final);
  };
}

inline static void insercion(int T[], int num_elem){
  insercion_lims(T, 0, num_elem);
}

inline void quicksort(int T[], int num_elem){
  quicksort_lims(T, 0, num_elem);
}

vector<int> EliminaRepetidos(int T[], int n){
   quicksort(T, n);
   int auxiliar = T[0];
   vector<int> salida;
   salida.push_back(auxiliar);
   for(int i = 1; i < n; i++){
      if(T[i] != auxiliar){
         salida.push_back(T[i]);
         auxiliar = T[i];
      }
   }

   return salida;
}

double uniforme(){
   int t = rand();
   double f = ((double)RAND_MAX+1.0);
   return (double)t/f;
}

int main(int argc, char * argv[]) {
   vector<int> resultado;
   chrono::high_resolution_clock::time_point tantes, tdespues;
   chrono::duration<double> transcurrido;
   if (argc != 2) {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
   }

   int n = atoi(argv[1]);

   int * v = new int[n];
   assert(v);

   srand(time(0));
   for (int j=0; j<n; j++) {
      double u=uniforme();
      int k=(int)(n*u);
      v[j]=k;
   }

   tantes = chrono::high_resolution_clock::now();
   resultado = EliminaRepetidos(v, n);
   tdespues = chrono::high_resolution_clock::now();
   transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
   cout << n << " " << transcurrido.count() << endl;
}
