#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int *gerar_vetor_inteiro(int n);

int ranckSort(int t) {
    int* vetor = NULL;
    vetor = gerar_vetor_inteiro(t);

    
    int* vetor_ordenado = (int*)malloc(sizeof(int) * t);
    double tempo;

    clock_t start = clock();
	int con = 0;
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < t; j++) {
            if (vetor[i] < vetor[j]) {
                con++;
            } else if (vetor[i] == vetor[j] && i > j){
            	con++;
			}
        }
        vetor_ordenado[con] = vetor[i];
        con = 0;
    }
    clock_t end = clock();
    tempo =((double)(end - start)) / CLOCKS_PER_SEC;


    printf("Para o tamanho %i o tempo foi: %.5f segundos\n", t, tempo);
    free(vetor);
    free(vetor_ordenado);
    return 1;
}

int main() {
    for (int i = 10; i < 10000000; i *= 10) {
        ranckSort(i);
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

