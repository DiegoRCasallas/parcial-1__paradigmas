#include <stdio.h>


/*
ARGUMENTACION

La funcion recursiva es menos eficiente debido al constante uso de la pila para almacenar los datos, ademas
con valore muy grandes la pila puede llenarse y el programa no funcionar. Por el contrario, la 
funcion iterativa hace un uso minimo de memoria porque utiliza una variable acumulativa para el resultado


*/
int factorialIterativo(int num){
    for(int i = num ; i-1 != 0 ; i--){
        num=num*(i-1);
    }     
}

int factorialRecursivo(int num){
    if (num==0) return 1; 
    if (num==1 )return 1;
    return num*factorialRecursivo(num-1);
}
int main(void)
{
int x;
printf("\nintroduce numero:  ");
scanf("%d",&x);
int resultadoRecursivo = factorialRecursivo(x);
printf("\n El factorial (Iterativo) es: %d \n",resultadoRecursivo);
int resultadoIterativo = factorialIterativo(x);
printf("\n El factorial (Recursivo) es: %d \n ",resultadoIterativo);
return 0;
}