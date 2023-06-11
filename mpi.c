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
    MPI_Bcast(&t,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&vetor,1,MPI_INT,0,MPI_COMM_WORLD);
 
   MPI_Win win;
   MPI_Win_allocate_shared(t *sizeof(int),sizeof(int), MPI_INFO_NULL,MPI_COMM_WORLD,&vetor_ordenado,&win );
   
   MPI_Win_fence(0,win);

 
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    int sub_size = (int)(t/size);
    int aux[sub_size];
    
    printf("sub_size %i \n",sub_size);
    printf("size %i \n",size);
    
    for(int i = rank ; i < sub_size ; i += size){
    	aux[i] = vetor[i];
    }
    
    int local_rank[sub_size];
    for (int i = 0; i < sub_size;i++){
    	local_rank[i] = 0;
    }
    
    for (int i = 0; i < sub_size; i++) {
        for (int j = 0; j < t; j++) {
            if (aux[i] < vetor[j]){
                local_rank[i]++;
            }else if(aux[i] == vetor[j] && i > j){
              	local_rank[i]++;
            }
        }
    }
    
    
    for(int i = 0; i < sub_size;i++ ){
    	//printf("local_rank %i \n",local_rank[i]);
    	vetor_ordenado[local_rank[i]] = aux[i];
    }
    

    MPI_Barrier(MPI_COMM_WORLD);
    // Imprime o vetor ordenado no processo 0
    if (rank == 0) {
        printf("Vetor ordenado: ");
        for (int i = 0; i < t; i++) {
            printf("%d ", vetor_ordenado[i]);
        }
        printf("\n");
        
    }
	free(vetor);
    
  
    free(vetor_ordenado);

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
