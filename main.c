#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int *gerar_vetor_inteiro(int n);


void main(){
    int tamanho = pow(10,5);
    int* vetor = NULL;
	vetor = gerar_vetor_inteiro(tamanho);
    double inicio, fim, tempo_serial,tempo_paralelo; 


    // incio do SERIAL ------------------------------------------
    printf("incio da serial \n");
    inicio = omp_get_wtime();
   	
	int con = 0; 
   	int vetor_ordenado[tamanho];
   	
   	
   	for(int i = 0; i < tamanho; i++){
   		for(int j = 0; j < tamanho; j++){
   			if (vetor[i] < vetor[j]){
   				con++;
			}
		}
		vetor_ordenado[con] = vetor[i];
		con = 0; 
	}
   	
   	/*
   	printf(" \n |");
	for (int i=0;i<tamanho;i++){
		printf(" %i |",vetor_ordenado[i]);
	}
	*/
    fim = omp_get_wtime();
    tempo_serial = fim - inicio;

    printf("Tempo  %f \n\n",tempo_serial);

    // fim do SERIAL ------------------------------------------

  
    // inicio do paralelo com região critica 

    printf("inicio do paralelo\n");
  	inicio = omp_get_wtime();
  	
   	int vetor_ordenado2[tamanho];

    #pragma omp parallel  num_threads(4)
    {
		int con2 = 0; 
      	#pragma omp for
		   	for(int i = 0; i < tamanho; i++){
		   		for(int j = 0; j < tamanho; j++){
		   			if (vetor[i] < vetor[j]){
		   				con2++;
					}
				}
				vetor_ordenado2[con2] = vetor[i];
				con2 = 0; 
			}
    }


    fim = omp_get_wtime();
    tempo_paralelo = fim - inicio;
    printf("Tempo  %f \n\n",tempo_paralelo);



    printf("Execu��o serial: %.5f \n",tempo_serial);
    printf("Execu��o paralela: %.5f \n",tempo_paralelo);
    double speedup = tempo_serial/tempo_paralelo;
	printf("Speedup: %.4f\n", speedup);
	printf("Eficiencia: %.4f\n\n",speedup/4.0);
    


}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    long int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand());
        vetor[i] = num;
    }
    return vetor;
}



