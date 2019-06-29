#include <stdlib.h>

void f(long double *a){
	a = (long double *)malloc(sizeof(long double) * 1000);
}

int main(void) {
	long double *a;

        while(1) {
		f(a);
        }
        return 0;
}
