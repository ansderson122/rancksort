#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int* gerar_vetor_inteiro(int n);


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    
    int t = 10;
    int* vetor = NULL;
    int* vetor_ordenado = NULL;
    int* subvetor = NULL;
    
    
    
    if (rank == 0){
    srand(time(NULL));
    	if (argc > 1){
    		t = atoi(argv[1]);
    	}
      vetor = gerar_vetor_inteiro(t);
      vetor_ordenado = (int *)malloc(sizeof(int) * t);
      
      
      printf("Vetor : ");
        for (int i = 0; i < t; i++) {
            printf("%d ", vetor[i]);
        }
        printf("\n");
    }

    if (rank != 0){
        vetor = (int*)malloc(sizeof(int) * t);
    }
    MPI_Bcast(&t,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(vetor,t,MPI_INT,0,MPI_COMM_WORLD);   
    
    int sub_size = (int)(t/size);

    subvetor = malloc(sub_size*sizeof(int));
    MPI_Scatter(vetor, sub_size, MPI_INT, subvetor,sub_size, MPI_INT, 0, MPI_COMM_WORLD);
   
    int vRankLocal[sub_size];
    for (int i = 0; i < sub_size;i++){
    	vRankLocal[i] = 0;
    }
    
    for (int i = 0; i < sub_size; i++) {
        for (int j = 0; j < t; j++) {
            if (subvetor[i] < vetor[j]){
                vRankLocal[i]++;
            }else if(subvetor[i] == vetor[j] && (rank +(i*size)) > j){
              	vRankLocal[i]++;
            }
        }
    }

    int* vetor_rank = NULL;
    if(rank == 0){
        vetor_rank = malloc(t*sizeof(int));

    }
    
    MPI_Gather(&vRankLocal, sub_size , MPI_INT, vetor_rank, t, MPI_INT, 0, MPI_COMM_WORLD);

    

    
    // Imprime o vetor ordenado no processo 0
    if (rank == 0) {
        for(int i = 0; i < t ; i++){
            vetor_ordenado[vetor_rank[i]] = vetor[i]
        }


        printf("Vetor ordenado: ");
        for (int i = 0; i < t; i++) {
            printf("%d ", vetor_ordenado[i]);
        }
        printf("\n");
        free(vetor_ordenado);
        
    }
	free(vetor);
    
  
    

    MPI_Finalize();
    return 0;
}

int* gerar_vetor_inteiro(int n) {
    int* vetor;
    vetor = (int*)malloc(sizeof(int) * n);
    for (long int i = 0; i < n; i++) {
        int num = rand() % 11;
        vetor[i] = num;
    }
    return vetor;
}
