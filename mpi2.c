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
    int sub_size = (int)(t/size);
    
    
    
    if (rank == 0){
        int vetorRes[sub_size][2];
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
        MPI_Bcast(&t,1,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Bcast(vetor,t,MPI_INT,0,MPI_COMM_WORLD);
        for(int i = 1;i < sub_size; i++){
            MPI_Recv(&vetorRes, 1, MPI_LONG, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for(int j = 0;j<sub_size;j++){
                vetor_ordenado[vetorRes[j][1]] = vetorRes[j][0];
            }
        }
    } else if(rank != 0){
        MPI_Bcast(&t,1,MPI_INT,0,MPI_COMM_WORLD);
        
        vetor = (int*)malloc(sizeof(int) * t);
        MPI_Bcast(vetor,t,MPI_INT,0,MPI_COMM_WORLD);

       
        int aux[sub_size];
        int vetorRes[sub_size][2];
        
        printf("sub %i rank %i size %i \n",sub_size,rank,size);

        int index = 0;
        for(int i = rank ; i < sub_size ; i += size){
            printf("vetor %i = %i \n",i,vetor[i]);

            aux[index] = vetor[i];
            printf("aux %i = %i \n",index,aux[index]);
            index++;
            
        }
        
        int local_rank[sub_size];
        for (int i = 0; i < sub_size;i++){
            local_rank[i] = 0;
        }
        
        for (int i = 0; i < sub_size; i++) {
            for (int j = 0; j < t; j++) {
                if (aux[i] < vetor[j]){
                    local_rank[i]++;
                }else if(aux[i] == vetor[j] && (rank +(i*size)) > j){
                    local_rank[i]++;
                }
            }
        }
        
        
        for(int i = 0; i < sub_size;i++ ){
            //printf("local_rank %i \n",local_rank[i]);
            vetorRes[i][0] = aux[i];
            vetorRes[i][2] = local_rank[i];
        }
        MPI_Send(&vetorRes, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    }
  
   

    MPI_Barrier(MPI_COMM_WORLD);
    // Imprime o vetor ordenado no processo 0
    if (rank == 0) {
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
