#include <stdio.h>
#include <math.h>

int main(int argc,char const *argv[]){
    long i=0;
    while (i<(pow(2,32))-1){
        i++;
    }
    printf("%ld",i);
    return 0;
}
