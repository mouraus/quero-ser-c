#include <stdio.h>


int main (void) {
  int arr1[10] = {-1, 5, -10, 20, 42, 3, 2, 1, 220, 2};
  int arr2[10] = {26, 134, 135, 15, 170, 30, 31, 32, 33, 300};
  
  int tamanhoArr1 = sizeof(arr1)/sizeof(arr1[0]);
  int tamanhoArr2 = sizeof(arr2)/sizeof(arr2[0]);

  int menorDistancia = 0;
  int elementoArr1MenorDistancia;
  int elementoArr2MenorDistancia;

  for (int i = 0; i < tamanhoArr1; i++){
    for(int j = 0; j < tamanhoArr2; j++){
        
        int distancia = arr1[i] - arr2[j];
        if(distancia < 0){
            distancia = distancia * -1;
        }
        if (menorDistancia == 0 || distancia < menorDistancia){
            elementoArr1MenorDistancia = arr1[i];
            elementoArr2MenorDistancia = arr2[j];
            menorDistancia = distancia;
        }

    }
  }
  printf("A menor distancia seria a combinacao do numero %d do array 1 com o numero %d do array 2, que seria %d de distancia\n", elementoArr1MenorDistancia, elementoArr2MenorDistancia, menorDistancia);
  return 0;
}