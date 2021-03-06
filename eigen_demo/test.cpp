#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
using namespace std;
using Eigen::MatrixXf;
using Eigen::VectorXf;

void print_matrix(const char* msg, MatrixXf& matrix, int m, int n)
{
    return;
    printf("info: %s\n", msg);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.4f ", matrix(i, j));
        }
        printf("\n");
    }
}
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

void PCA(float* pData, int m, int n, int K)
{
    float* pBuf = pData;
    MatrixXf mat;
    mat = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>();
    mat.resize(m, n);
    //MatrixXf mat(m,n);//MatrixXd表示是任意尺寸的矩阵ixj, m(2,2)代表一个2x2的方块矩阵
    for (int i = 0; i < m ; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat(i, j) = *pBuf++;
        }
    }
    SaveMatrix(mat, m, n, "/home/lo3ck/workspace/sourcecode/infieit/output/linux_x86_clinic/tmp/11_211_pca_ori.txt");
    print_matrix("start", mat, m , n);

    VectorXf mean_x(n);
    mean_x = mat.colwise().mean();

    for (int row = 0; row < m; row ++)
    {
        for (int col = 0; col < n; col ++)
        {
            mat(row, col) -= mean_x(col);
        }
    }
    print_matrix("x - mean", mat, m , n);

    MatrixXf mat_trans(n, m);
    mat_trans = mat.transpose();
    print_matrix("x trans", mat_trans, n , m);

    mat_trans = (mat_trans*mat) / (m - 1);
    print_matrix("x trans * x", mat_trans, n , m);

    //Eigen::BDCSVD <Eigen::MatrixXf> svd(mat_trans, Eigen::ComputeThinV );
    MatrixXf V(n, n);
    #if 1
    Eigen::BDCSVD <Eigen::MatrixXf> svd;
    svd.compute(mat_trans, Eigen::ComputeThinV);
    
    V =  svd.matrixV();
    print_matrix("svd", V, m , n);
    #else 
    Eigen::EigenSolver<MatrixXf> es;
    es.compute(mat_trans, /* computeEigenvectors = */ true);
    V = es.pseudoEigenvectors();
    //std::cout << es.pseudoEigenvectors()<< endl;
    print_matrix("EigenSolver", V, m , n);
    #endif
    //return;
    

    MatrixXf b_p(m, K);
    MatrixXf b_p_trans(K, m);

    b_p = mat * V.leftCols(K);
    b_p_trans = b_p.transpose();

    MatrixXf b_p_plus(K, K);
    b_p_plus = b_p_trans * b_p;
   

    MatrixXf y = b_p *(b_p_plus.inverse() * (b_p_trans * mat));
    print_matrix("PCA Result", y, m , n);
    SaveMatrix(y, m, n, "/home/lo3ck/workspace/sourcecode/infieit/output/linux_x86_clinic/tmp/11_211_pca_after.txt");
}





int main()
{
    #if 0
    int m = 3, n = 3;
    int K = 2;

    float buffer[m * n] = {3, 2, 1, 2, 2, 0, 1, 0, 1};
    #else 
    int m = 201, n = 416, K = 2;
    float buffer[m * n];
    LoadData(buffer, m, n, "/home/lo3ck/workspace/sourcecode/infieit/output/linux_x86_clinic/tmp/11_211_ori.txt");
#endif
    PCA(buffer, m, n, K);
}