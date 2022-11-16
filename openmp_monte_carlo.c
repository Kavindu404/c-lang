#include <stdio.h>
#include <omp.h>
#include<stdlib.h>
long long monte_carlo(long long l_num_tosses, int tid);

void main(void){

    long long int num_tosses = 1000000;
    long long int l_num_tosses = num_tosses/8;
    long long int inside=0;
    long long int local_inside;
    double pi_est;
    int tid;
    
    #pragma omp parallel num_threads(8)
    {
        
        
    #pragma omp critical
    {
       tid = omp_get_thread_num();
       inside += monte_carlo(l_num_tosses, tid);
    }
    
    }
    
    pi_est = 4*inside/((double)num_tosses);
    printf("The Pi estimate is: %.4f\n", pi_est);




}


long long monte_carlo(long long l_num_tosses, int tid){

    long long int i;
    double x,y;
    double d_sqrd;
    long long l_inside=0;
    
    srandom(tid+1);
    for (i=0;i<l_num_tosses;i++){
    
        x = (double)random()/RAND_MAX;
        y = (double)random()/RAND_MAX;
        
        d_sqrd = (x*x) + (y*y);
        
        
        
        if (d_sqrd<=1){
            l_inside += 1;
        }
    
    }
    return l_inside;
}




