#ifndef _EITCAP_PCA_H_
#define _EITCAP_PCA_H_


/**
 * 所有与原始电压值相关的处理
 * */
#include "Eigen/Dense"
#include "Eigen/SVD"

using Eigen::MatrixXf;
using Eigen::VectorXf;

#define IMG_3D_VOLTAGE_COUNT 416
#define RingMaxNumPerfDefault 201

class CEITCAPPCA
{
public:
    CEITCAPPCA();

    /**
     * PCA计算，
     * type: ventlation or perfusion
     * pVolt: all voltage
     * voltageCnt: voltage number , 104 or 416
     * ringNumber: frame number in ring
     * */
    bool Calc(float* pBuffer, int m, int n, int k);

    static const int PCA_COL;
    static const int PCA_ROW;
    static const int PCA_K;

    float _ringOut[IMG_3D_VOLTAGE_COUNT][RingMaxNumPerfDefault];

public:
    void PCA(MatrixXf& mat, MatrixXf& matOut, int m, int n, int K);
    void print_matrix(const char* msg, MatrixXf& matrix, int m, int n);

    

    MatrixXf _mat;
    MatrixXf _matOut;
    
    MatrixXf mat_trans;
    MatrixXf V;
    Eigen::BDCSVD <Eigen::MatrixXf> svd;
   
    MatrixXf b_p;
    MatrixXf b_p_trans;
    MatrixXf b_p_plus;

    
};



#endif