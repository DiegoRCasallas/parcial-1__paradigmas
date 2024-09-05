#include <stdio.h>
#include <time.h>

/*
ARGUMENTACION

La funcion recursiva es menos eficiente debido al constante uso de la pila para almacenar los datos, ademas
con valore muy grandes la pila puede llenarse y el programa no funcionar. Por el contrario, la 
funcion iterativa hace un uso minimo de memoria porque utiliza una variable acumulativa para el resultado


Ejemplo: ejecucion de programa que calcula faltorial de 10,
se muestran los tiempos del uso de los dos estilos de programacion

introduce numero:  10

 El factorial (Iterativo) es: 3628800
Tiempo de ejecución recursivo: 0.00000000 segundos

 El factorial (Recursivo) es: 3628800
 Tiempo de ejecución iterativo: 0.00000200 segundos
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


clock_t inicio, fin;
double tiempoIterativo, tiempoRecursivo;
int x;

printf("\nintroduce numero:  ");
scanf("%d",&x);

inicio = clock();
int resultadoRecursivo = factorialRecursivo(x);
fin = clock();
tiempoRecursivo = (double)(fin - inicio) / CLOCKS_PER_SEC;


inicio = clock();
int resultadoIterativo = factorialIterativo(x);
fin = clock();
tiempoIterativo = (double)(fin - inicio) / CLOCKS_PER_SEC;


printf("\n El factorial (Iterativo) es: %d \n",resultadoIterativo);
printf("Tiempo de ejecución recursivo: %.8f segundos\n", tiempoIterativo);

printf("\n El factorial (Recursivo) es: %d \n ",resultadoRecursivo);
printf("Tiempo de ejecución iterativo: %.8f segundos\n", tiempoRecursivo);
return 0;
}