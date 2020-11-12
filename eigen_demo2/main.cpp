#include <iostream>
#include "eitcap_pca.h"
#include <omp.h>


void LoadData(float* buffer, int m, int n, const char* filePath)
{
    FILE* ft = fopen(filePath, "rt");
    float* pBuf = buffer;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n-1; j++)
        {
            fscanf(ft, "%f ", pBuf++);
        }
        fscanf(ft, "%f \n", pBuf++);
    }

    fclose(ft);
}
void SaveMatrix(MatrixXf& y, int m, int n, const char* filePath)
{
    FILE* ft = fopen(filePath, "w");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(ft, "%f ", y(i, j));
        }
        fprintf(ft, "\n");
    }
    fclose(ft);
}
#if 0
typedef struct
{
    CEITCAPPCA* pPCA;

}STRU_PCA_PARAM;
static void* pca_thread(void* p)
{
    pca[i].Calc(&matBuf[i][0], m, n/4, K);
}
#endif
int main()
{
    CEITCAPPCA pca[4];

    

    int m = 201, n = 416, K = 4;
    MatrixXf matPCA(m , n);
    float buffer[m * n];
    LoadData(buffer, m, n, "/home/lo3ck/test/test.txt");

#ifdef PCA_SPLIT
    float matBuf[4][m * 104];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int d = 0; d < 104; d ++)
            {
                matBuf[i][j * 104 + d] = buffer[j * n + i * 104 + d];
            }
        }
    }
    int nthreads,tid;
    #pragma omp parallel for num_threads(4) 
    for (int i = 0; i < 4; i++)
    {
       // tid=omp_get_thread_num();
        printf("Hello Word from OMP thread %d\n",tid);
        pca[i].Calc(&matBuf[i][0], m, n/4, K);
        
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < m; j ++)
        {
            for (int d = 0; d < 104; d++)
            {
                matPCA(j, i * 104 + d) = pca[i]._matOut(j, d);
            }
        }
    }
    
    SaveMatrix(matPCA, m, n, "/home/lo3ck/test/pca_after_split.txt");
#else 
    pca[0].Calc(&buffer[0], m, n, K);
    SaveMatrix(pca[0]._matOut, m, n, "/home/lo3ck/test/pca_after.txt");
#endif



    
    return 0;
}