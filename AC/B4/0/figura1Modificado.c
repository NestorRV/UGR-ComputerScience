#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct {
	int a;
	int b;
} s[5000];

int main(int argc, char** argv) {
	int i, ii, X1, X2;
	int X1a=0, X2a=0;
	int X1b=0, X2b=0;
	int X1c=0, X2c=0;
	int X1d=0, X2d=0;
	int X1e=0, X2e=0;
	int R[40000];
	struct timespec cgt1, cgt2;
    double tiempo;

    for(i=0; i<5000;i++)  {
		s[i].a = i;
		s[i].b = i;
    }


	clock_gettime(CLOCK_REALTIME, &cgt1);

	for (ii=0; ii<40000;ii++) {

		/*X1=0; X2=0;

		for(i=0; i<5000;i++){
			X1+=2*s[i].a+ii;
			X2+=3*s[i].b-ii;
		}*/

		X1a=0; X2a=0;
		X1b=0; X2b=0;
		X1c=0; X2c=0;
		X1d=0; X2d=0;
		X1e=0; X2e=0;
		for(i=0; i<5000;i+=5) {
			X1a+=2*s[i].a+ii;
			X1b+=2*s[i+1].a+ii;
			X1c+=2*s[i+2].a+ii;
			X1d+=2*s[i+3].a+ii;
			X1e+=2*s[i+4].a+ii;

			X2a+=3*s[i].b-ii;
			X2b+=3*s[i+1].b-ii;
			X2c+=3*s[i+2].b-ii;
			X2d+=3*s[i+3].b-ii;
			X2e+=3*s[i+4].b-ii;
		}
		X1 = X1a+X1b+X1c+X1d+X1e;
		X2 = X2a+X2b+X2c+X2d+X2e;

		if (X1<X2)
			R[ii]=X1;
		else
			R[ii]=X2;
	}

	clock_gettime(CLOCK_REALTIME, &cgt2);
	tiempo = (double) (cgt2.tv_sec - cgt1.tv_sec)+ (double) ((cgt2.tv_nsec - cgt1.tv_nsec) / (1.e+9));
	printf("a: %i - b: %i", R[5000], s[4999].a);
	printf(" Tiempo(seg.): %11.9f\n", tiempo);

}
