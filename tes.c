#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int *gerar_vetor_inteiro(int n);
double media(double * v,int t);

int ranckSort(int t) {
    int* vetor = NULL;
    vetor = gerar_vetor_inteiro(t);

    int con = 0;
    int* vetor_ordenado = (int*)malloc(sizeof(int) * t);
       
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < t; j++) {
            if (vetor[i] < vetor[j]) {
                con++;
            }
        }
        vetor_ordenado[con] = vetor[i];
        con = 0;
    }
   
   
    free(vetor);
    free(vetor_ordenado);
    return 1;
}

int main() {
	double tempo, tempos[10],tempoMedio;
    for (int i = 10; i < 10000000; i *= 10) {
    	for(int j = 0;j < 10; j++){
    		clock_t start = clock();
    		ranckSort(i);
    		clock_t end = clock();
    		tempo =((double)(end - start)) / CLOCKS_PER_SEC;
    		tempos[j] = tempo;
		}
		tempoMedio = media(tempos,10);
		
        printf("Para o tamanho %i o tempo foi: %.5f segundos\n", i, tempoMedio);
    }

    return 0;
}

int* gerar_vetor_inteiro(int n) {
    int* vetor;
    vetor = (int*)malloc(sizeof(int) * n);
    for (long int i = 0; i < n; i++) {
        int num = rand();
        vetor[i] = num;
    }
    return vetor;
}

double media(double * v,int t){
	double soma;
	for (int i = 0; i < t;i++){
		soma += v[i];
	}
	return (soma /(double) t);
}
