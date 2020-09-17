#include <iostream>
#include "eitcap_pca.h"


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

int main()
{
    CEITCAPPCA pca;

    int m = 201, n = 416, K = 2;
    float buffer[m * n];
    LoadData(buffer, m, n, "/home/lo3ck/workspace/sourcecode/infieit/output/linux_x86_clinic/test/11_211_ori.txt");

    pca.Calc(buffer, m, n, K);

    SaveMatrix(pca._matOut, m, n, "/home/lo3ck/workspace/sourcecode/infieit/output/linux_x86_clinic/test/11_211_pca_after.txt");
    return 0;
}