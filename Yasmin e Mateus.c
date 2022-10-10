#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include <math.h>

#define N 2000000

int rand_array[N];
int get_max_num(int start_num,int end_num){
    int max = -1;
    for(int p = start_num; p < end_num; p++){
        if(rand_array[p] > max)
            max = rand_array[p];
    }
    return max;
}
int get_final_max_num(int x1,int x2,int x3,int x4){
    int max = x1;
    if(x2 > max)
        max = x2;
    if(x3 > max)
        max = x3;
    if(x4 > max)
        max = x4;
    return max;
}
int main(int argc,char **argv){
    for(int j = 0; j < N; j++){
        rand_array[j] = rand();
    }

    MPI_Comm comm = MPI_COMM_WORLD;
    int size,rank,dest;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(comm,&size);
    MPI_Comm_rank(comm,&rank);

    if(rank==0){
        int max,max1,max2,max3,max4;

        MPI_Recv(&max1,1,MPI_INT,1,1,comm,MPI_STATUS_IGNORE);
        MPI_Recv(&max2,1,MPI_INT,2,2,comm,MPI_STATUS_IGNORE);
        MPI_Recv(&max3,1,MPI_INT,3,3,comm,MPI_STATUS_IGNORE);
        MPI_Recv(&max4,1,MPI_INT,4,4,comm,MPI_STATUS_IGNORE);

        max = get_final_max_num(max1,max2,max3,max4);
        printf("O maior elemento eh: %d\n",max);

    }
    else if(rank==1){
        int max = get_max_num(0,500000);
        MPI_Send(&max,1,MPI_INT,0,1,comm);
    }
    else if(rank==2){
        int max = get_max_num(500001,1000000);
        MPI_Send(&max,1,MPI_INT,0,2,comm);
    }
    else if(rank==3){
        int max = get_max_num(1000001,1500000);
        MPI_Send(&max,1,MPI_INT,0,3,comm);
    }
    else if(rank==4){
        int max = get_max_num(150001,2000000);
        MPI_Send(&max,1,MPI_INT,0,4,comm);
    }
    MPI_Finalize();
    return 0;
}