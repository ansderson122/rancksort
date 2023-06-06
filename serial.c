#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

int *gerar_vetor_inteiro(int n);

int ranckSort(int t){
    int* vetor = NULL;
	vetor = gerar_vetor_inteiro(t);
    
    int con = 0,tempo_exedido = 0; 
   	int vetor_ordenado[t];
    double inicio, fim, tempo;

     
    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        {
            sleep(10);
            tempo_exedido = 1;
        }
        #pragma omp section
        { 
            inicio = omp_get_wtime();
            for(int i = 0; i < t; i++){
   	            for(int j = 0; j < t; j++){
   			        if (vetor[i] < vetor[j]){
   				         con++;
			        }
		        }
		    vetor_ordenado[con] = vetor[i];
		    con = 0; 
	        }
            fim = omp_get_wtime();
            tempo = fim - inicio;
        }
    }
    

   
    if(tempo_exedido){
        printf("Para o tamanha o %i tempo limite excedido. \n",t);
        return 0;
    }

    printf("Para o tamanha %i o tempo foi : %d \n",t,tempo);
    free(vetor);free(vetor_ordenado);
    return 1;   

}


void main(){

    
    for(int i = 10; i < 10000000; i*=10){
        ranckSort(i);
    }


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
