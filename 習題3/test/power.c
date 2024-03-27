#include <stdio.h>
int power(int a,int n){
    int r,i;
    r = 1;
    i = 1;
    while (i<=n) {
        r = r * a;
        i = i + 1;
    }
    return r;
}

int main() {
    printf("power(10,2)=%d\n", power(10,2));
}