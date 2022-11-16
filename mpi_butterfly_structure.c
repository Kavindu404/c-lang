#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int Global_sum(int my_int, int my_rank, int comm_sz, MPI_Comm comm); 
int Floor_log(int comm_sz);

const int MAX_CONTRIB = 20;

int main(void) {
   int i, sum, my_int;
   int my_rank, comm_sz;
   MPI_Comm comm;
   int* all_ints = NULL; int* sum_proc = NULL;
   
   MPI_Init(NULL, NULL);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &comm_sz);
   MPI_Comm_rank(comm, &my_rank);

   srandom(my_rank + 1);
   my_int = random() % MAX_CONTRIB;
   
   sum = Global_sum(my_int, my_rank, comm_sz, comm);
   
   if ( my_rank == 0) {
      all_ints = malloc(comm_sz*sizeof(int)); sum_proc = malloc(comm_sz*sizeof(int));
      
      MPI_Gather(&my_int, 1, MPI_INT, all_ints, 1, MPI_INT, 0,comm);
      printf("\nInts being summed:\n   ");
      for (i = 0; i < comm_sz; i++)
         printf("%d ", all_ints[i]);
      printf("\n");
      
      MPI_Gather(&sum, 1, MPI_INT, sum_proc, 1, MPI_INT, 0,comm);
      printf("Sums on the processes:\n   ");
      for (i = 0; i < comm_sz; i++)
         printf("%d ", sum_proc[i]);
      printf("\n");
      free(all_ints);
   } else {
      
      MPI_Gather(&my_int, 1, MPI_INT, all_ints, 1, MPI_INT, 0,comm);
      
      MPI_Gather(&sum, 1, MPI_INT, sum_proc, 1, MPI_INT, 0,comm);
   }
   
   MPI_Finalize();
   return 0;
}  

int Global_sum(
      int my_int,
      int my_rank,
      int comm_sz,
      MPI_Comm comm) {
   
   int partner, recvtemp;
   int my_sum = my_int;
   unsigned bitmask = 1;
   int floor_log_p = Floor_log(comm_sz);

  
   if (my_rank >= floor_log_p) {
      partner = my_rank - floor_log_p;
      
      MPI_Send(&my_sum, 1, MPI_INT, partner, 0, comm);
   } else {
      partner = my_rank + floor_log_p;
      if (partner < comm_sz) {
         
         MPI_Recv(&recvtemp, 1, MPI_INT, partner, 0, comm, MPI_STATUS_IGNORE);
         my_sum += recvtemp;
      }
   }
   
  
   if (my_rank < floor_log_p)
      while (bitmask < floor_log_p) {
         partner = my_rank ^ bitmask;
          
         MPI_Send(&my_sum, 1, MPI_INT, partner, 0, comm);
         MPI_Recv(&recvtemp, 1, MPI_INT, partner, 0, comm, MPI_STATUS_IGNORE);
         my_sum += recvtemp;
         bitmask <<= 1;
      }  
      
   if (my_rank >= floor_log_p) {
      partner = my_rank - floor_log_p;
      
      MPI_Recv(&my_sum, 1, MPI_INT, partner, 0, comm, MPI_STATUS_IGNORE);
   } else {
      partner = my_rank + floor_log_p;
      if (partner < comm_sz)
         
         MPI_Send(&my_sum, 1, MPI_INT, partner, 0, comm);
   }

   return my_sum;
}  

int Floor_log(int comm_sz) {
   int fl = 1;

   while (2*fl <= comm_sz)
      fl *= 2;

   return fl;
}  
