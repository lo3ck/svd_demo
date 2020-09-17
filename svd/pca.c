#include <stdio.h>

extern double **dmatrix(int, int, int, int);
extern double *dvector(int, int);
extern void svdcmp(double **, int, int, double *, double **);

void print_matrix(double **x, int m, int n)
{
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%.4f ", x[i][j]);
        }
        printf("\n");
    }
}

void pca(double **x, int m, int n, int k_size, double **y)
{
    printf("pca start\n");

    /*
    M = size(X, 1);

    mean_X = mean(X);
    X = X-repmat(mean_X,M,1);
    */
    double avg = 0;
    for (int col = 1; col <= n; col++)
    {
        avg = 0;
        for (int row = 1; row <= m; row++)
        {
            avg += x[row][col];
        }
        avg /= m;

        for (int row = 1; row <= m; row++)
        {
            x[row][col] -= avg;
        }
    }
    printf("x-mean: \n");
    print_matrix(x, m, n);
    /**
     * [~,~,V] = svd((X'*X)/(M-1));
    */
    double **x_trans = dmatrix(1, m, 1, n);
    double tmp = 0;
    for (int col = 1; col <= n; col++)
    {
        for (int row = 1; row <= m; row++)
        {
            x_trans[row][col] = x[col][row];
        }
    }

    printf("x trans: \n");
    print_matrix(x_trans, m, n);

    double **x_ins = dmatrix(1, m, 1, n);
    for (int row = 1; row <= m; row++)
    {
        for (int col = 1; col <= n; col++)
        {
            x_ins[row][col] = 0;
            for (int i = 1; i <= n; i++)
            {
                x_ins[row][col] += (x_trans[row][i] * x[i][col]);
            }
            x_ins[row][col] /= (m - 1);
        }
    }
    printf("x trans * x: \n");
    print_matrix(x_ins, m, n);

    double *w;
    double **u, **v;
    double t;
	double t1[4],t2[4];
    w = dvector(1, m);
    u = dmatrix(1,3,1,3);
    v = dmatrix(1, m, 1, n);

    for (int i=1; i<=3; i++) {
		for (int j=1; j<=3; j++)
			u[i][j] = x_ins[i][j];
	}

    svdcmp(u,m,n,w,v);

    /* Sort the singular values in descending order */
	for (int i=1; i<3; i++) {
		for (int j=i+1; j<=3; j++) {
			if (w[i]<w[j]) {
				t = w[i];
				w[i] = w[j];
				w[j] = t;
				for (int k=1; k<=3; k++) {
					t1[k] = u[k][i];
					t2[k] = v[k][i];
				}
				for (int k=1; k<=3; k++) {
					u[k][i] = u[k][j];
					v[k][i] = v[k][j];
				}
				for (int k=1; k<=3; k++) {
					u[k][j] = t1[k];
					v[k][j] = t2[k];
				}
			}
		}
	}

	for (int i=1; i<=3; i++) {
		printf("Sigular value %d = %le\n",i,w[i]);
		printf("        vector   = %le %le %le\n",u[1][i],u[2][i],u[3][i]);
	}

    printf("svd v: \n");
    print_matrix(u, m, n);

    double **b_p = dmatrix(1, m, 1, k_size);

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= k_size ; j++)
        {
            b_p[i][j] = 0;
            for (int z = 1; z <= n; z++)
            {
                b_p[i][j] += x[i][z] * v[z][j];
            }
        }
    }
    printf("b_p: \n");
    print_matrix(b_p, m, k_size);

    double **b_p_trans = dmatrix(1, k_size, 1, m);

    for (int row = 1; row <= k_size; row++)
    {
        for (int col = 1; col <= m; col++)
        {
            b_p_trans[row][col] = b_p[col][row];
        }
    }

    printf("b_p_trans: \n");
    print_matrix(b_p_trans, k_size, m);

    
}