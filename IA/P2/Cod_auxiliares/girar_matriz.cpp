#include <cstdlib>
#include <iostream>
#include <ctime>
#define n 5

using namespace std;

int matriz[n][n];
int mTem[n][n];

void gira_izquierda();
void gira_derecha();
void guarda_tem();

void guarda_tem(){
    for(int x = 0; x < n; x++){
        for(int y = 0; y < n; y++){
            matriz[x][y] = mTem[x][y];
            cout<<matriz[x][y]<<" ";
        }
        cout<<endl;
    }
}

void gira_izquierda(){
   int t = 0;
   for(int i = n-1; i >= 0; --i){
      for(int j = 0; j < n; j++){
         mTem[t][j] = matriz[j][i];
      }
      t++;
   }
   guarda_tem();
}

void gira_derecha(){
   int t;
   for(int i = 0; i < n; i++){
      t = 0;
      for(int j = n-1; j >= 0; --j){
         mTem[i][t] = matriz[j][i];
         t++;
      }
   }
   guarda_tem();
}

int main(){
   int opc;
   srand(time(0));
   for(int y = 0; y < 5; y++){
      for(int x = 0; x < 5; x++){
         matriz[y][x] = rand()%10;
         cout<<matriz[y][x]<<" ";
      }
      cout<<endl;
   }

   cout<<endl;
   while(true){
      cout<<"1) Gira Izquierda\n2) Gira Derecha\n3) Salir\n";
      cin>>opc;
      switch(opc){
         case 1:
            gira_izquierda();
            break;
         case 2:
            gira_derecha();
            break;
         case 3:
            return 0;
         default:
            cerr<<"Error";
            cin.get();
            cin.get();
            system("cls");
            break;
      }
   }
   return 0;
}
