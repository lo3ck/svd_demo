#include "eitcap_pca.h"

CEITCAPPCA::CEITCAPPCA()
{
    _mat = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>();
    _mat.resize(PCA_ROW, PCA_COL);

    _matOut = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>();
    _matOut.resize(PCA_ROW, PCA_COL);

    mat_trans = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>();
    mat_trans.resize(PCA_COL, PCA_ROW);

    V = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>();
    V.resize(PCA_COL, PCA_COL);

    _pSvd = new Eigen::BDCSVD<Eigen::MatrixXf>(PCA_COL, PCA_COL, Eigen::ComputeThinV);

   // mean_x = Eigen::VectorXf<float, Eigen::Dynamic>();
   // mean_x.resize(PCA_COL);

    b_p = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>();
    b_p.resize(PCA_ROW, PCA_K);

    b_p_trans = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>();
    b_p_trans.resize(PCA_K, PCA_ROW);

    b_p_plus = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>();
    b_p_plus.resize(PCA_K, PCA_K);
   
}

const int CEITCAPPCA::PCA_ROW = RingMaxNumPerfDefault;
const int CEITCAPPCA::PCA_COL = IMG_3D_VOLTAGE_COUNT;
const int CEITCAPPCA::PCA_K = 4;

bool CEITCAPPCA::Calc(float* pBuffer, int m, int n, int k)
{
    float* pBuf = pBuffer;
    for (int i = 0; i < m ; i++)
    {
        for (int j = 0; j < n; j++)
        {
            _mat(i, j) = *pBuf++;
        }
    }
    PCA(_mat, _matOut, m, n, k);
    return true;
}
void CEITCAPPCA::print_matrix(const char* msg, MatrixXf& matrix, int m, int n)
{
    return;
    char sz[1024];
    sprintf(sz, "/home/lo3ck/tmp/11_121_%s_demo_%d_%d.txt", msg, m, n);
    FILE* ft = fopen(sz, "w");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(ft, "%f ", matrix(i, j));
        }
        fprintf(ft, "\n");
    }
    fclose(ft);
    return;
}
struct timeval LKTimeCalcStart(void)
{
    struct timezone tz;
    struct timeval t1;
    gettimeofday ( &t1 , &tz );  
    return t1;
}
int LKTimeCalcEnd(struct timeval* pt1)
{
    struct timeval t2;
    struct timezone tz; 
    int sec_dif, us;  
    gettimeofday ( &t2 , &tz );  
    sec_dif = t2.tv_sec - pt1->tv_sec;
    us = t2.tv_usec - pt1->tv_usec;
    return sec_dif * 1000 + us / 1000;
}
void CEITCAPPCA::PCA(MatrixXf& mat, MatrixXf& matOut, int m, int n, int K)
{
    print_matrix("start", mat, m , n);

    Eigen::setNbThreads(4);

    struct timeval start = LKTimeCalcStart();

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

    mat_trans = mat.transpose();
    print_matrix("x trans", mat_trans, n , m);

    V = (mat_trans*mat) / (m - 1);
    print_matrix("x trans _ x", V, n , n);

    /* Init  */
    

    _pSvd->compute(V, Eigen::ComputeThinV);
    V =  _pSvd->matrixV();
    
    print_matrix("svd", V, n , n);

    b_p = mat * V.leftCols(K);
    b_p_trans = b_p.transpose();

    b_p_plus = b_p_trans * b_p;   

    matOut = b_p *(b_p_plus.inverse() * (b_p_trans * mat));
    print_matrix("out ", matOut, m , n);

    int ms = LKTimeCalcEnd(&start);

    printf("PCA time is: %d ms\n", ms);
}