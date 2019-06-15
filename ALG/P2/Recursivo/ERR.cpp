#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <vector>

using namespace std;

void EliminaRepetidos(int array[], int size);
int merge(int list1[ ], int size1, int list2[ ], int size2, int list3[ ], int size);

int merge(int list1[ ], int size1, int list2[ ], int size2, int list3[ ], int size) {
   int i1, i2, i3;
   if (size1 + size2 > size) {
      return false;
   }
   i1 = 0;
   i2 = 0;
   i3 = 0;
   while (i1 < size1 && i2 < size2) {
      if (list1[i1] < list2[i2]) {
         list3[i3++] = list1[i1++];
      } else {
         list3[i3++] = list2[i2++];
      }
   }
   while (i1 < size1) {
      list3[i3++] = list1[i1++];
   }
   while (i2 < size2) {
      list3[i3++] = list2[i2++];
   }
}

void EliminaRepetidos(int array[], int size, int sin[]) {
   int temp[size];
   int mid, i;

   if (size < 2) {
      return;
   } else {

      mid = size / 2;
      EliminaRepetidos(array, mid, sin);
      EliminaRepetidos(array + mid, size - mid, sin);
      merge(array, mid, array + mid, size - mid, temp, size);
      sin[0] = temp[0];
      int leer = 0;
      for (i = 0; i < size; i++) {
         array[i] = temp[i];
         if (temp[i] != sin[leer]) {
            sin[leer+1] = temp[i];
            leer++;
         }
      }

   }
}

double uniforme() {
   int t = rand();
   double f = ((double) RAND_MAX + 1.0);
   return (double) t / f;
}

int main(int argc, char * argv[]) {
   chrono::high_resolution_clock::time_point tantes, tdespues;
   chrono::duration<double> transcurrido;

   if (argc != 2) {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
   }

   int n = atoi(argv[1]);
   int * v = new int[n];
   int * sin = new int[n];

   assert(v);

   srand(time(0));
   for (int j = 0; j < n; j++) {
      double u = uniforme();
      int k = (int) ((n * u) + 0);
      v[j] = k;
   }

   tantes = chrono::high_resolution_clock::now();
   EliminaRepetidos(v, n, sin);
   tdespues = chrono::high_resolution_clock::now();
   transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
   cout << n << " " << transcurrido.count() << endl;
}
