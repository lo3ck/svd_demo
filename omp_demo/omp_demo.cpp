#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
void Test(int n)
{
    
    usleep(n * 100000);
    printf("%d\n", n);
    
}
int main(int argc, char *argv[])
{
    int i;
    int nthreads,tid;
    #pragma omp parallel private(nthreads,tid)
    for (i = 0; i < 10; ++i)
    {
        tid=omp_get_thread_num();
        printf("Hello Word from OMP thread %d\n",tid);

        // only master thread does this;
        if(tid==0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of thread: %d\n",nthreads);
        }
        Test(i);
    }
        
    
    return 1;
}